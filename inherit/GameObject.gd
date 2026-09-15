#extends Node

class_name GameObject

# 信号：消息发送（供 UI 订阅显示）
signal message_sent(msg: String)

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
	set_attr("uid",uid)		


func query_default_object():
	return default_ob

func set_default_object(ob):
	if( !getuid() ) :
		setuid(getuid());
	default_ob = ob;
	ob.add("no_clean_up", 1);

func set_attr(key:String,value):
	dbase[key] = value
	
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
	dbase.erase(key)

func delete_temp(key):
	if( !mapp(tmp_dbase) ) :
		return 0;
	tmp_dbase.erase(key)

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

func set_dbase_dict(dbase):
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
	ob.set_attr("destruct",true)
	# GameObject 不是 Node，不能调用 queue_free()
	# 标记为已销毁，由环境/管理器负责清理
	pass


func sizeof(array):
	if array is Array :
		return array.size()
	else:
		return -1	

# 返回自身（兼容 MUD 代码中的 this_object() 调用）
func this_object():
	return self

# 返回当前玩家（兼容 MUD 代码中的 this_player() 调用）
func this_player():
	return self

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
	# 发送消息，通过信号通知 UI
	message_sent.emit(msg)
	pass
	
func say(msg):
	message_sent.emit(str(msg))
		
func command(cmd:String):
	# 通过 COMMAND_D 分发命令
	var parts = cmd.split(" ", false, 1)
	var verb = parts[0] if parts.size() > 0 else ""
	var arg = parts[1] if parts.size() > 1 else ""
	if verb == "":
		return
	COMMAND_D.do_command(self, verb, arg)
		
func error(e):
	print_debug(str(e))

func notify_fail(message:String):
	message_sent.emit(message)
	return message

# 各类信息发送
func message_vision(message:String,me,ob=null):
	var msg = message
	var N = ""
	var n = ""
	if me and me.has_method("query"):
		N = str(me.query("name"))
	if ob and ob.has_method("query"):
		n = str(ob.query("name"))
	msg = msg.replace("$N",N)
	msg = msg.replace("$n",n)
	# 通知我
	if me and me.has_method("message_sent"):
		me.message_sent.emit(msg)
	# 通知对方
	if ob and ob.has_method("message_sent"):
		ob.message_sent.emit(msg)
	return msg

func tell_object(who,msg:String):
	# 向指定对象发送消息
	if who and who.has_method("message_sent"):
		who.message_sent.emit(msg)
	else:
		print_debug(msg)
	
############################## Move ###########################################

var weight = 0;
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
	return weight

func set_weight(w):
	if( !environment() ) :
		weight = w;
		return;
	if( w!=weight ) :
		environment().add_encumbrance( w - weight );
	weight = w;

# # This is the "current" weight of an object, which is used on weight
# # checking in move().
func query_total_weight() :
	return weight + encumb;

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
# 	if( !env && (int)ob.query_encumbrance() + query_total_weight()
# 		> (int)ob.query_max_encumbrance() )
# 	{
# 		if( ob==this_object() )
# 			return notify_fail(me.name() + "对你而言太重了。\n");
# 		else
# 			return notify_fail(me.name() + "对" + ob.name() +"而言太重了。\n");
# 	}

	# Move the object and update encumbrance
	w = query_total_weight();
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
	set_attr("name", name);
	set_attr("id", id);
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
	# 将对象移动到目标环境中
	# GameObject 不是 Node，通过 environment 记录所在容器
	pass
	
################################ tools #############################
func remove_call_out(func_name):
	pass
	
func call_out(func_name, second):
	pass		
	
func new_ob(file):
	var ob
	ob = load(file).new()
	return ob
