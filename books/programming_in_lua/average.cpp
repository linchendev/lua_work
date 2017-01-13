//lua调用c++、c函数

#include <iostream>
using namespace std;

#include <stdio.h>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h> 
}

lua_State* L;

static int average(lua_State* L)
{
	//返回栈中元素的个数
	int n = lua_gettop(L);
	double sum = 0;
	int i;
	for(int i = 1; i <= 2; i++)
	{
		if(!lua_isnumber(L, i))
		{
			lua_pushliteral(L, "Incorrect argument to 'average'");
			lua_error(L);
		}
		sum += lua_tonumber(L, i);
	}
	/* push the average */
	lua_pushnumber(L, sum/n);
	/* push the sum */
	lua_pushnumber(L, sum);

	/* return the number of results */
	return 2;
}

int main(int argc, char* argv[])
{
	/* initialize Lua */
	L = luaL_newstate();

	/* load Lua libraries */
	luaL_openlibs(L);

	/* register our function */
	lua_register(L, "average", average);

	/* run the script */
	luaL_dofile(L, "e15.lua");

	//如果没有该变量，则默认为0,进行压栈
	lua_getglobal(L, "avg");
	cout << "avg is:" << lua_tointeger(L, 1) << endl;

	//lua_pop(L, 1);
	lua_getglobal(L, "sum");
	cout << "sum is:" << lua_tointeger(L, 2) << endl;

	/* cleanup Lua */
	lua_close(L);

	return 0;
}
