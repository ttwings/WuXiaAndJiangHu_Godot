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

func _init():
	create()
	pass

##################################################  dbase #################################	

func getuid(ob=self):
	return ob.get_instance_id()
	
func setuid(uid):
	set("uid",uid)		

var dbase = {"objects" : {}}
var tmp_dbase = {}

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
	return dbase[key]

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
		return 0		
		
func query(key:String):
	if	dbase.has(key) :
		return get_dbase()[key]
	else:
		return 0		
	pass

func query_entire_dbase():
	return dbase;

func query_entire_temp_dbase():
	return tmp_dbase;

func set_dbase(dbase):
	dbase = dbase

func get_dbase():
	return dbase	
	
#############################################################		
func setup():
	setuid(getuid())
	pass


	
# 销毁这件物品	
func destruct(ob=self):
	# TODO
	ob.set("destruct",true)
	ob.queue_free()
#	ob = null
	pass	


func sizeof(array):
	return array.size()	

func this_object(ob=self):
	return ob	

# todo	
func environment(ob=self):
	return ob.query_temp("environment")

func strsrch(string1,string2):
	var result = string1.find(string2)
	print_debug(result)
	return result

# 返回物品
# todo
func present(name:String,to):
	to.add("present",name)

func is_character():
	return false
			
func random(n:int):
	return randi()%n
	
func dir(ob = self):
	return ob.get_script().get_path().get_base_dir() + "/"	

func file_name(ob = self):
	return ob.get_script().get_path()
	
func arrayp(a):
	return a is Array	
	
func mapp(d):
	return d is Dictionary
	
func stringp(s):
	return s is String	

func intp(i):
	return i is int
	
func undefinedp(u):
	return !u		
	
func objectp(ob):
	return true
	
# todo	
func userp(ob):
	return false
		
func functionp(fun,ob=self):
	return ob.has_method(fun)		
	
func evaluate(interrupt,fun,args=[],ob=self):	
	if ob.has_method(fun) :
		call(fun,args)
		
func keys(d:Dictionary):
	return d.keys()

# todo test
func sprintf(string,arg1=null,arg2=null,arg3=null,arg4=null):
	string.format(arg1,arg2,arg3,arg4)
	print_debug(string)

func create():
	pass	
		
######################################### message #######################
func message(version:String,msg:String,frome=null,to=null):
	print_debug(version,msg,frome.name(),to.name())
	pass
	
func say(msg):
	print_debug(msg)		
	
func command(cmd:String):
	var array = cmd.split(" ")
	var command = array[0]
	var args = array.remove(0)
	if functionp(command) :
		evaluate(command,args)	
		
func error(e):
	print_debug(str(e))

func notify_fail(message:String):
	print_debug(message)
	return message
	pass	

# 各类信息发送
func message_vision(message:String,ob):
	# TODO
#	print_debug(ob.query("name") + message)
	var msg = message
	var str_n = ob.query("name")
	msg = msg.replace("$N",str_n)
	# emit_signal("message_ob_sended",msg,ob)
	return msg

func tell_object(who,msg:String):
	#  TODO
	who.add("msg",msg)
	print_debug(who.name(),msg)		