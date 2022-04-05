--测试尾调用会不会被执行呢

function f()
	return 1
end

function f1()
	return f()
end

local t = f1()

print(f1(), t)
