# extends GameObject

class_name Item

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

#
#// item.c
#
##include <dbase.h>
##include <move.h>
##include <name.h>
#
#inherit F_CLEAN_UP;
#inherit F_DBASE;
#inherit F_MOVE;
#inherit F_NAME;
#
#void setup()
#{
#	seteuid(getuid());
#	set("weight",100);
#}

var __DIR__ = dir()
var __FILE__ = file_name()


func setup():
	setuid(getuid())
	set("weight",100)

###########
#TODO call func
var actions = {}

func _init():
	create()
	pass
	
func getuid(ob=self):
	return ob.get_instance_id()

func geteuid(ob=self):
	return ob.get_instance_id()	
	
func setuid(uid):
	set("uid",uid)			



######################################## F_DBASE #####################################

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


########################################  F_MOVE #####################################
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

func move(dest, silently:int = 1):
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
	ob.add_encumbrance(w);

	return 1;		


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

	return string
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


