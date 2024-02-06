-- Vector3 class definition
Vector3 = {
    _type = "Vector3",
    x = 0,
    y = 0,
    z = 0
}

-- Constructor
function Vector3:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

-- Methods
function Vector3:set(x, y, z)
    self.x = x or 0
    self.y = y or 0
    self.z = z or 0
end

function Vector3:print()
    print("Vector3:", self.x, self.y, self.z)
end

print("Maths module initialized.")

return 25
