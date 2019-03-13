extends Resource

class_name GameObject
# color
const NOR = "[/color]"
const BLK = "[color=#000000]"
const RED = "[color=#ff0000]"
const GRN = "[color=#00ff00]"
const YEL = "[color=#ffff00]"
const BLU = "[color=#0000ff]"
const MAG = "[color=#ff00ff]"
const CYN = "[color=#00ffff]"
const WHT = "[color=#ffffff]"   
const HIR = "[color=#ff0000]"
const HIG = "[color=#00ff00]"
const HIY = "[color=#ffff00]"
const HIB = "[color=#44cef6]"
const HIM = "[color=#ff00ff]"
const HIC = "[color=#177cb0]"
const HIW = "[color=#e9e7ef]"
const BRED = "[color=#ff2121]"
const BGRN = "[color=#00e500]"
const BYEL = "[color=#ffb61e]"
const BBLU = "[color=#4b5cc4]"
const BMAG = "[color=#8d4bbb]"
const BCYN = "[color=#1685a9]"
const HBRED = "[color=#ff2121]"
const HBGRN = "[color=#40de5a]"
const HBYEL = "[color=#eacd76]"
const HBBLU = "[color=#3b2e7e]"
const HBMAG = "[color=#815463]"
const HBCYN = "[color=#00e09e]"
const HBWHT = "[color=#f0fcff]"


# 基本属性
#var name_cn
#var weight

var dbase = {}
var temp_dbase = {}
var skills = {}
var map_skills = {}
var prepare_skills = {}
# 门派
var family = {}
# 携带的物品
var objs = {}

func set_name_cn(value1:String,value2:String):
	dbase.name = value1
	dbase.id = value2
	
func name():
	return dbase.name
			
func set_weight(value:int):
	dbase.weight = value

func set(key:String,value):
	dbase[key] = value
	
func add(key:String,value):
	dbase[key] = dbase[key] + value	

func add_temp(key:String,value):
	# temp_dbase[key] = temp_dbase[key] + value
	set_temp(key,query(key) + value)
	
func set_temp(key:String,value):
	temp_dbase[key] = value
	
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

# 实例化物品	
# TODO
#func carry_object(path:String):
#	var obj = get_node(path)
#	objs.append(obj)

func query_skill(skill:String,key:String):
	if skills.has(skill) and skills[skill].has(key):
		return skills[skill][key]
	else:
		return false
		
func query_temp(key:String):
	if temp_dbase.has(key) :
		return temp_dbase[key]
	else:
		return false		
		
func query(key:String):
	if	dbase.has(key) :
		return dbase[key]
	else:
		return ""		
	pass

# UID todo
var uid = 0	
func getuid():
	return uid + 1

func setuid(id):
	uid = id		
		
func setup():
	setuid(getuid())
	
func message_vision(message:String,ob:GameObject):
	# TODO
	print_debug(ob.query("name") + message)
	var msg = ""
	return msg

func tell_object(who:GameObject,msg:String):
	#  TODO
	print_debug(who.name,msg)	
	
# 销毁这件物品	
func destruct(ob:GameObject):
	# TODO
#	queue_free()
	pass	

#
var actions = {}	
func add_action(fun:String,id:String):
	actions[id] = fun
	pass	
	
# # todo	
func this_player():
 	var player = self
 	return player	

func this_object():
	return self	
# todo
func new_ob(path:String):
	var obj
	obj = load("res:/" + path + ".gd").new()
	obj.set_temp("environment",self.id)
	return obj
	
func environment():
	return query_temp("environment")

# todo
func move(to:GameObject):
	to.add("objects",self)
	self.add("environment",to)
	pass	
	

		
func get_ob_dir(ob:GameObject):
#	print_debug("test" + resource_path)
	# return like "res://xxx/xxx"
	return ob.get_script().get_path().get_base_dir()
#	print_debug(get_parent().filename)		

func get_ob_path(ob:GameObject):
	return ob.get_script().get_path().get_basename()