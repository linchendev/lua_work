Account = {balance = 0}

function Account:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return 0
end


function Account:deposit(v)
	self.balance = self.balance + v
end

function Account:withdraw(v)
	if v > self.balance then error"insufficient funds" end
	self.balance = self.balance - v
end

--------
--子类
SpecialAccount = Account:new()

s = SpecialAccount:new({limit = 1000})
