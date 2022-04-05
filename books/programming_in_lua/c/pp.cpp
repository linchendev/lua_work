#include "helper.hpp"

//！失败了，用pp1.cpp
void load (char *filename, int *width, int *height) {
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

//	if (luaL_dofile(L, filename)) {
//		luaL_error(L, "cannot run configuration file: %s", lua_tostring(L, -1));
//	}
//

	if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0)) {
		luaL_error(L, "cannot run configuration file: %s", lua_tostring(L, -1));
	}

	lua_getglobal(L, "width");
	*width = (int)lua_tonumber(L, -1);

	lua_getglobal(L, "height");
	*height = (int)lua_tonumber(L, -1);

	if (!lua_isnumber(L, -2)) {
		luaL_error(L, "`width` should be a number\n");
	}
	if (!lua_isnumber(L, -1)) {
		luaL_error(L, "`height` should be a number\n");
	}


	cout << "load:" << (int)lua_tonumber(L, 1) << (int)lua_tonumber(L, 2)<< endl;

	lua_close(L);
}

int main() {
	int width, height;

	load("pp_config.lua", &width, &height);
	return 0;
}
