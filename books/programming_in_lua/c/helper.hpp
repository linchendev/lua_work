//lua调用c++、c函数

#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <lua.hpp>

//dump堆栈
static void stackDump(lua_State *L) {
	int i;
	int top = lua_gettop(L); //返回栈顶（最后一个）的索引，等同于总元素个数
	for (i = 1; i <= top; i++) {
		int t = lua_type(L, i);
		switch (t) {
			case LUA_TSTRING: //strings
				printf("`%s`", lua_tostring(L, i));
				break;
			case LUA_TBOOLEAN: //booleans
				printf(lua_toboolean(L, i) ? "true" : "false");
				break;
			case LUA_TNUMBER: //numbers
				printf("%g", lua_tonumber(L, i));
				break;
			default: //other values
				printf("%s", lua_typename(L, t));
				break;
		}
		printf(" "); //put a separator
	}
	printf("\n"); //end the listing
}

static void error(lua_State *L, const char* fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}

#define MAX_COLOR 255

//assume that table is on the top of the stack
int getcolorfield(lua_State *L, const char *key) {
	int result, isnum;
	lua_pushstring(L, key);
	cout << "--------- getcolorfield:" << endl;
	stackDump(L);
	lua_gettable(L, -2);

	result = (int)(lua_tonumberx(L, -1, &isnum) * MAX_COLOR);
	if (!isnum) {
		error(L, "invalid componet '%s' in color", key);
	}
	lua_pop(L, 1);
	return result;
}

void setcolorfield(lua_State *L, const char *index, int value) {
	lua_pushnumber(L, (double)value/MAX_COLOR);
	lua_setfield(L, -2, index);
}

//TODO: Segmentation fault,还不知道什么BUG
//gdb调试不太行，需要调整下，找下对应的版本
void call_va(lua_State *L, const char *func, const char *sig, ...) {
	va_list vl;
	int narg, nres; //number of arguments and results

	va_start(vl, sig);
	lua_getglobal(L, func); //push function

	//push and count arguments
	for (narg = 0; *sig; narg++) {
		//check stack space
		luaL_checkstack(L, 1, "too many arguments");

		switch (*sig++) {
			case 'd': //double argument
				lua_pushnumber(L, va_arg(vl, double));
				break;
			case 'i': //int argument
				lua_pushinteger(L, va_arg(vl, int));
				break;
			case 's': //string argument
				lua_pushstring(L, va_arg(vl, char *));
				break;
			case '>':
				goto endargs; //break the loop
			default:
				error(L, "invalid option (%c)", *(sig-1));

		}
	}

endargs:
	nres = strlen(sig); //number of expected results

	if (lua_pcall(L, narg, nres, 0) != 0) { //do the call 
		error(L, "error calling '%s': %s", func, lua_tostring(L, -1));	
	}

	//retrieve results
	nres = -nres; //stack index of first result
	while (*sig) { //repeat for each result
		switch (*sig++) {
			case 'd': {//double result
				int isnum;
				double n = lua_tonumberx(L, nres, &isnum);
				if (!isnum) {
					error(L, "wrong result type");
				}
				*va_arg(vl, double *) = n; //FIXME 指针传进来还是段错误
				break;
			}
			case 'i': {//int result
				int isnum;
				int n = lua_tointegerx(L, nres, &isnum);
				if (!isnum) {
					error(L, "wrong result type");
				}
				*va_arg(vl, int *) = n;
				break;
			}
			case 's': {//string result
				const char *s = lua_tostring(L, nres);
				if (s == NULL) {
					error(L, "wrong result type");
				}
				*va_arg(vl, const char **) = s;
				break;
			}
			default:
				error(L, "invalid option (%c)", *(sig - 1));
		}
		nres++;
	}
	va_end(vl);
}
