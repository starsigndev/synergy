Node3D = {

type = "Node3D",
rotation = 0,
position =0,
scale =0,

}

function Node3D:new(o)

    o = o or {}
    setmetatable(o,self)
    self.__index = self
    self.type = "Node3D"

end 

function Node3D:debug()

    print("Node3D Debug Output.");

end 

Node3DMetaTable = {}
Node3DMetaTable.__index = Node3D
setmetatable(Node3D, Node3DMetaTable)

print("Registered System.Node")
