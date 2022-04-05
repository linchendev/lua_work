#include "helper.hpp"

int main() {
	lua_State *L = luaL_newstate(); 

	lua_pushboolean(L, 1);
	lua_pushnumber(L, 10);
	lua_pushnil(L);
	lua_pushstring(L, "hello");
	stackDump(L);

	lua_pushvalue(L, -4);
	stackDump(L);

	lua_replace(L, 3);
	stackDump(L);

	lua_settop(L, 6);
	stackDump(L);

	lua_remove(L, -3);
	stackDump(L);

	lua_settop(L, -5);
	stackDump(L);

	lua_close(L);
	return 0;
}
