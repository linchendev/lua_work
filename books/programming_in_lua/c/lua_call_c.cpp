#include <helper.hpp>

// call a function 'f' defined in Lua
double f (lua_State *L, double x, double y) {
	int isnum;
	double z;

	//push functions and arguments
	lua_getglobal(L, "f"); //function to be called
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	//do the call (2 arguments, 1 result)
	if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
		error(L, "error running  function 'f': %s", lua_tostring(L, -1));	
	}

	z = lua_tonumberx(L, -1, &isnum);
	if (!isnum) {
		error(L, "'f' should return a number");
	}
	lua_pop(L, 1);
	return z;
}

int main() {
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, "e12.lua");

	//first call
	//double xy;
	//xy = f(L, 2, 3); 
	//cout << "f result1:" << xy << endl;

	//second call
	double z;
	call_va(L, "f", "dd>d", 3, 4, &z);
	cout << "f result2:" << z << endl;
	lua_close(L);
	return 0;
}
