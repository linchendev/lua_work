#include "helper.hpp"


int main() {
	lua_State *L = luaL_newstate();	

	lua_pushnumber(L, 3.5);
	lua_pushstring(L, "hello");
	lua_pushnil(L);

	stackDump(L);
	cout << "lua_rotate(L, 1, -1): " << endl;
	lua_rotate(L, 1, -1); //可以理解为循环左移这种操作
	stackDump(L);

	cout << "lua_rotate(L, 1, 1): " << endl;
	lua_rotate(L, 1, 1);
	stackDump(L);

	//拷贝-2位置的元素并添加到栈顶
	lua_pushvalue(L, -2);
	stackDump(L);

	cout << "------- remove 1 ----" << endl;
	//删除栈底
	lua_remove(L, 1);
	stackDump(L);

	cout << "------- insert -2 ----" << endl;
	lua_pushnumber(L, 1111);
	stackDump(L);
	lua_insert(L, -3);
	stackDump(L);
	return 0;
}
