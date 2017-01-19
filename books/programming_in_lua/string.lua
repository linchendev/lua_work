-- 字符串缓冲

-- 从文件中读取大量字符串

-- WARNING: bad code ahead!!
-- 效率低下
--[[
local buff = ""
for line in io.lines() do
	buff = buff .. line .. "\n"
end
]]--

--[[
优化思路：用一个栈，在栈的底部用来保存已经生成的大的字符串，而小的串从栈顶入栈。
栈的状态变化和经典的汉诺塔问题类似：位于栈下面的串肯定比上面的长，只要一个较长的
串入栈后比它下面的串长，就将两个串合并成一个新的更大的串，新生成的串继续与相邻的
串比较如果长于底部的将继续进行合并，循环进行到没有串可以合并或者到达栈底。
]]--

function newStack()
	return {""}
end

function addString(stack, s)
	table.insert(stack, s)
	for i = #stack, 1, -1 do
		if string.len(stack[i]) > string.len(stack[i-1]) then
			break
		end
		stack[i] = stack[i] .. table.remove(stack)
	end
end

function toString(t)
	return table.concat(t)
end

-- table.concat 可以合并所有字符串
local s = newStack()
for line in io.lines("utils.lua") do
	addString(s, line .. "\n")
end

s = toString(s)
print(s)
