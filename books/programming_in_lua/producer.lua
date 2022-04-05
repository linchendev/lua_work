--function producer ()
--	while true do
--		local x = io.read()
--		send(x)
--	end
--end

-- TODO：测试失败

function consumer ()
	while true do
		local x = receive()
		io.write(x, "\n")
	end	
end


function receive()
	local status, value = coroutine.resume(producer)
	--print("receive:", status, value)
	return value
end

function send()
	coroutine.yield(x)
end


producer = coroutine.create(function ()
	while true do
		local x = io.read()
		send(x)
	end
end)


