-- desc: to print the list of contributing guys
function list_iter (t)
	local i = 0
	local n = #t
	return function()	-- 这里是想实现一个static功能
		i = i + 1
		if i <= n then return t[i] end
	end
end

helpful_guys = {
	"-----start-----",
	"123","sdfsdf","123213",
	"\n",
	
	"-----sdfsdf-----",
	"sfsdfsdf",
	"\n"
}

for e in list_iter(helpful_guys) do
	print(e)
end
