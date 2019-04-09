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

########################################  move #####################################
var weight : int = 0
var encumb : int = 0
var max_encumb : int = 0
func query_encumbrance():
	return encumb
func over_encumbranced():
	return encumb > max_encumb

func query_max_encumbrance():
	return max_encumb
	
func set_max_encumbrance(e:int):
	max_encumb = e

func add_encumbrance(w:int):
	encumb += w;
	if( encumb < 0 ):
		print_debug(self,"O encumbrance underflow")
		return
		# log_file("move.bug", sprintf("%O encumbrance underflow.\n", this_object()));
	if( encumb > max_encumb ) :
		this_object().over_encumbrance();
	if( environment() ) :
		environment().add_encumbrance(w);

func over_encumbrance():
#	if( !interactive(this_object()) ) :
#		return;
	tell_object(this_object(), "你的负荷过重了！\n");

func query_weight() :
	return weight
func set_weight(w:int):
	if( !environment() ) :
		weight = w;
		return;
	if( w!=weight ) :
		environment().add_encumbrance( w - weight );
	weight = w;

# This is the "current" weight of an object, which is used on weight
# checking in move().
func weight() :
	return weight + encumb;

func move(dest, silently:int):
	var ob
	var env
	var inv
	var me = this_object()
	var where = environment()
	var exits
	var str1
	var dirs
#	var time = NATURE_D.game_time()
	var i
	var w

	# If we are equipped, unequip first.
	if( query("equipped") && !me.unequip() ):
		return notify_fail("你没有办法取下这样东西。\n");

	# Find the destination ob for moving.
	if( objectp(dest) ):
		ob = dest;
	elif( stringp(dest) ) :
#		call_other(dest, "???");
#		ob = find_object(dest);
		if(!ob) :
			return notify_fail("move: destination unavailable.\n");
	else:
		return notify_fail(sprintf("move: invalid destination %O.\n", dest));

	# Check if the destination ob can hold this object.
	# Beforce checking it, we check if the destination is environment of
	# this_object() (or environment of its environment). If it is, then
	# this could be like get something from a bag carried by the player.
	# Since the player can carry the bag, we assume he can carry the this
	# object in the bag and encumbrance checking is unessessary.
	env = me;
	
	while(environment(env)) :
		env = environment(env)
		if( env==ob ) :
			break;
	if( !env && ob.query_encumbrance() + weight() > ob.query_max_encumbrance() ):
		if( ob==this_object() ):
			return notify_fail(me.name() + "对你而言太重了。\n");
		else:
			return notify_fail(me.name() + "对" + ob.name() +"而言太重了。\n");

	# Move the object and update encumbrance
	w = weight();
	if( environment() ) :
		environment().add_encumbrance( - w);
	move_object(ob);
	if( !me) :
		return 0;
	me.remove_all_enemy();  # by qingyun
	ob.add_encumbrance(w);

	##################################
# 	# If we are players, try look where we are.
# 	if( interactive(me)			# are we linkdead?
# 		&& living(me)			# are we still concious?
# 		&& !me.query_temp("noliving")	# are we still concious?
# 		&& userp(me)			# are we still concious?
# 		&& !silently )
# 	{
# 		if( query("env/brief") )
# 		{
# 			tell_object(me, HIC+environment().query("short") + NOR + " -\n");
# 		}
# 		else
# 		if( query("env/brief1") )
# 		{
# 			str = HIC+environment().query("short") + NOR + " -\n";
# 			inv = all_inventory(environment());
# 	  if (sizeof(inv)<20)
# 			  for(i=0; i<sizeof(inv); i++)
# 			  {
# 				  if( inv[i]==me ) continue;
# 				  if( inv[i].query("no_shown")) continue;
# 				  if( !me.visible(inv[i]) ) continue;
# 				  str += "  " + inv[i].short() + "\n";
# 			  }
# 	  else
# 		str += listob(inv);
# 			 tell_object(me, str);
# 		}
# 		else
# 		if( query("env/brief2") )
# 		{
# 			str = HIC+environment().query("short") + NOR + " -\n";
# 			inv = all_inventory(environment());
# 	  if (sizeof(inv)<20)
# 			  for(i=0; i<sizeof(inv); i++) 
# 			  {
# 				  if( inv[i]==me ) continue;
# 				   if( inv[i].query("no_shown")) continue;
# 				  if( !me.visible(inv[i]) ) continue;
# 				  str += "  " + inv[i].short() + "\n";
# 			  }
# 	  else
# 		str += listob(inv);
# 			if( mapp(exits = environment().query("exits")) )
# 			{
# 				dirs = keys(exits);
# /*				for(i=0; i<sizeof(dirs); i++)
# 					if( (int)env.query_door(dirs[i], "status") & DOOR_CLOSED ) dirs[i] = 0;
# 				dirs -= ({ 0 });
# */
# 				if ( environment().query("outdoors") &&
# 					!present("fire", this_object()) &&
# 					!wizardp(this_object()) &&
# 					((strsrch(time, "亥时") >= 0) ||
# 					 (strsrch(time, "子时") >= 0) ||
# 					 (strsrch(time, "丑时") >= 0) ||
# 					 (strsrch(time, "寅时") >= 0) ))
# 					str += "    天色太黑了，你看不清明显的出路。\n";
# 				else if( sizeof(dirs)==0 )
# 					str += "    这里没有任何明显的出路。\n";
# 				else if( sizeof(dirs)==1 )
# 					str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
# 				else
# 					str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
# 					implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
# 			}
# 			tell_object(me, str);
# 		}
# 		else
# 			command("look");
# 	}

	return 1;
	
#######################################   ##########################

func set_dbase(dbase):
	dbase = dbase

func get_dbase():
	return dbase	

func add_action(fun:String,key:String,ob=self):
	actions[key] = fun
	pass	
	
		
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
#func move(to:GameObject):
#	to.add("objects",self)
#	self.add("environment",to.file_name())
#	pass	
	
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
	var party;
	var guard
	var degree
	var party_title
	var title
	var nick
	var string
	var str1
	var mask;
#
#	if( !stringp(string = query("short")) ):
#		string = name(raw) + "(" + capitalize(query("id")) + ")";
#
#	if( !this_object().is_character() ) :
#		return string;
#
#	if (!raw) :
#		if (query_temp("pending/exercise") != 0):
#			return name() + "正坐在地下修炼内力。";
#		elif (query_temp("pending/respirate") != 0):
#			return name() + "正坐在地下吐纳炼精。";
#	}
#
#        if( !raw && sizeof(mask = query_temp("apply/short")) ):
#                str = str(mask[sizeof(mask)-1]);
##	if( !raw && stringp(str1 = (string)query_temp("apply/short")) ) {
##		str = (string)mask[sizeof(mask) - 1];
##		return (string)query_temp("apply/short");
##		if (stringp(str1))
##		  	str += str1;
##	}
#	else: 
#		if( stringp(nick = query("nickname")) ):
#			str = sprintf("「%s」%s", nick, str);
#
#		if( stringp(title = query("title")) ) :
#			# 叛师过的无门派人士改称隐士。Modified by Spacenet@FXLT
#			if (title == "普通百姓" && query("betrayer")):
#				title = "隐士";
#			str = sprintf("%s%s%s", title,(nick?"":" "), str);
#		if ( mapp(party = query("party")) ) :
#			party_title = party["party_name"] + party["rank"];
#			str=sprintf("%s%s%s%s", party_title,(title?"":""),(nick?"":" "), str);
#		if ( stringp(degree = query("degree")) ) :
#			str = sprintf("%s%s%s%s%s",degree,(party_title?"":""),(title?"":""),(nick?"":" "), str);
#		if ( stringp(guard = query("guard")) ) :
#			str = sprintf("%s%s%s%s%s%s",guard,(degree?"":""),(party_title?"":""),(title?"":""),(nick?"":" "), str);
#
#	if( !raw ) :
#		if( this_object().is_ghost() ) :
#			str = HIB "(鬼气) " NOR + str;
#		# if( query_temp("netdead") ) :
#		# 	str += HIG" <断线中>" NOR;
#		# if( in_input() ) str += HIC" <输入文字中>" NOR;
#		# if( in_edit() ) str += HIY" <编辑档案中>" NOR;
#		# if( query_temp("boss_screen") ) :
#		# 	str += HIG" <逃避老板中>" NOR;
#		if( query_temp("bixie/cimu") ) :
#			str += HIR + " <失明中>" + NOR;
#		if( query_temp("noliving/sleeped") ) :
#			str += HIR + " <睡梦中>"  + NOR;
#		if( query_temp("noliving/fakedie") ) :
#			str += HIR + " <装死中>"  + NOR;
#		if( query_temp("noliving/jingzuo") ) :
#			str += HIR + " <静坐中>"  + NOR;
#		if( query_temp("noliving/journey") ) :
#			str += HIR + " <旅途中>"  + NOR;
#		if( query_temp("noliving/unconcious") ):
#			str += HIR + " <昏迷不醒>" +  NOR;
#		if( interactive(this_object()) && query_idle(this_object())>120):
#			str += HIM +  " <发呆中>"  + NOR;
#		if( !living(this_object()) ):
#			str += HIR + query("disable_type") + NOR;
#	return str;
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

func intp(i):
	return i is int
	
func undefinedp(u):
	return !u		
	
func objectp(ob):
	return true
		
func keys(d:Dictionary):
	return d.keys()

# todo test
func sprintf(string,arg1=null,arg2=null):
	string.format(arg1,arg2)

# call out
func call_out(func_name,time):
	var timer = get_tree().create


func create():
	pass	
	
	
	