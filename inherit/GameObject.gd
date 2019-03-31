#extends Node

class_name GameObject
# const color -----------------------------------
const NOR = "[/color]"
const BLK = "[color=#000000]"
const RED = "[color=#ff0000]"
const GRN = "[color=#00ff00]"
const YEL = "[color=#ffff00]"
const BLU = "[color=#0000ff]"
const MAG = "[color=#ff0.0ff]"
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
var __DIR__ = dir()
var __FILE__ = file_name()
# 用信号处理各类信息
signal message_player_sended(msg,player)
signal message_ob_sended(msg,ob)
signal message_room_sended(msg,room)
# 基本属性
#var name_cn
#var weight
var dbase = {"objects" : {}}
var temp_dbase = {}

#TODO call func
var actions = {}

func _init():
	create()
	pass

func set_dbase(dbase):
	dbase = dbase

func get_dbase():
	return dbase	

func add_action(fun:String,key:String,ob=self):
	actions[key] = fun
	pass	
	
func set_name_cn(value1:String,value2:String):
	dbase.name = value1
	dbase.id = value2

func set_name(value1:String,value2:String):
	dbase.name = value1
	dbase.id = value2

	
func name():
	return dbase.name
			
func set_weight(value:int):
	dbase.weight = value

func set(key:String,value):
	dbase[key] = value
	
func add(key,value):
	# var dbase = get_dbase()
	if key == "objects":
#		if dbase[key] is Dictionary:
#			if dbase[key].has(value):
##				dbase[key][value] = dbase[key][value] + 1
#				dbase[key][value] =  1
#			else:
#				dbase[key][value] =  1
#		else:
#			dbase[key] = int(dbase[key]) + int(value)
		if dbase.has(key):
			dbase[key][value] = dbase[key][value] + 1
		else:
			dbase[key] = {}
			dbase[key][value] = 1
#		dbase[key] = value
	else:
		dbase[key] = dbase[key] + value	

func add_temp(key:String,value):
	temp_dbase[key] = temp_dbase[key] + value
	# set_temp(key,query(key) + value)
	
func set_temp(key:String,value):
	temp_dbase[key] = value
		
func query_temp(key:String):
	if temp_dbase.has(key) :
		return temp_dbase[key]
	else:
		return ""		
		
func query(key:String):
	if	dbase.has(key) :
		return get_dbase()[key]
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

# 各类信息发送
func message_vision(message:String,ob:GameObject):
	# TODO
#	print_debug(ob.query("name") + message)
	var msg = message
	var str_n = ob.query("name")
	msg = msg.replace("$N",str_n)
	# emit_signal("message_ob_sended",msg,ob)
	return msg

func tell_object(who:GameObject,msg:String):
	#  TODO
	print_debug(who.name,msg)	
	
# 销毁这件物品	
var destruct = false
func destruct(ob=self):
	# TODO
	destruct = true
	ob.queue_free()
#	ob = null
	pass	
	
func random(n:int):
	return randi()%n

func this_object():
	return self	
func this_player():
	pass	
# todo
func new_ob(path:String):
	var obj
	if path.find("res:/")>0 and path.find(".gd",-1)>0 :
		obj = load(path).new() 
	else:
		obj = load("res:/" + path + ".gd").new()
	obj.set_temp("environment",self)
	return obj
	
func environment(ob=self):
	return ob.query("environment")
	# return query_temp("environment")

# todo
func move(to:GameObject):
	to.add("objects",self)
	self.add("environment",to.file_name())
	pass	
	
func move_object(ob=self,dest=self):
	dest.add("objects",ob.file_name())
		
func dir(ob = self):
	return ob.get_script().get_path().get_base_dir() + "/"	

func file_name(ob = self):
	return ob.get_script().get_path()

func strsrch(string1,string2):
	var result = string1.find(string2)
	print_debug(result)
	return result

# 返回物品
# todo
func present(name:String,to):
	# var objects = query("objects")
	# if objects.has(name):
	# 	return objects[name]
	# return null
	to.add("present",name)

# yield(get_tree().create_timer(1), 'timeout')
func start_busy(time):
#	yield,"timeout")
	pass

func notify_fail(message:String):
	print_debug(message)
	return message
	pass	

func create():
	pass	