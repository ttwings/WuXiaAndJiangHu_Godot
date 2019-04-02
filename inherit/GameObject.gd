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
var tmp_dbase = {}

#TODO call func
var actions = {}

func _init():
	create()
	pass
	
func getuid():
	return get_instance_id()
	
func setuid(uid):
	set("uid",uid)		
##################################################  dbase #################################
var default_ob;

func query_default_object():
	return default_ob

func set_default_object(ob):
	if( !getuid() ) :
		setuid(getuid());
	default_ob = ob;
	ob.add("no_clean_up", 1);

func set(key:String,value):
	dbase[key] = value
	
func add(key,value):

	if dbase.has(key):
		if dbase[key] is int:
			dbase[key] = dbase[key] + value
		elif dbase[key] is Array:
			dbase[key].append(value)
		elif dbase[key] is Directory:
			dbase[key][value] = dbase[key][value] + 1
	else:
		dbase[key] = value	

#func add(prop:String,data):
#	# mixed old;
#	var old
#	if( !mapp(dbase) || !(old = query(prop, 1)) ):
#		return set(prop, data);
#
#	# if( functionp(old) )
#	# 	error("dbase: add() - called on a function type property.\n");
#	return set(prop, old + data);

func add_temp(prop:String, data):
	var old;
	old = query_temp(prop)
	# if( !mapp(tmp_dbase) || !(old = query_temp(prop, 1)) )
	if( !mapp(tmp_dbase) || !old ):
		return set_temp(prop, data);
	# if( functionp(old) )
	# 	error("dbase: add_temp() - called on a function type property.\n");
	return set_temp(prop, old + data);

func delete(key):
	if( !mapp(dbase) ) :
		return 0;
	dbase.ease(key)

func delete_temp(key):
	if( !mapp(tmp_dbase) ) :
		return 0;
	tmp_dbase.ease(key)

func set_temp(prop:String,data):
	if( !mapp(tmp_dbase) ):
		tmp_dbase = {};
	tmp_dbase[prop] = data
		
func query_temp(key:String):
	if tmp_dbase.has(key) :
		return tmp_dbase[key]
	else:
		return ""		
		
func query(key:String):
	if	dbase.has(key) :
		return get_dbase()[key]
	else:
		return ""		
	pass

func query_entire_dbase():
	return dbase;

func query_entire_temp_dbase():
	return tmp_dbase;

########################################   ##########################

func set_dbase(dbase):
	dbase = dbase

func get_dbase():
	return dbase	

func add_action(fun:String,key:String,ob=self):
	actions[key] = fun
	pass	
	

func set_weight(value:int):
	dbase.weight = value
	
		
func setup():
	# setuid(getuid())
	pass

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


func sizeof(array):
	return array.size()	

func this_object():
	return self	

var player
#func set_player(user:Char):
#	player = user
func this_player():
	return player
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
########################################  name ####################
func set_name_cn(value1:String,value2:String):
	dbase.name = value1
	dbase.id = value2

var my_id
func set_name(name,id):
	set("name", name);
	set("id", id);
	my_id = id;

func name(raw=1):
	var st
	var mask;
	mask = query_temp("apply/name")
	if( !raw && sizeof(mask) ):
		return mask[sizeof(mask)-1];
	else:
		st = query("name")
		if( stringp(st) ):
			return st;
		else:
			return file_name(this_object());
func short(raw=1):
	pass

func long(raw=1):
	var st
	var extra
	var mask;
	mask = query_temp("apply/long")
	if( !raw && sizeof(mask) ):
		st = mask[sizeof(mask)-1];
	elif( !stringp(query("long")) ):
		st = short(raw) + "。\n";
	
	extra = this_object().extra_long()
	if( stringp(extra) ):
		st += extra;

	return st;

func extra_long():
	# todo
	pass	

###################################### F clean up  ###########################
#func clean_up():
#	var inv;
#	var i;
#
#	if( !clonep() && this_object().query("no_clean_up") ) :
#		return 1;
#
#	if(interactive(this_object())) :
#		return 1;
#
#	# If we are contained in something, let environment do the clean
#	# up instead of making recursive call. This will prevent clean-up
#	# time lag.
#
#	if(environment()) :
#		return 1;
#
#	inv = all_inventory();
#	# for(i=sizeof(inv)-1; i>=0; i--)
#	for i in sizeof(inv):
#		if(interactive(inv[i])) :
#			return 1;
#
#	destruct(this_object());
#	return 0;


# ----------------------------------------- tools ------------------
# func delete(key):
# 	dbase.erase(key)

# func delete_temp(key):
# 	temp_dbase.erase(key)	
			
func random(n:int):
	return randi()%n
	
func dir(ob = self):
	return ob.get_script().get_path().get_base_dir() + "/"	

func file_name(ob = self):
	return ob.get_script().get_path()
	
func mapp(d):
	return d is Dictionary
	
func stringp(s):
	return s is String	

	
func undefinedp(u):
	return !u		
	
func keys(d:Dictionary):
	return d.keys()
func create():
	pass	