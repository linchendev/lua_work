--可变参数
printResult = ""

function myprint(...)
	print("arg param len:", arg.n)
	for i,v in ipairs(arg) do
		printResult = printResult .. tostring(v) .. "\t"
	end
	print(printResult)
end

myprint(1,2,3,4)
