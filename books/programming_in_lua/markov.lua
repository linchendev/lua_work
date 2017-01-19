-- 马尔可夫链表
local N = 2
local MAXGEN = 10000
local NOWORD = "\n"
local statetab = {}
--[[
statetab = 
{
	["\n \n"]		= {"the"},
	["\n the"]		= {"more"},
	["the more"]	= {"we", "we"},
	["more we"]		= {"try", "do"},
	["we try"]		= {"the"},
	["try the"]		= {"more"},
	["we do"]		= {"\n"},
}
]]--

function allwords()
	local line = io.read()
	local pos = 1
	return function ()
		while line do
			local s, e = string.find(line, "%w+", pos)
			if s then
				pos = e + 1
				return string.sub(line, s, e)
			else
				line = io.read()
				pos = 1
			end
		end
		return nil
	end
end

function prefix(w1, w2)
	return w1 .. ' ' .. w2
end

function printtable(tab)
	for k,v in pairs(tab) do
		print(k, v)
	end
end


function insert(index, value)
	if not statetab[index] then
		statetab[index] = {}
	end
	table.insert(statetab[index], value)
	--printtable(statetab[index])
end

local w1, w2 = NOWORD,NOWORD
for w in allwords() do
	insert(prefix(w1, w2), w)
	w1 = w2; w2 = w;
end

insert(prefix(w1, w2), NOWORD)

for k,v in pairs(statetab) do
	print("key:", k)
	printtable(v)
end

w1 = NOWORD; w2 = NOWORD
for i=1,MAXGEN do
	local list = statetab[prefix(w1, w2)]
	-- choose a random item from list
	local r = math.random(#list)
	local nextword = list[r]
	if nextword == NOWORD then return end
	io.write(nextword, " ")
	w1 = w2; w2 = nextword
end
