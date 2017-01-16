-- 尾调用

function room1()
	print("I'm in room 1,input the next:")
	local move = io.read()
	if move == "s" then
		return room3()
	elseif move == "e"  then
		return room2()
	else
		print("invalid move")
		return room1()
	end
end

function room2()
	print("I'm in room 2,input the next:")
	local move = io.read()
	if move == "s" then
		return room4()
	elseif move == "w"  then
		return room1()
	else
		print("invalid move")
		return room2()
	end
end

function room3()
	print("I'm in room 3,input the next:")
	local move = io.read()
	if move == "n" then
		return room1()
	elseif move == "e"  then
		return room4()
	else
		print("invalid move")
		return room3()
	end
end

function room4()
	print("congratulations!")
end

room1()
