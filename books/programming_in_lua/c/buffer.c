#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int main()
{
	char buff[256];
	int error;
	//lua_State *L = lua_open();
	lua_State *L = luaL_newstate();
	luaopen_base(L);
	luaopen_table(L);
	luaopen_io(L);
	luaopen_string(L);
	luaopen_math(L);

	while(fgets(buff, sizeof(buff), stdin) != NULL) {
		error = luaL_loadbuffer(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0); //pcall运行
		if(error) {
			fprintf(stderr, "%s", lua_tostring(L, -1));
			lua_pop(L, 1); //pop error message from the stack
		}
	}

	return 0;
}

