Set = {}
function Set.new(t)
	setmetatable(t, Set)
	return t
end

s1 = Set.new{1,2}
s2 = Set.new{3,4}
print(getmetatable(s1), s1)
print(getmetatable(s2), s2)
