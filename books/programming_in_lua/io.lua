-- local count = 1
-- while true do
-- 	local line = io.read() -- lua: io.lua:5: attempt to call local 'line' (a string value)
-- 	if line == nil then break end
-- 	io.write(string.format("%6d ", count), line "\n")
-- 	count = count + 1
-- end


local lines = {}
for line in io.lines() do
	table.insert(lines, line)
end

table.sort(lines)

for i, l in ipairs(lines) do io.write(l, "\n") end
