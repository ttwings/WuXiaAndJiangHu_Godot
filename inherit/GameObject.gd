#extends Node

class_name GameObject
# const color -----------------------------------

# 消息信号 - 供 UI 层监听显示命令执行结果
signal message_sent(msg: String)

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


var dbase = {"objects" : {}}
var tmp_dbase = {}
var default_ob;

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


func query_default_object():
	return default_ob

func set_default_object(ob):
	if( !getuid() ) :
		setuid(getuid());
	default_ob = ob;
	ob.add("no_clean_up", 1);

func set(key:StringName,value) -> void:
	dbase[str(key)] = value
	
func add(key,value):

	if dbase.has(key):
		if dbase[key] is int:
			dbase[key] = dbase[key] + value
		elif dbase[key] is Array:
			dbase[key].append(value)
		elif dbase[key] is DirAccess:
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

# TODO 判断对象是否还在
func living(ob=self):
	return is_instance_valid(ob)
	
# 销毁这件物品	
func destruct(ob=self):
	# TODO
	ob.set("destruct",true)
	ob.queue_free()
#	ob = null
	pass	


func sizeof(array):
	if array is Array :
		return array.size()
	else:
		return -1	

func this_object(ob = null):
	if ob == null:
		return self
	return ob	

# todo	
func environment(ob = null):
	if ob == null:
		ob = self
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
	# 通过脚本继承链判断是否为 Char（避免 Char extends GameObject 的循环依赖）
	var s = get_script()
	while s:
		if s.resource_path == "res://inherit/Char.gd":
			return true
		s = s.get_base_script()
	return false

# MUD兼容：返回当前交互玩家（Godot中无此概念，返回null由调用方处理）
func this_player():
	return null
			
func random(n:int):
	return randi()%n
	
func dir(ob = null):
	if ob == null:
		ob = self
	return ob.get_script().get_path().get_base_dir() + "/"	

func file_name(ob = null):
	if ob == null:
		ob = self
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
	
func evaluate(fun,args=[],ob=self):	
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
func message(msg:String,frome=null,to=null):
	print_debug(msg,frome.name(),to.name())
	pass
	
func say(msg):
	print_debug(msg)		
	
func command(cmd:String):
	# 解析命令：动词 + 参数
	var parts := cmd.strip_edges().split(" ", false, 1)
	var verb := parts[0] if parts.size() > 0 else ""
	var arg := parts[1] if parts.size() > 1 else ""

	if verb == "":
		return

	# 移动命令简写：直接输入方向
	if COMMAND_D and COMMAND_D.is_move_command(verb) and arg == "":
		# 方向命令直接触发移动
		_do_move(verb)
		return

	# 通过命令守护进程查找处理方法
	var handler := ""
	if COMMAND_D:
		handler = COMMAND_D.find_command(verb)

	if handler != "" and self.has_method(handler):
		# 优先调用角色上定义的处理方法
		self.call(handler, arg)
	else:
		# 回退：如果对象自身有同名方法，直接调用
		if self.has_method(verb):
			self.call(verb, arg)
		else:
			print_debug("command: 未找到命令处理 '%s' (参数: %s)" % [verb, arg])

# 移动命令处理 - 由房间出口按钮或方向命令触发
func _do_move(direction: String) -> void:
	# 将简写方向转为标准方向名
	var dir_map := {
		"n": "north", "s": "south", "e": "east", "w": "west",
		"nu": "north", "na": "south", "dong": "east", "xi": "west",
		"shang": "up", "xia": "down", "jin": "in", "chu": "out",
	}
	var dir := dir_map.get(direction, direction)

	var env = environment()
	if env == null or not env is Room:
		return
	var exits = env.query("exits")
	if exits and exits is Dictionary and exits.has(dir):
		var dest_path: String = exits[dir]
		var dest = Global.load_room(dest_path + ".gd") if Global else load(dest_path + ".gd").new()
		self.move(dest)
	else:
		print_debug("无法向 %s 方向移动" % dir)
		
func error(e):
	print_debug(str(e))

func notify_fail(message:String):
	print_debug(message)
	# 广播失败消息，供 UI 层显示
	if self.has_signal("message_sent"):
		self.emit_signal("message_sent", message)
	return message
	pass	

# 各类信息发送
func message_vision(message:String,me,ob=null):
	# TODO
#	print_debug(ob.query("name") + message)
	var msg = message
	var N
	var n 
	N = me.query("name")
	n = ob.query("name") if ob else ""
	msg = msg.replace("$N",N)
	msg = msg.replace("$n",n)
	# 自动向 actor 发送消息，供 UI 显示
	tell_object(me, msg)
	# emit_signal("message_ob_sended",msg,ob)
	return msg

func tell_object(who,msg:String):
	#  TODO
	who.add("msg",msg)
	print_debug(who.name(),msg)
	# 广播消息，供 UI 层显示
	if who and who.has_signal("message_sent"):
		who.emit_signal("message_sent", msg)
		# 同时从发送者也广播（便于统一监听）
		if self != who and self.has_signal("message_sent"):
			self.emit_signal("message_sent", msg)
	
############################## Move ###########################################

var obj_weight = 0;
var encumb = 0
var max_encumb = 0;
 # func listob(object *inv);
func query_encumbrance():
	return encumb;
func over_encumbranced():
	return encumb > max_encumb;

func query_max_encumbrance():
	return max_encumb;
func set_max_encumbrance(e:int):
	max_encumb = e;
func add_encumbrance(w:int):
	encumb += w;
	if( encumb < 0 ):
		sprintf("%O encumbrance underflow.\n", this_object())
	if( encumb > max_encumb ):
		this_object().over_encumbrance();
	if( environment() ):
		environment().add_encumbrance(w);

func over_encumbrance():
#	if( !interactive(this_object()) ) :
#		return;
	tell_object(this_object(), "你的负荷过重了！\n");

func query_weight():
	return obj_weight

func set_weight(w):
	if( !environment() ) :
		obj_weight = w;
		return;
	if( w!=obj_weight ) :
		environment().add_encumbrance( w - obj_weight );
	obj_weight = w;

# # This is the "current" weight of an object, which is used on weight
# # checking in move().
func weight() :
	return obj_weight + encumb;

func move(dest, silently=1):
	var ob
	var env
	var inv
	var me = this_object()
	var where = environment();
	var exits;
#	string str, *dirs, time = NATURE_D.game_time();
	var i
	var w;

	# If we are equipped, unequip first.
	if( query("equipped") && !me.unequip() ):
		return notify_fail("你没有办法取下这样东西。\n");

	# Find the destination ob for moving.
	if( objectp(dest) ):
		ob = dest;
	elif( stringp(dest) ):
#		call_other(dest, "???");
		ob = find_object(dest);
		if(!ob):
			return notify_fail("move: destination unavailable.\n");
	else:
		return notify_fail(sprintf("move: invalid destination %O.\n", dest));

# 	# Check if the destination ob can hold this object.
# 	# Beforce checking it, we check if the destination is environment of
# 	# this_object() (or environment of its environment). If it is, then
# 	# this could be like get something from a bag carried by the player.
# 	# Since the player can carry the bag, we assume he can carry the this
# 	# object in the bag and encumbrance checking is unessessary.
# 	env = me;
# 	while(env = environment(env)) if( env==ob ) break;
# 	if( !env && (int)ob.query_encumbrance() + weight()
# 		> (int)ob.query_max_encumbrance() )
# 	{
# 		if( ob==this_object() )
# 			return notify_fail(me.name() + "对你而言太重了。\n");
# 		else
# 			return notify_fail(me.name() + "对" + ob.name() +"而言太重了。\n");
# 	}

	# Move the object and update encumbrance
	w = weight();
	if( environment() ):
		environment().add_encumbrance( - w);
	move_object(ob);
	if( !me):
		return 0;
	me.remove_all_enemy();  # by qingyun
	ob.add_encumbrance(w);
	
	
	
############################## Name ##########################################
func set_name_cn(value1:String,value2:String):
	dbase.name = value1
	dbase.id = value2

var my_id
func set_name(name,id):
	set("name", name);
	set("id", id);
	my_id = id;

func name():
	var st
	var mask;
	mask = query_temp("apply/name")
	st = query("name")
	if( stringp(st) ):
		return st;
	else:
		return file_name(this_object());	
		
func base_name(ob=self):
	return file_name(ob)	
	
func find_object(ob=self):
	return file_name(ob)
	
func move_object(ob=self):
	ob.free()		
	
################################ tools #############################
func remove_call_out(func_name):
	pass
	
func call_out(func_name, second):
	pass		
	
func new_ob(file):
	var ob
	ob = load(file).new()
	return ob
