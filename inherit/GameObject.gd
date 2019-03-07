extends Node

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
var name_cn
var weight

var attributes = {}
var temps = {}
var skills = {}
var map_skills = {}
var prepare_skills = {}
# 门派
var family = {}
# 携带的物品
var objs = []
func _ready():
	set("name","张三")
	print(query("name"))

func set_name_cn(value1:String,value2:String):
	attributes.name = value1
	attributes.id = value2
	
func name():
	return attributes.name
			
func set_weight(value:int):
	weight = value

func set(key:String,value):
	attributes[key] = value
	
func add(key:String,value):
	attributes[key] += value	
	
func set_temp(key:String,value):
	temps[key] = value
	
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
func carry_object(path:String):
	var obj = get_node(path)
	objs.append(obj)

func query_skill(skill:String,key:String):
	if skills[skill] and skills[skill][key]:
		return skills[skill][key]
	else:
		return false
		
func query_temp(temp:String):
	if temps[temp] :
		return temps[temp]
	else:
		return false		
		
func query(key:String):
	if	attributes[key] :
		print(attributes[key])
		return attributes[key]
	else:
		return false		
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
	var msg = ""
	return msg

func tell_object(who:GameObject,msg:String):
	#  TODO
	print(who.name,msg)	
	
# 销毁这件物品	
func destruct(ob:GameObject):
	# TODO
	pass	
	