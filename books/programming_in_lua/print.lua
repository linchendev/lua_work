-- 可变参数

printResult = ""

function Print(a, b, ...)
	params = { ... }
	for i,v in ipairs(params) do
		printResult = printResult .. tostring(v) .. "\t"
	end
	printResult = printResult .. "\n"
end

-- 获取可变参数
function select(n, ...)
	args = {...}
	return args[n]
end

--print(select(1, string.find("hello hello", "hel")))

function fwrite(fmt, ...)
	args = {...}
	return print(string.format(fmt, table.unpack(args)))
end

--fwrite("%s %d", 1, 2)

function Window(options)
	print(options.x, options.y)
end

Window({x=0,y=0})

