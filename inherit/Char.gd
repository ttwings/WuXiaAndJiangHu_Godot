extends GameObject

class_name Char
#pragma save_binary

#include <action.h>
#include <ansi.h>
#include <command.h>
#include <condition.h>
#include <dbase.h>
#include <move.h>
#include <name.h>
#include <skill.h>
#include <team.h>
#include <user.h>
#include <combat.h>

# inherit F_ACTION;
# inherit F_ALIAS;		X 机器人程序相关,不需要
# inherit F_APPRENTICE;
# inherit F_ATTACK;
# inherit F_ATTRIBUTE;
# inherit F_COMMAND;
# inherit F_CONDITION;
# inherit F_DAMAGE;
# inherit F_DBASE;
# inherit F_EDIT;
# inherit F_FINANCE;
# inherit F_MESSAGE;
# inherit F_MORE; 
# inherit F_MOVE;		Y
# inherit F_NAME;		Y
# inherit F_SKILL;
# inherit F_TEAM;

# Use a tick with longer period than heart beat to save cpu's work
var tick:int;

func create():
	seteuid(0); # so LOGIN_D can export uid to us

# Use this function to identify if an object is a character.
func is_character() :
	return 1;

# setup: used to configure attributes that aren't known by this_object()
# at create() time such as living_name (and so can't be done in create()).
func setup():
	seteuid(getuid(this_object()));

	set_heart_beat(1);
	tick = 5 + random(10);
	enable_player();

	CHAR_D.setup_char( this_object() );
}

func heart_beat():
	var wimpy_ratio
	var cnd_flag=0;
	var  my = {};
	var  ob;

	my = query_entire_dbase();

	# If we are dying because of mortal wounds?
	if( my["eff_qi"] < 0 || my["eff_jing"] < 0):
		remove_all_enemy();
		die();
		return;
	
	# If we're dying or falling unconcious?
	if( my["qi"] < 0 || my["jing"] < 0):
		remove_all_enemy();
		if( !living(this_object()) ||
			this_object().query_temp("noliving") ) die();
		else unconcious();
		return;
	
	# Do attack if we are fighting.
	if( is_busy() ):
		continue_action();
		# We don't want heart beat be halt eventually, so return here.
		return;
	else:
		# Is it time to flee?
		wimpy_ratio = int(query("env/wimpy"))
		if( is_fighting() && intp(wimpy_ratio) && wimpy_ratio > 0 &&	\
			( my["qi"] * 100 / my["max_qi"] <= wimpy_ratio ||			\
			my["jing"] * 100 / my["max_jing"] <= wimpy_ratio) ):
			GO_CMD.do_flee(this_object());							
		# Do attack or clean up enemy if we have fleed.
		if( living(this_object()) && !this_object().query_temp("noliving") ):
			attack();

	if( !userp(this_object()) ):
		if( living(this_object()) ):
			this_object().chat();
		# chat() may do anything -- include destruct(this_object())
		if( !this_object() ) :
			return;	

	if (this_object().query("env/no_fight") && this_object().is_killing()) :
		this_object().delete("env/no_fight");
	tick = tick - 1
	if( tick <=0) :
		return;
	else:
		tick = 5 + random(10);

	if (!environment()||!environment().is_chat_room() || !query("env/halt_age")) :
		cnd_flag = update_condition();

	# If we are compeletely in peace, turn off heart beat.
	# heal_up() must be called prior to other two to make sure it is called
	# because the && operator is lazy :P
	if( ((cnd_flag & CND_NO_HEAL_UP) || !heal_up()) && !is_fighting() && !interactive(this_object())):
		if( environment() ) :
			ob = first_inventory(environment());
			while(ob && !interactive(ob)):
				ob = next_inventory(ob);
		if( !ob ) :
			set_heart_beat(0);

	if( !interactive(this_object()) ) :
		return;

	# Make us a bit older. Only player's update_age is defined.
	# Note: update_age() is no need to be called every heart_beat, it
	#       remember how much time has passed since last call.
	this_object().update_age();

	if(query_idle(this_object()) > IDLE_TIMEOUT && !wizardp(this_object())):
		this_object().user_dump(DUMP_IDLE);


###########	wiz func .not used.


# func visible(object ob):
# {
# 	int lvl, invis;

# 	lvl = wiz_level(this_object());

# 	if( lvl > wiz_level(ob) ) return 1;
# 	if(wizardp(ob)) invis = (int)ob.query("env/invisibility");
# 	else invis=0;
# 	if( intp(invis) && (invis > lvl) ) return 0;

# 	if( ob.is_ghost() ) {
# 		if( is_ghost() ) return 1;
# 		if( query_temp("apply/astral_vision") ) return 1;
# 		return 0;
# 	}
# 	return 1;
# }

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

############################### tool ############

func is_character():
	return true
#
func _init():
#	skills = {}
#	test_skills = {}
#	map_skills = {}
#	prepare_skills = {}
#	family = {}
	create()
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