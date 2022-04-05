#include <stdio.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

/* the Lua interpreter */
lua_State* L;

int luaadd ( int x, int y )
{
	int sum;
	lua_getglobal(L, "add");

	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	/* call the function with 2 
	 * arguments, return 1 result
	 */ 
	lua_call(L, 2, 1);

	/* get the result */
	sum = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return sum;
}

int main()
{
	int sum;
	L = luaL_newstate();
	luaL_dofile(L, "e12.lua");

	sum = luaadd(10, 15);

	printf("The sum is %d", sum);

	lua_close(L);
	return 0;
}
