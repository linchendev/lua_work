-- 非抢占式多线程 TODO 为啥下载不下来

-- LuaSocket库
local socket = require "socket"

function receive(con)
	con:settimeout(0)
	local s, status = con:receive(2^10)
	if status == "timeout" then
		print("receive timeout")
		coroutine.yield(connection)
	end
	print("receive:", s, status)
	return s, status
end


function download(host, file)
	print("start download file:", file)
	local c = assert(socket.connect(host, 80))
	local count = 0
	c:send("GET" .. file .. " HTTP/1.0\r\n\r\n")
	while true do
		local s, status = receive(c)
		count = count + string.len(s)
		if status == "closed" then break end
	end
	c:close()
	print("end download file:", file, count)
end

--download(host, file)

threads = {}
function get(host, file)
	local co = coroutine.create(function ()
		download(host, file)
	end)
	table.insert(threads, co)
end

function dispatcher()
	while true do
		local n = #threads
		if n == 0 then break end
		for i=1,n do
			local status, res = coroutine.resume(threads[i])
			if not res then
				table.remove(threads, i)
				break
			end
		end
	end
end

function dispatcher_select()
	while true do
		local n = #threads
		if n == 0 then break end
		local connections = {}
		for i=1,n do
			local status, res = coroutine.resume(threads[i])
			if not res then
				table.remove(threads, i)
				break
			else
				table.insert(connections, res)
			end
		end
		if #connections == n then
			socket.select(connections)
		end
	end
end

host = "www.3w.org"

get(host, "/TR/html401/html40.txt")
get(host, "/TR/REC-html32.html")

dispatcher_select()


