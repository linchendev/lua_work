-- 闭包实现 
function allwords()
	local line = io.read()	-- current line
	local pos = 1			-- current position in the line
	return function()		-- iterator function
		while line do		-- repeat while there are lines
			local s, e = string.find(line, "%w+", pos)
			if s then		-- found a word
				pos = e + 1	-- next position is after this word
				return string.sub(line, s, e)
			else
				line = io.read()
				pos = 1
			end
		end
	return nil
	end
end

--[[
for word in allwords() do
	print(word)
end
]]--

-- 采用table实现
local iterator
function allwords_table()
	local state = {line = io.read(), pos = 1}
	return iterator, state
end

function iterator(state)
	while state.line do			-- repeat while there are lines
		-- search for next word
		local s, e = string.find(state.line, "%w+", state.pos)
		if s then
			state.pos = e + 1
			return string.sub(state.line, s, e)
		else
			state.line = io.read()
			state.pos = 1
		end
	end
	return nil
end

for word in allwords_table() do
	print(word)
end

