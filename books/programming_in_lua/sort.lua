--table排序
network = {
	{name = "grauna", ip = "1.0.0.1"},
	{name = "arraial", ip = "1.0.0.2"},
	{name = "lua", ip = "1.0.0.3"},
	{name = "derain", ip = "1.0.0.4"},
	{name = "grauna1", ip = "1.0.0.5"},
}

table.sort(network, function(a,b)
	return (a.name > b.name)
end)

for k,v in pairs(network) do
	print(k .. " " .. v.name)
end

