-- desc: to print the list of contributing guys
-- example:thanks.lua
function list_iter (t)
	local i = 0
	local n = #t
	return function()	-- 这里是想实现一个static功能
		i = i + 1
		if i <= n then return t[i] end
	end
end

-- defines a factorial function
-- 阶乘
function fact (n)
	if n == 0 then
		return 1
	else
		return n * fact(n-1)
	end
end

function norm (x, y)
	local n2 = x^2 + y^2
	return math.sqrt(n2)
end

function twice (x)
	return 2*x
end

