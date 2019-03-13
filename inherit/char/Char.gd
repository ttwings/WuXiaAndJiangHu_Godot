extends GameObject

class_name Char

func carry_object(path:String):
	var obj
	obj = load("res:/" + path + ".gd").new()
	obj.set("environment",self)
    # objs[obj.query(name)] = obj
#    self.set("objects",obj)
	return obj