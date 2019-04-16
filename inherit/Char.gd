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

# inherit F_ACTION;		Y
# inherit F_ALIAS;		X 机器人程序相关,不需要
# inherit F_APPRENTICE;	Y
# inherit F_ATTACK;
# inherit F_ATTRIBUTE;	Y
# inherit F_COMMAND;
# inherit F_CONDITION;
# inherit F_DAMAGE;
# inherit F_DBASE;		E
# inherit F_EDIT;
# inherit F_FINANCE;
# inherit F_MESSAGE;
# inherit F_MORE; 
# inherit F_MOVE;		Y
# inherit F_NAME;		Y
# inherit F_SKILL;		Y
# inherit F_TEAM;


########################################## F_ACTION ######################
var busy
var interrupt
var old_busy = 0;

func start_busy(new_busy, new_interrupt):
	if( !new_busy ) :
		return;
	if( !intp(new_busy) && !functionp(new_busy) ):
		print_debug("action: Invalid busy action type.\n");
# Add being busy time to New busy. By winder. 2001.10.18
# 改dazuo状态下 start_busy(3)的bug 
	if( this_object().is_busy()):
		if (functionp(busy)):
			old_busy += new_busy;
		elif (intp(busy)):
			busy += new_busy;
	else:
		busy = new_busy;
	if( !intp(new_interrupt) && !functionp(new_interrupt) ):
		print_debug("action: Invalid busy action interrupt handler type.\n");
	if (functionp(new_interrupt)):
		interrupt = new_interrupt;
	set_heart_beat(1);
	
func set_heart_beat(i):
	pass	

func query_busy() :
	return busy
func is_busy() :
	return busy!=0

# This is called by heart_beat() instead of attack() when a ppl is busy
# doing something else.

func continue_action():
	if( intp(busy) && (busy > 0) ) :
		busy = busy - 1;
		return;
	elif( functionp(busy) ) :
		if( !evaluate(busy, this_object()) ) :
#			busy = 0;
			busy = old_busy;
			old_busy = 0;
			interrupt = 0;

	else :
		busy = 0;
		interrupt = 0;


func interrupt_me(who, how:String):
	if( !busy ) :
		return;

	if( intp(busy) && intp(interrupt) ) :
		if( busy < interrupt ) :
			busy = 0;
	elif( functionp(interrupt) ) :
		if( evaluate(interrupt, this_object(), who, how) ) :
			busy = old_busy;
			old_busy = 0;
			interrupt = 0;

func remove_busy():
	old_busy = 0;
	busy = 0;
	interrupt = 0;

# This function is for temporary conditions's recovery call_outs, bcz
# such recovery function call_out might be destroyed if some wizard
# destructed the object that is reponsible of it, so we let users launch
# the call_out themself. Thus we can make sure the recovery call_out.
# 
# Because this could cause a serious security problem, so we need highest
# security check here.
const ROOT_UID = -1

func start_call_out(fun, delay:int):
	if( !previous_object() || (getuid(previous_object()) != ROOT_UID			\
		&& sscanf(base_name(previous_object()),"/kungfu/skill/%*s/%*s")!=2		\
		&& userp(this_object()) && this_player() != this_object())):			
		return 0;

	call_out("eval_function", delay, fun);
	return 1;

func eval_function(fun,ob) :
	evaluate(fun,ob)

########  TODO #######
func previous_object():
	pass

func base_name(ob):
	self.name()
	
func sscanf(s,s1):
	pass	
########################################## F_APPERENCE 学徒##################

func is_apprentice_of(ob):
	var family;
	family = query("family")
	if( !mapp(family) ) :
		return 0;

	if( family["master_id"] == ob.query("id") && family["master_name"] == ob.query("name") ):
		return 1;
	return 0;	

func assign_apprentice(title:String, privs:int):
	var family;
	family = query("family")
	if( !mapp(family) ) :
		return;

	family["title"] = title;
	family["privs"] = privs;

	if( userp(this_object()) || !query("title") ) :
		if( family["generation"]==1 ):
			set("title", family["family_name"] + "开山祖师");
		else:
			set("title", sprintf("%s第%s代%s", family["family_name"],
				chinese_number(family["generation"]), family["title"]));


# This is used for NPC, or start a new family for a player.
func create_family(family_name:String, generation:int, title:String):
	var family;

	# family = allocate_mapping(6);

	family["family_name"] = family_name;
	family["generation"] = generation;

	set("family", family);

	# priv = -1 for ALL privileges.
	assign_apprentice( title, -1 );

func recruit_apprentice(ob):
	var my_family
	var family;

	if( ob.is_apprentice_of( this_object() ) ):
		return 0;
	my_family = query("family")	
	if( !mapp(my_family) ):
		return 0;

#	family = allocate_mapping(sizeof(my_family));
	family = {}
	family["master_id"] = query("id");
	family["master_name"] = query("name");
	family["family_name"] = my_family["family_name"];
	family["generation"] = my_family["generation"] + 1;
	family["enter_time"] = OS.get_time(); #  return {}
	ob.set("family", family);
	ob.assign_apprentice("弟子", 0);
	return 1;



##########################################  F_ATTRIBUTE ###################
# 膂力 -- 出手重
func query_str():
	var improve = query_skill("unarmed", 1) / 10;

	if ( query_skill("leg", 1) || query_skill("strike", 1) ||	\
		query_skill("finger", 1) || query_skill("cuff", 1) ||   \
		query_skill("hand", 1) || query_skill("claw", 1)):
		if ( query_skill("leg", 1) >= improve * 10):
			improve = query_skill("leg", 1) / 10;
		if ( query_skill("strike", 1) >= improve * 10 ):
			improve = query_skill("strike", 1) / 10;
		if ( query_skill("finger", 1) >= improve * 10):
			improve = query_skill("finger", 1) / 10;
		if ( query_skill("cuff", 1) >= improve * 10):
			improve = query_skill("cuff", 1) / 10;
		if ( query_skill("hand", 1) >= improve * 10):
			improve = query_skill("hand", 1) / 10;
		if ( query_skill("claw", 1) >= improve * 10):
			improve = query_skill("claw", 1) / 10;
	return query("str") + query_temp("apply/strength") + improve;

# 悟性 -- 学习和读书快
func query_int():
	return query("int") + query_temp("apply/intelligence") + query_skill("literate", 1) / 10;

# 根骨 -- 气血恢复快且长大时气血上限增量高
func query_con():
	return query("con") + query_temp("apply/constitution") + query_skill("force", 1) / 10;

# 身法 -- 躲避快
func query_dex():
	return query("dex") + query_temp("apply/dexerity") + query_skill("dodge", 1) / 10;

# 耐力 -- 内力恢复快
func query_sta():
	return query("sta") + query_temp("apply/stamina") + query_skill("parry", 1) / 10;

# 灵性 -- 能学更多的武功，且速度也快
func query_spi():
	var improve = query_skill("buddhism", 1) / 10;

	if ( query_skill("buddhism", 1) || query_skill("mahayana", 1) ||	\
		query_skill("lamaism", 1) || query_skill("taoism", 1) ||		\
		query_skill("ziyunyin",1) || query_skill("zhengqijue",1) || query_skill("poison")):
			if ( query_skill("buddhism", 1) >= improve * 10 ):
				improve = query_skill("buddhism", 1) / 10;
			if ( query_skill("mahayana", 1) >= improve * 10):
				improve = query_skill("mahayana", 1) / 10;
			if ( query_skill("lamaism", 1) >= improve * 10):
				improve = query_skill("lamaism", 1) / 10;
			if ( query_skill("taoism", 1) >= improve * 10):
				improve = query_skill("taoism", 1) / 10;
			if ( query_skill("ziyunyin", 1) >= improve * 10):
				improve = query_skill("ziyunyin", 1) / 10;
			if ( query_skill("zhengqijue", 1) >= improve * 10):
				improve = query_skill("zhengqijue", 1) / 10;
			if ( query_skill("poison", 1) >= improve * 10):
				improve = query_skill("poison", 1) / 10;		
	return query("spi") + query_temp("apply/spirit") + improve;

# 福缘 -- 机缘好
func query_kar():
	return query("kar") + query_temp("apply/karma");

# 容貌 -- 对定力低的异性有震慑力
func query_per():
	return query("per") + query_temp("apply/personality");

# 定力 -- 出手破绽少，不易被反击，对方进功成功率低
func query_cps():
	return query("cps") + query_temp("apply/composure");

# 胆识 -- 出手成功率高
func query_cor():
	return query("cor") + query_temp("apply/courage");

# 兽类驯服度 -- 
func query_obe():
	return query("obe") + query_temp("apply/obedience");


################################################################# char ##################################

# Use a tick with longer period than heart beat to save cpu's work
var tick:int;

func create():
	setuid(0); # so LOGIN_D can export uid to us

# Use this function to identify if an object is a character.
func is_character() :
	return 1;

# setup: used to configure attributes that aren't known by this_object()
# at create() time such as living_name (and so can't be done in create()).
func setup():
	setuid(getuid(this_object()));

	set_heart_beat(1);
	tick = 5 + random(10);
	
#	enable_player();

	CHAR_D.setup_char( this_object() );

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
		if( !living(this_object()) || this_object().query_temp("noliving") ):
			die();
		else :
			unconcious();
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
# 	if(wizardp(ob)) invis = ob.query("env/invisibility");
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
	
#var skills = {}
#var test_skills = {}
#var map_skills = {}
#var prepare_skills = {}
#
#func set_skill(key:String,value):
##	if !skills:skills={}
#	skills[key] = value
#
#func get_skill(key:String):
#	return skills[key]
#
#func map_skill( key:String,value):
##	if !map_skills:map_skills={}
#	map_skills[key] = value
#
#func prepare_skill(key:String,value):
##	if !prepare_skills:prepare_skills={}
#	prepare_skills[key] = value
#
#func query_skill(skill:String,key:String):
#	if skills.has(skill) and skills[skill].has(key):
#		return skills[skill][key]
#	else:
#		return false
		
		

# ---------------------------- family ----------------------	
#var family = {}
#func create_family(key:String,lvl:int,nack_name:String):
#	family.name = key
#	family.lvl =  lvl
#	family.nack_name = nack_name

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
#
func _init():
#	skills = {}
#	test_skills = {}
#	map_skills = {}
#	prepare_skills = {}
#	family = {}
	create()
	pass	

# todo new()  to  new_ob()
func new_ob(path:String):
	var obj
	if path.find("res:/")>0 and path.find(".gd",-1)>0 :
		obj = load(path).new() 
	else:
		obj = load("res:/" + path + ".gd").new()
	obj.set("environment",self.name())
	obj.set_temp("environment",self)
	return obj

########################################  F_NAME ####################
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
	

######################################### F_SKILL ########################

var skills;
var learned;
var skill_map;
var skill_prepare;

func query_skills() :
	return skills
func query_learned() :
	return learned

func set_skill(skill:String, val:int = 0):
	if( !find_object(SKILL_D(skill)) &&	file_size(SKILL_D(skill)+".c") < 0 ):
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) ) :
		skills = {skill: val}
	else :
		skills[skill] = val;

func delete_skill(skill:String):
	if( mapp(skills) ) :
		map_delete(skills, skill);
		if( mapp(learned) ) :
			map_delete(learned, skill);
			return undefinedp(learned[skill]);
		return undefinedp(skills[skill]);
	return 0;

# This function 'map' a skill <skill> to another skill <mapped_to>.
# If 2nd argument not given, cancel the mapped skill <skill>.
func map_skill(skill:String, mapped_to:String):
	if( !mapped_to && mapp(skill_map) ):
		map_delete(skill_map, skill);
		return;

	if( !find_object(SKILL_D(skill)) &&	file_size(SKILL_D(skill)+".c") < 0 ):
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) || undefinedp(skills[mapped_to]) ):
		return;
		
	if( !mapp(skill_map) ) :
		skill_map = {skill: mapped_to}
	else :
		skill_map[skill] = mapped_to;

# This function 'prepare' a skill <skill> to another skill <mapped_to>.
# If 2nd argument not given, cancel the prepared skill <skill>.
func prepare_skill(skill:String, mapped_to:String):
	if( !mapped_to && mapp(skill_prepare) ) :
		map_delete(skill_prepare, skill);
		return;

	if( !find_object(SKILL_D(skill)) && file_size(SKILL_D(skill)+".c") < 0 ):
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) || undefinedp(skills[mapped_to]) ):
		return;
		
	if( !mapp(skill_prepare) ) :
		skill_prepare = {skill: mapped_to};
	else :
		skill_prepare[skill] = mapped_to;

func query_skill_mapped(skill:String,raw:int = 0):
	if( mapp(skill_map) && !undefinedp(skill_map[skill]) ):
		return skill_map[skill];
	return 0;

func query_skill_prepared(skill:String,raw:int = 0):
	if( mapp(skill_prepare) && !undefinedp(skill_prepare[skill]) ):
		return skill_prepare[skill];
	return 0;

func query_skill(skill:String, raw:int = 0):
	if( !raw ) :
		var s;
		
		s = query_temp("apply/" + skill);
		if( mapp(skills) ) :
			s += skills[skill] / 2;
			if( mapp(skill_map) ):
				s += skills[skill_map[skill]];
		return s;
	if( mapp(skills) && !undefinedp(skills[skill]) ) :
		return skills[skill];
	return 0;

func query_skill_map():
	return skill_map;

func query_skill_prepare():
	return skill_prepare;

func skill_death_penalty():
	var sk;
	var i;

	if( wizardp(this_object()) || !mapp(skills) ) :
		return 0;

	sk = keys(skills);
# /*
# 	if( !mapp(learned) )
# 		for(i = 0; i<sizeof(sk); i++)
# 		{
# 			skills[sk[i]]--;
# 			if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
# 		}
# 	else
# 		for(i = 0; i<sizeof(sk); i++)
# 		{
# #			if( (int)learned[sk[i]] > (skills[sk[i]]+1) * (skills[sk[i]]+1) / 2 )
# #				map_delete(learned, sk[i]);
# #			else {
# #				skills[sk[i]]--;
# #				if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
# #			}
# 			skills[sk[i]]--;
# 			map_delete(learned,sk[i]);
# 			if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
# 		}
# */
		# for(i = 0; i<sizeof(sk); i++)
	for i in range(sizeof(sk)) :
		skills[sk[i]] = skills[sk[i]] - 1;
		if( skills[sk[i]]<0  || (skills[sk[i]]==0 && learned[sk[i]]==0) ):
			map_delete(skills, sk[i]);
			if (mapp(learned)):
				map_delete(learned,sk[i]);


	skill_map = 0;
	return 1;


func skillreincarnate():
	var sk
	var i

	sk = keys(skills);
#	for(i = 0; i<sizeof(sk); i++) :
	for i in range(sizeof(sk)) :
		skills[sk[i]] = skills[sk[i]] + 1;
	log_file("skill_re", sprintf("[%s] %s eat %s \n", ctime(time()), geteuid(this_object()),base_name(previous_object())));
	return 1;

func improve_skill(skill:String, amount:int, weak_mode:int):
	var spi;

#只有玩家和好学的npc才能学习。比如宠物或玩家小孩等。
	if (!userp(this_object()) && !this_object().query("curiousness")):
		return; 
	if( !find_object(SKILL_D(skill)) && file_size(SKILL_D(skill)+".c") < 0 ):
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !weak_mode || !userp(this_object()) ) :
		if( !mapp(skills) ) :
			skills = ([]);
		if( undefinedp(skills[skill]) ) :
			skills[skill] = 0;


	# Give learning penalty to those learning too much skills.
	spi = this_object().query_spi();
	if( sizeof(learned) > spi ):
		amount /= sizeof(learned) - spi;

	if( !amount ) :
		amount = 1;

	if( !mapp(learned) ) :
		learned = {skill : amount};
	else :
		learned[skill] += amount;

	if( (!weak_mode || !userp(this_object())) && learned[skill] > (skills[skill] + 1) * (skills[skill] + 1) ) :
		skills[skill] = skills[skill] + 1;
		learned[skill] = 0;
		tell_object(this_object(), HIC + "你的「" + to_chinese(skill) + "」进步了！\n" + NOR);
		SKILL_D(skill).skill_improved(this_object());



###################### tools ##############
func chinese_number(i:int):
	CHINESE_D.chinese_number(i)
	
func this_object(ob=self):
	return ob
	
### todo	
func this_player(ob=self):
	return ob	
	
func call_out(funcname, delay, fun):
	pass
			
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
	return string

# todo 
func living(ob):
	return true
	
# todo
var fighting = false	
func is_fighting():
	return fighting	or query("fighting")
	
func sizeof(a):
	return a.size()	