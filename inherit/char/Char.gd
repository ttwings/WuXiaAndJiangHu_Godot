extends GameObject

class_name Char


# -------------- props ----------
var max_food_capacity
var max_water_capacity
func max_food_capacity():
	max_food_capacity = query("str") * 5 + 300
	return max_food_capacity

func max_water_capacity():
	max_food_capacity = query("int") * 5 + 300
	return max_food_capacity
	
var skills = {}
var test_skills = {}
var map_skills = {}
var prepare_skills = {}

func set_skill(key:String,value):
#	if !skills:skills={}
	skills[key] = value

func get_skill(key:String):
	return skills[key]

func map_skill( key:String,value):
#	if !map_skills:map_skills={}
	map_skills[key] = value
	
func prepare_skill(key:String,value):
#	if !prepare_skills:prepare_skills={}
	prepare_skills[key] = value

func query_skill(skill:String,key:String):
	if skills.has(skill) and skills[skill].has(key):
		return skills[skill][key]
	else:
		return false
		
		

# ---------------------------- family ----------------------	
var family = {}
func create_family(key:String,lvl:int,nack_name:String):
	family.name = key
	family.lvl =  lvl
	family.nack_name = nack_name

func carry_object(path):
	# if obj
	var ob = load("res:/" + path + ".gd").new()
#	self.dbase.objects[path] = obj
	self.add("objects",path)
	self.add_temp("objects",ob)
#	if ob is Weapon :
#		self.set("weapon",ob)
	print_debug(self.query("objects"))
	pass
	
#func create():
#	pass
#
func _init():
#	skills = {}
#	test_skills = {}
#	map_skills = {}
#	prepare_skills = {}
#	family = {}
	create()
	pass	