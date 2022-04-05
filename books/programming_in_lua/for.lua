local i = 0
for i=0,10 do --外层i的值没有被修改，因为循环内的i为独立var
	print(i)
end
print(i)
