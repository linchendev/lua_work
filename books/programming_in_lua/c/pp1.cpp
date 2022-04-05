#include "helper.hpp"

struct ColorTable {
	char *name;
	unsigned char red, green, blue;
} colortable[] = {
	{"WHITE", MAX_COLOR, MAX_COLOR, MAX_COLOR},
	{"RED", MAX_COLOR, 0, 0},
	{"GREEN", 0, MAX_COLOR, 0},
	{"BLUE", 0, 0, MAX_COLOR},
	{"BLACK", 0, 0, 0},
	{NULL, 0, 0, 0},
};

int getglobint(lua_State *L, const char *var) {
	int isnum, result;
	lua_getglobal(L, var);
	result = (int)lua_tointegerx(L, -1, &isnum);
	if (!isnum) {
		error(L, "`%s` should be a number\n", var);
	}
	lua_pop(L, 1);
	return result;
}

void load(lua_State *L, const char *fname, 	int *w, int *h) {
	if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
		error(L, "cannot run config. file: %s", lua_tostring(L, -1));
	}

	*w = getglobint(L, "width");
	*h = getglobint(L, "height");
}

void loadtable(lua_State *L, const char *fname) {
	if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
		error(L, "cannot run config. file: %s", lua_tostring(L, -1));
	}

	lua_getglobal(L, "background");
	if (!lua_istable(L, -1)) {
		error(L, "`background` is not a table");
	}

	int red, green, blue;
	red = getcolorfield(L, "red");
	green = getcolorfield(L, "green");
	blue = getcolorfield(L, "blue");

	printf("loadtable: background, %d,%d,%d\n", red, green, blue);
}

//assume that table is at the top
void setfield(const char *index, int value) {
	lua_pushstring(L, index);
	lua_pushnumber(L, (double)value/MAX_COLOR);
	lua_settable(L, -3);
}

void setcolor(struct ColorTable *ct) {
	lua_newtable(L); //create a table
	setfield("r", ct->red); //table.r = ct->r
	setfield("g", ct->green);
	setfield("b", ct->blue);
	lua_setglobal(L, ct->name);
}

int main() {
	int width, height;

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	load(L, "pp_config.lua", &width, &height);
	printf("load: %d %d\n", width, height);

	loadtable(L, "pp_config1.lua");

	//将颜色注册到lua
	//应用程序必须在运行用户脚本之前，执行这个循环
	int i = 0;
	while (colortable[i].name != NULL) {
		setcolor(&colortable[i++]);
	}
	return 0;
}
