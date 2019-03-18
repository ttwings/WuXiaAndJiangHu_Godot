extends GameObject

class_name Char

var skills = {}
var map_skills = {}
var prepare_skills = {}

func carry_object(path:String):
	var obj
	obj = load("res:/" + path + ".gd").new()
	
	obj.set("environment",self)
    # objs[obj.query(name)] = obj
#    self.set("objects",obj)
	# add("objects",obj.file())
	# 
	objects[obj.file_name()]=1
#	obj.add("objects",path)
#	print_debug(obj.file())
	return obj


func set_skill(key:String,value):
	skills[key] = value

func map_skill( key:String,value):
	map_skills[key] = value
	
func prepare_skill(key:String,value):
	prepare_skills[key] = value
	
func create_family(key:String,lvl:int,nack_name:String):
	family.name = key
	family.lvl =  lvl
	family.nack_name = nack_name


func query_skill(skill:String,key:String):
	if skills.has(skill) and skills[skill].has(key):
		return skills[skill][key]
	else:
		return false
		
func _init():
	pass		