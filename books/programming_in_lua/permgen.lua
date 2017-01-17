function printResult(a)
	for _,v in ipairs(a) do
		io.write(v, " ")
	end
	io.write("\n")
end

-- 打印一个数组元素的所有排列
function permgen(a, n)
	if n == 0 then
		printResult(a)
	else
		for i=1,n do
			a[n],a[i] = a[i],a[n]
			permgen(a, n-1)
			a[n],a[i] = a[i],a[n]
		end
	end
end

function comb(a, b, n, m)
	if m == 0 then
		printResult(b)
	else
		for i=n,1,-1 do
			b[m] = a[i]
			comb(a,b,i-1,m-1)
		end
	end
end

-- main
--permgen({1,2,3,4}, 4)
b = {}
comb({1,2,3,4,5,6}, b, 6, 3)
