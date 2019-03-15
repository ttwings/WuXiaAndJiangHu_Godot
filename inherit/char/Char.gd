extends GameObject

class_name Char

func carry_object(path:String):
	var obj
	obj = load("res:/" + path + ".gd").new()
	print_debug("res:/" + path + ".gd")
	obj.set("environment",self)
    # objs[obj.query(name)] = obj
#    self.set("objects",obj)
	# add("objects",obj.file())
	# 
	objects.append(obj.file())
	print_debug(objects)
	return obj
