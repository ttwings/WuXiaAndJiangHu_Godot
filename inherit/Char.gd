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
# inherit F_ATTACK;		Y
# inherit F_ATTRIBUTE;	Y
# inherit F_COMMAND;		TODO: 未发现确实需要的东西
# inherit F_CONDITION;	Y
# inherit F_DAMAGE;		Y
# inherit F_DBASE;		E
# inherit F_EDIT;		X 内建编辑器
# inherit F_FINANCE;	Y
# inherit F_MESSAGE;		TODO: 用信号来实现
# inherit F_MORE; 		X 下一页
# inherit F_MOVE;		Y
# inherit F_NAME;		Y
# inherit F_SKILL;		Y
# inherit F_TEAM;		Y


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

# TODO 打断函数
func interrupt_me(who, how:String):
	if( !busy ) :
		return;

	if( intp(busy) && intp(interrupt) ) :
		if( busy < interrupt ) :
			busy = 0;
#	elif( functionp(interrupt) ) :
#		if( evaluate(interrupt, [this_object()], who, how) ) :
#			busy = old_busy;
#			old_busy = 0;
#			interrupt = 0;

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
#	if( !previous_object() || (getuid(previous_object()) != ROOT_UID			\
#		&& sscanf(base_name(previous_object()),"/kungfu/skill/%*s/%*s")!=2		\
#		&& userp(this_object()) && this_player() != this_object())):			
#		return 0;
#
#	call_out("eval_function", delay, fun);
	return 1;

func eval_function(fun,ob) :
	evaluate(fun,ob)

########  TODO #######
func previous_object():
	pass
	
func sscanf(s:String,s1:String):
	var f = s.find(s1)
	print_debug(f)
	return f
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
	var family = {};

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


######################################### F_ATTACK #############################

# const MAX_OPPONENT = 4
var enemy = [];
var killer = [];

# # prototypes

# func query_enemy() :
# 	return enemy
# func query_killer() :
# 	return killer

# # This function returns 1 if we are fighting anyone (or with ob)
func is_fighting(ob=self):
 	if( !ob ) :
 		return sizeof(enemy) > 0;

# 	return member_array(ob, enemy)!=-1;

# # This function returns 1 if we are fighting anyone (or with ob)
# func is_killing(id):
# 	if( !id ) :
# 		return sizeof(killer) > 0;

# 	return member_array(id, killer)!=-1;

# #This function starts fight between this_object() and ob
# func fight_ob(ob):
# 	var inv
# 	var obj;
# 	var i;

# 	if(!ob || ob==this_object()) :
# 		return;
# 	if (environment(ob) != environment(this_object())) :
# 		return;
# 	set_heart_beat(1);

# 	if( member_array(ob, enemy)==-1 ) :
# 		enemy += [ ob ];

# # This function starts killing between this_object() and ob
# func kill_ob(ob):
# 	var guards;
# 	var me = this_object();

# 	if( me.query_temp("guardfor") == ob):
# 		tell_object(me, HIR + "不能杀你要保护的人！\n" + NOR);
# 		return;

# 	if( environment(me).query("no_fight")) :
# 		return;
# 	if (environment(me)!=environment(ob)) :
# 		return;

# 	if (me.is_killing(ob.query("id")) && me.is_fighting(ob)) :
# 		return;
# 	tell_object(ob, HIR + "看起来" + this_object().name() + "想杀死你！\n" + NOR);

# 	if( member_array(ob.query("id"), killer)==-1 ):
# 		killer += [ ob.query("id") ];
# 	if (me.query("env/no_fight")) :
# 		me.delete("env/no_fight");
# 	if (ob.query("env/no_fight")) :
# 		ob.delete("env/no_fight");


# # /*	if ( ob == query_temp( "guardfor" ) )
# # 	{
# # 		delete_temp("guardfor");
# # 		guards = ob.query_temp("guarded");
# # 		guards -= [ this_object() ];
# # 		ob.set_temp("guarded", guards);
# # 		tell_object(this_object(), HIY "你停止保护" + ob.name() + "。\n" NOR);
# # 		tell_object(ob, HIY + this_object().name() + "停止保护你。\n" NOR);
# # 	}
# # */

# # TODO:
# 	# if ( !this_object().query("jianxi")&&!this_object().query("quest_no_guard")&& arrayp(guards = ob.query_temp("guarded")))
# 	# 	guards = filter_array(guards, (: objectp($1)
# 	# 	&& living($1) && !$1.query_temp("noliving") 
# 	# 	&& $1 != this_object()
# 	# 	&& present($1, environment())
# 	# 	&& !is_fighting($1)
# 	# 	&& $1.visible(this_object()) :));

# 		if ( sizeof(guards) > 0 ):
# 			enemy += guards;
# 			message("vision", HIR + ob.name() + "受到攻击！你挺身加入战团！\n" + NOR, guards);
# 			guards.kill_ob(this_object());


# 	fight_ob(ob);


# func clean_up_enemy():
# 	if( sizeof(enemy) > 0 ) :
# 		# for(int i=0; i<sizeof(enemy); i++)
# 		for i in range(sizeof(enemy)):
# 			if( !objectp(enemy[i]) || environment(enemy[i])!=environment() || ((!living(enemy[i]) || 	\
# 				enemy[i].query_temp("noliving") ) && 													\
# 				!is_killing(enemy[i].query("id"))) ) :
# 				enemy[i] = 0;
		
# 		enemy -= [ 0 ];


# # This function checks if the current opponent is available or
# # select a new one.
# func select_opponent():
# 	var which;
# #	object *ob;
# #  int i;
# #  ob=enemy;
# 	if( enemy.size() <= 0 ) :
# 		return 0;

# 	which = random(MAX_OPPONENT);
# 	which = enemy[which] if which < sizeof(enemy) else enemy[0]
# #	return which < sizeof(enemy) ? enemy[which] : enemy[0];
# 	return which

# # /*  for (i=0;i<sizeof(ob);i++)
# #         if (!objectp(ob[i]) || environment(ob[i])!=environment(me))
# #          ob -= [ob[i]];
# #    if (!sizeof(ob)) return 0;
# #    elif (sizeof(ob)>4) return ob[random(MAX_OPPONENT)];
# #    else return ob[random(sizeof(ob))];
# # */


# # Stop fighting ob.
# func remove_enemy(ob):
# 	if( is_killing(ob.query("id")) ) :
# 		return 0;
# 	enemy -= [ ob ];
# 	return 1;

# # Stop killing ob.
# func remove_killer(ob):
# 	if( is_killing(ob.query("id")) ) :
# 		killer -= [ ob.query("id") ];
# 		remove_enemy(ob);
# 		return 1;

# 	return remove_enemy(ob);


# # Stop all fighting, but killer remains.
# func remove_all_enemy():
# #	enemy.clear()
# 	var size = enemy.size()
# 	for i in range(size) :
# 		# We ask our enemy to stop fight, but not nessessary to confirm
# 		# if the fight is succeffully stopped, bcz the fight will start
# 		# again if our enemy keeping call COMBAT_D.fight() on us.
# 		if( enemy[i] is Char ) :
# 			enemy[i].remove_enemy(this_object());
# 		enemy[i] = 0

# 	enemy = [];

# # Stop all fighting and killing.
# func remove_all_killer() :
# 	killer = [];
# 	enemy -= [ 0 ];

# 	# for(int i=0; i<sizeof(enemy); i++)
# 	for i in range(sizeof(enemy)) :
# 		if( enemy[i].remove_killer(this_object()) ):
# 			enemy[i] = 0

# 	enemy -= [ 0 ];


# # reset_action()
# #
# # This function serves as a interface of F_ATTACK and wielded, worn objects.
# # When the living's fighting action need update, call this function.
# #
# func reset_action():
# 	var me
# 	var ob
# 	var prepare
# 	var type
# 	var skill

# 	me = this_object();
# 	prepare = query_skill_prepare();
# 	ob = query_temp("weapon")
# 	if( ob or ob != "" ) :
# 		type = ob.query("skill_type");
# 	elif ( sizeof(prepare) == 0) :
# 		type = "unarmed";
# 	elif ( sizeof(prepare) == 1) :
# 		type = (keys(prepare))[0];
# 	elif ( sizeof(prepare) == 2) :	
# 		type = (keys(prepare))[query_temp("action_flag")];

# 	skill = query_skill_mapped(type)
# 	if( stringp(skill) ):
# # If using a mapped skill, call the skill daemon.
# 		if ( ob ):
# 			set("actions", [ call_other, SKILL_D(skill), "query_action", me, ob ] );
# 		else:
# 			set("actions", [ call_other, SKILL_D(skill), "query_action" ] );
# 	else :
# # Else, let weapon handle it.
# 		if( ob ) :
# #			set("actions", ob.query("actions",1) );
# 			set("actions",ob.query("actions"))
# 		else :
# #			set("actions", query("default_actions",1) );
# 			set("actions",query("default_actions"))


# # This is called in heart_beat() to perform attack action.
# func attack():
# 	var opponent;

# 	clean_up_enemy();

# 	opponent = select_opponent();
# 	if( objectp(opponent) ) :
# 		set_temp("last_opponent", opponent);
# 		# TODO
# #		COMBAT_D.fight(this_object(), opponent);
# 		return 1;
# 	else :
# 		return 0;


# #
# # init() - called by MudOS when another object is moved to us.
# #
# func init() :
# 	var ob;
# 	var vendetta_mark;

# 	# We check these conditions here prior to handle auto fights. Although
# 	# most of these conditions are checked again in COMBAT_D's auto_fight()
# 	# function,these check reduces lots of possible failure in the call_out
# 	# launched by auto_fight() and saves some overhead.
	
# 	# TODO. 弄清楚再修改 
# 	ob = this_player()
# 	if( is_fighting() || !living(this_object()) ||						\
# 		this_object().query_temp("noliving") ||							\
# 		! ob || environment(ob) != environment() ||						\
# 		!living(ob) || ob.query_temp("noliving") ||						\
# 		ob.query("linkdead") ):
# 		return;

# 	# Now start check the auto fight cases.
# 	vendetta_mark = query("vendetta_mark")
# 	if( userp(ob) && is_killing(ob.query("id")) ):
# 		COMBAT_D.auto_fight(this_object(), ob, "hatred");
# 		return;
# 	elif( stringp(vendetta_mark) &&			\
# 		ob.query("vendetta/" + vendetta_mark) ) :
# 		COMBAT_D.auto_fight(this_object(), ob, "vendetta");
# 		return;
# 	elif (userp(ob) && query("attitude")=="aggressive"):
# 		COMBAT_D.auto_fight(this_object(), ob, "aggressive");
# 		return;


# func do_ride_none(me):
# 	var ob
# 	var inv;
# 	var i = 0;

# #	if( !this = find_object( VOID_OB ) )
# #		this = load_object( VOID_OB );
# #	inv = all_inventory(this);
# 	inv = all_inventory(me);
# 	while( i < sizeof(inv) && i >= 0 ) :
# #		if( inv[i].query_temp("is_rided_by") == me.query("id") )
# 		if( inv[i].query_temp("is_rided_by") == me ):
# 			ob = inv[i];
# 			i = -10;

# 		i = i + 1;

# 	if( i >= 0 ):
# 		return notify_fail("发现错误！\n");

# 	return 1;




# ##########################################  F_ATTRIBUTE ###################
# # 膂力 -- 出手重
# func query_str():
# 	var improve = query_skill("unarmed", 1) / 10;

# 	if ( query_skill("leg", 1) || query_skill("strike", 1) ||	\
# 		query_skill("finger", 1) || query_skill("cuff", 1) ||   \
# 		query_skill("hand", 1) || query_skill("claw", 1)):
# 		if ( query_skill("leg", 1) >= improve * 10):
# 			improve = query_skill("leg", 1) / 10;
# 		if ( query_skill("strike", 1) >= improve * 10 ):
# 			improve = query_skill("strike", 1) / 10;
# 		if ( query_skill("finger", 1) >= improve * 10):
# 			improve = query_skill("finger", 1) / 10;
# 		if ( query_skill("cuff", 1) >= improve * 10):
# 			improve = query_skill("cuff", 1) / 10;
# 		if ( query_skill("hand", 1) >= improve * 10):
# 			improve = query_skill("hand", 1) / 10;
# 		if ( query_skill("claw", 1) >= improve * 10):
# 			improve = query_skill("claw", 1) / 10;
# 	return query("str") + query_temp("apply/strength") + improve;

# # 悟性 -- 学习和读书快
# func query_int():
# 	return query("int") + query_temp("apply/intelligence") + query_skill("literate", 1) / 10;

# # 根骨 -- 气血恢复快且长大时气血上限增量高
# func query_con():
# 	return query("con") + query_temp("apply/constitution") + query_skill("force", 1) / 10;

# # 身法 -- 躲避快
# func query_dex():
# 	return query("dex") + query_temp("apply/dexerity") + query_skill("dodge", 1) / 10;

# # 耐力 -- 内力恢复快
# func query_sta():
# 	return query("sta") + query_temp("apply/stamina") + query_skill("parry", 1) / 10;

# # 灵性 -- 能学更多的武功，且速度也快
# func query_spi():
# 	var improve = query_skill("buddhism", 1) / 10;

# 	if ( query_skill("buddhism", 1) || query_skill("mahayana", 1) ||	\
# 		query_skill("lamaism", 1) || query_skill("taoism", 1) ||		\
# 		query_skill("ziyunyin",1) || query_skill("zhengqijue",1) || query_skill("poison")):
# 			if ( query_skill("buddhism", 1) >= improve * 10 ):
# 				improve = query_skill("buddhism", 1) / 10;
# 			if ( query_skill("mahayana", 1) >= improve * 10):
# 				improve = query_skill("mahayana", 1) / 10;
# 			if ( query_skill("lamaism", 1) >= improve * 10):
# 				improve = query_skill("lamaism", 1) / 10;
# 			if ( query_skill("taoism", 1) >= improve * 10):
# 				improve = query_skill("taoism", 1) / 10;
# 			if ( query_skill("ziyunyin", 1) >= improve * 10):
# 				improve = query_skill("ziyunyin", 1) / 10;
# 			if ( query_skill("zhengqijue", 1) >= improve * 10):
# 				improve = query_skill("zhengqijue", 1) / 10;
# 			if ( query_skill("poison", 1) >= improve * 10):
# 				improve = query_skill("poison", 1) / 10;		
# 	return query("spi") + query_temp("apply/spirit") + improve;

# # 福缘 -- 机缘好
# func query_kar():
# 	return query("kar") + query_temp("apply/karma");

# # 容貌 -- 对定力低的异性有震慑力
# func query_per():
# 	return query("per") + query_temp("apply/personality");

# # 定力 -- 出手破绽少，不易被反击，对方进功成功率低
# func query_cps():
# 	return query("cps") + query_temp("apply/composure");

# # 胆识 -- 出手成功率高
# func query_cor():
# 	return query("cor") + query_temp("apply/courage");

# # 兽类驯服度 -- 
# func query_obe():
# 	return query("obe") + query_temp("apply/obedience");

# ################################################################# F_CONDITION ##############

# var conditions;
# var type_conditions;

# # This function is called by heart_beat to update "continously active"
# # conditions. These conditions will be saved as well. Because such type
# # of conditions costs heart beat evaluation time, don't make player got
# # too much this kind of conditions or you might got lots fo "Too long
# # evaluation" error message in the log file.

# func update_condition():
# 	var cnd
# 	var err
# 	var i
# 	var flag
# 	var update_flag
# 	var cnd_d
# 	i = conditions.size()
# 	if( !mapp(conditions) || i <= 0 ) :
# 		return 0;
# 	cnd = keys(conditions);
# 	update_flag = 0;
# 	i = i - 1
# 	while(i>0) :
# 	# In order to not casue player lost heart beat occasionally while
# 	# calling external condition daemons, we take careful calling
# 	# convention here.

# 		cnd_d = find_object(CONDITION_D(cnd[i]));
# 		if( !cnd_d ):
# 			err = catch(call_other(CONDITION_D(cnd[i]), "???"));
# 			cnd_d = find_object(CONDITION_D(cnd[i]));
# 	# If we failed to load the external condition daemon, remove
# 	# it before we stuff log files with error messages.
# 			if( err || !cnd_d ):
# 				log_file("condition.err", sprintf("Failed to load condition daemon %s, removed from %O\nError: %s\n", CONDITION_D(cnd[i]), this_object(), err));
# 				map_delete(conditions, cnd[i]);
# 				continue;

# 	# We assume since the condition daemon is loaded successfully, the
# 	# calling on its update_condition() should success as well. Because
# 	# catch() is somewhat costly, so we don't attempt to catch possible
# 	# error from the call_other. It is condition daemon's reponsibility
# 	# that don't cause error in users's heart beat.
# 	# If condition daemon returns 0 (or update_condition() not defined),
# 	# we can just assume the condition expired and remove it.
# 		flag = call_other(cnd_d, "update_condition", this_object(), conditions[cnd[i]]);
# 		if( !( flag & CND_CONTINUE ) ) :
# 			map_delete(conditions, cnd[i]);
# 		update_flag |= flag;
	
# 	if( !sizeof(conditions) ) :
# 		conditions = 0;
# 	return update_flag;


# # apply_condition()
# #
# # This function applies the specific condition to the character. Note we 
# # don't check if the condition already exist before setting condition info.
# # It is condition giver's reponsibility to check if the condition should
# # override the old one if same condition already exists.(Use query_condition
# # to check)

# func apply_condition(cnd:String, info):
# 	if( !mapp(conditions) ):
# 		conditions = { cnd : info };
# 	else:
# 		conditions[cnd] = info;


# # query_condition()
# #
# # This function returns info about the specific condition if any.

# func query_condition(cnd:String):
# 	if( !mapp(conditions) || undefinedp(conditions[cnd]) ) :
# 		return 0;
# 	return conditions[cnd];


# func query_entire_conditions():
# 	return conditions;


# func query_conditions_by_type(required_type:String):
# 	var cnd_d
# 	var i
# 	var cnd_type
# 	var cnd
# 	var err
	
# 	if (!mapp(conditions) || !sizeof(conditions) > 0) :
# 		return 0;
# 	type_conditions = 0;
# 	cnd = keys(conditions);
# 	i = i - 1
# 	# In order to not casue player lost heart beat occasionally while
# 	# calling external condition daemons, we take careful calling
# 	# convention here.
# 	while(i>0):
# 		cnd_d = find_object(CONDITION_D(cnd[i]));
# 		if (!cnd_d):
# 			err = catch(call_other(CONDITION_D(cnd[i]), "???"));
# 			cnd_d = find_object(CONDITION_D(cnd[i]));
# 	# If we failed to load the external condition daemon, remove
# 	# it before we stuff log files with error messages.
# 			if (err || !cnd_d):
# 				log_file("condition.err", sprintf("Failed to load condition daemon %s, removed from %O\nError: %s\n", CONDITION_D(cnd[i]), this_object(), err));
# 				if (mapp(conditions)):
# 					map_delete(conditions, cnd[i]);
# 				continue;

# 	# We assume since the condition daemon is loaded successfully, the
# 	# calling on its update_condition() should success as well. Because
# 	# catch() is somewhat costly, so we don't attempt to catch possible
# 	# error from the call_other. It is condition daemon's reponsibility
# 	# that don't cause error in users's heart beat.
# 	# If condition daemon returns 0 (or update_condition() not defined),
# 	# we can just assume the condition expired and remove it.
# 		cnd_type = call_other(cnd_d, "query_type", this_object());
# 		if (cnd_type == required_type):
# 			if (!mapp(type_conditions)) :
# 				type_conditions = { cnd[i]: conditions[cnd[i]] };
# 			else :
# 				type_conditions[cnd[i]] = conditions[cnd[i]];

# 	return type_conditions;


# # /*
# # nomask clear_condition()
# # {
# # 	conditions = 0;
# # }
# # */ 
# func clear_condition(cnd:String):
# 	if (!cnd):
# 		conditions = 0;
# 	elif (mapp(conditions)) :
# 		map_delete(conditions, cnd);


# func clear_conditions_by_type(required_type:String):
# 	var cnd_d
# 	var i
# 	var cnd_type
# 	var cnd 
# 	var err

# 	if (!mapp(conditions) || ! sizeof(conditions) > 0) :
# 		return;
# 	cnd = keys(conditions);
# 	i = i - 1
# 	while(i>0):
# 	# In order to not casue player lost heart beat occasionally while
# 	# calling external condition daemons, we take careful calling
# 	# convention here.
# 		cnd_d = find_object(CONDITION_D(cnd[i]));
# 		if (!cnd_d):
# 			err = catch(call_other(CONDITION_D(cnd[i]), "???"));
# 			cnd_d = find_object(CONDITION_D(cnd[i]));
# 	# If we failed to load the external condition daemon, remove
# 	# it before we stuff log files with error messages.
# 			if (err || !cnd_d):
# 				log_file("condition.err",
# 					sprintf("Failed to load condition daemon %s, removed from %O\nError: %s\n", CONDITION_D(cnd[i]), this_object(), err));
# 				if (mapp(conditions)):
# 					map_delete(conditions, cnd[i]);
# 				continue;

# 	# We assume since the condition daemon is loaded successfully, the
# 	# calling on its update_condition() should success as well. Because
# 	# catch() is somewhat costly, so we don't attempt to catch possible
# 	# error from the call_other. It is condition daemon's reponsibility
# 	# that don't cause error in users's heart beat.
# 	# If condition daemon returns 0 (or update_condition() not defined),
# 	# we can just assume the condition expired and remove it.
# 		cnd_type = call_other(cnd_d, "query_type", this_object());
# 		if (cnd_type == required_type) :
# 			map_delete(conditions, cnd[i]);

# ############################################################### F_DAMAGE #############

# const ENTRY_ROOM = "/d/huashan/sheshen"
# var ghost = 0;
# func is_ghost() :
# 	return ghost
# func set_ghost(i) :
# 	ghost=i

# #varargs int receive_damage(type:String, dama:intge, object who)
# 	var val;
# 	var imp;

# 	if( damage < 0 ) :
# 		error("F_DAMAGE: 伤害值为负值。\n");
# 	if( type!="jing" && type!="qi" ):
# 		error("F_DAMAGE: 伤害种类错误( 只能是 jing, qi 其中之一 )。\n");

# 	if( objectp(reason) ) :
# 		set_temp("last_damage_from", reason);
# 	if( stringp(reason) ) :
# 		set_temp("die_reason",reason);
# 	imp=damage/5;
# 	if (query("max_nuqi") && this_object().is_fighting()):
# 		add( "nuqi" , imp );
# 	if ( query("nuqi")>query("max_nuqi") ):
# 		set("nuqi",query("max_nuqi"));
# 	val = query(type) - damage;

# 	if( val >= 0 ) :
# 		set(type, val);
# 	else :
# 		set( type, -1 );

# 	set_heart_beat(1);

# 	return damage;


# func receive_wound(type:String, damage:int,reason):
# 	var val;
# 	var imp;

# 	if( damage < 0 ) :
# 		error("F_DAMAGE: 伤害值为负值。\n");
# 	if( type!="jing" && type!="qi" ):
# 		error("F_DAMAGE: 伤害种类错误( 只能是 jing, qi 其中之一 )。\n");

# 	if( objectp(reason) ) :
# 		set_temp("last_damage_from", reason);
# 	if( stringp(reason) ) :
# 		set_temp("die_reason",reason);
# 	imp=damage/3;
# 	if (query("max_nuqi") && this_object().is_fighting()):
# 		add( "nuqi" , imp );
# 		if ( query("nuqi")>query("max_nuqi") ):
# 			set("nuqi",query("max_nuqi"));
# 	val = query("eff_" + type) - damage;

# 	if( val >= 0 ) :
# 		set("eff_" + type, val);
# 	else :
# 		set( "eff_" + type, -1 );
# 		val = -1;

# 	if( query(type) > val ) :
# 		set(type, val);

# 	set_heart_beat(1);

# 	return damage;


# func receive_heal(type:String, heal:int):
# 	var val;

# 	if( heal < 0 ) :
# 		error("F_DAMAGE: 恢复值为负值。\n");
# 	if( type!="jing" && type!="qi" ):
# 		error("F_DAMAGE: 恢复种类错误( 只能是 jing, qi 其中之一 )。\n");
# 	val = query(type) + heal;
# 	if( val > query("eff_"+type) ) :
# 		set(type, query("eff_"+type));
# 	else :
# 		set( type, val );

# 	return heal;


# func receive_curing(type:String, heal:int):
# 	var max_
# 	var val
# 	if( heal < 0 ) :
# 		error("F_DAMAGE: 恢复值为负值。\n");
# 	if( type!="jing" && type!="qi" ):
# 		error("F_DAMAGE: 恢复种类错误( 只能是 jing, qi 其中之一 )。\n");

# 	val = query("eff_" + type);
# 	max_ = query("max_" + type);

# 	if( val + heal > max_ ) :
# 		set("eff_" + type, max_);
# 		return max_ - val;
# 	else :
# 		set( "eff_" + type, val + heal);
# 		return heal;


# func unconcious():
# 	var defeater;
# 	var riding;

# 	# 所在房间定义了no_unconcious，不允许晕倒 
# 	if (environment().no_unconcious(this_object())) :
# 		return;
# 	if( !living(this_object()) || this_object().query_temp("noliving") ):
# 		return;
# 	if( wizardp(this_object()) && query("env/immortal") ) :
# 		return;
# 	defeater = query_temp("last_damage_from")
# 	if( objectp(defeater) ):
# 			COMBAT_D.winner_reward(defeater, this_object());
# 	if (environment(this_object())==environment(defeater)):
# 		if (this_object().query("max_nuqi")):
# 			this_object().set("nuqi",query("max_nuqi"));

# 	this_object().remove_all_enemy();
# 	this_object().set_temp("faint_by", query_temp("last_damage_from")); 
# 	riding = query_temp("is_riding")
# 	if (objectp(riding)):
# 		message_vision("$N一头从$n上面栽了下来！\n",this_object(), riding);
# 		delete_temp("is_riding");
# 		riding.delete_temp("is_rided_by");
# 		riding.move(environment());
		

# 	message("system", HIR + "\n你的眼前一黑，接着什么也不知道了....\n\n" + NOR, this_object());
# # 避免add_action的bug
# 	if(userp(this_object())):
# 		this_object().set_temp("noliving/unconcious", 1);
# 	else :
# 		this_object().disable_player(" <昏迷不醒>");

# 	set("jing", 0);
# 	set("qi", 0);

# 	set_temp("block_msg/all", 1);
# 	COMBAT_D.announce(this_object(), "unconcious");

# 	call_out("revive", random(100 - query("con")) + 30);


# func revive(quiet:int):
# 	remove_call_out("revive");
# 	while( environment().is_character() ):
# 		this_object().move(environment(environment()));
# # 避免add_action的bug
# 	if(userp(this_object())) :
# 		this_object().delete_temp("noliving");
# 	else :
# 		this_object().enable_player();

# 	if( !quiet ):
# 		COMBAT_D.announce(this_object(), "revive");
# 		set_temp("block_msg/all", 0);
# 		message("system", HIY + "\n慢慢地你终于又有了知觉....\n\n" + NOR, this_object());
# 	else:
# 		set_temp("block_msg/all", 0);


# func die():
# 	var corpse
# 	var killer
# 	var i
# 	var reason
# 	var riding

	
# 	if( !living(this_object()) || this_object().query_temp("noliving") ):
# 		revive(1);
# 	else :
# 		delete_temp("faint_by");
# 	# 所在房间定义了no_die，不允许死亡 
# 	if (environment().no_die(this_object())) :
# 		return;
# 	if( wizardp(this_object()) && query("env/immortal") ) :
# 		return;

# 	if(userp(this_object()) && this_object().is_ghost()):
# 		this_object().receive_curing("jing", 10);
# 		this_object().receive_curing("qi", 10);
# 		message_vision(HIW + "黑白索魂无常忽然出现，喝道：何方孤魂野鬼，快快随我前去阎罗大殿！\n" + NOR, this_object());
# 		this_object().move("/d/death/dadian");
# 		return;



# # 擂台比武不死
# 	if (file_name(environment(this_object())) == "/d/city/leitai"):
# 		message_vision(HIR + "公平子道：“已分胜负，不决生死。”\n" + NOR, this_object());
# 		this_object().move("/d/city/wudao4");
# 		this_object().receive_curing("jing", 10);
# 		this_object().receive_curing("qi", 10);
# 		return;
	
# 	if (userp(this_object())&& environment(this_object()).query("bwdhpk")):
# 		message_vision(HIR + "华山论剑，只分胜负，不决生死！。\n" + NOR, this_object());
# 		message_vision(HIR + "$N被抬了下去。\n" + NOR, this_object());
# 		killer = query_temp("last_damage_from")
# 		if( objectp(killer) ):
# 			killer.add_temp("bwdh_pknum",1);
# 			message("channel:chat", HIC + "【华山论剑】公平子："+this_object().query("name")+"不敌"+killer.query("name")+"，被迫退出华山论剑！\n" + NOR,users() );
	
# 	this_object().set("eff_jing", this_object().query("max_jing"));
# 	this_object().set("jing", this_object().query("max_jing"));
# 	this_object().set("eff_qi", this_object().query("max_qi"));
# 	this_object().set("qi", this_object().query("max_qi"));
# 	this_object().set("jingli", this_object().query("max_jingli"));
# 	this_object().set("neili", this_object().query("max_neili"));
# 	this_object().remove_all_killer();
# 	this_object().remove_all_enemy();
# 	this_object().delete_temp("bwdh_join");
# 	this_object().delete_temp("bwdh_pknum");
# 	this_object().delete_temp("bwdh_nknum");
# 	this_object().move(ENTRY_ROOM);
# 	return;
# 	riding = query_temp("is_riding")
# 	if (objectp(riding)):
# 		message_vision("$N一头从$n上面栽了下来！\n",this_object(), riding);
# 		delete_temp("is_riding");
# 		riding.delete_temp("is_rided_by");
# 		riding.move(environment());



# 	if (this_object().query_condition("huaiyun") > 0 && this_object().query_condition("huaiyun") < 2560 ):
# 		tell_object(this_object(),"你莫名地感到一阵心痛。。。\n");
# 	killer = query_temp("last_damage_from")	
# 	if( objectp(killer) && file_name(environment(killer)) == file_name(environment(this_object()))):
# # Clear all the conditions by normal death.
# 		if ( userp(this_object()) && userp(killer) && (!environment(this_object()).query("bwdhpk")) &&	\
# 			(time()-this_object().query("dietime")<13400 ||	time()-killer.query("killertime")<13400)):	
# 			this_object().set("eff_qi",10);
# 			this_object().set("eff_jing",10);
# 			this_object().set("qi",10);
# 			this_object().set("jing",10);
# 			message_vision(HIY + "\n天后仙子自云中飘然而下：一日不过四。不准频繁屠杀！\n" + NOR, this_object());
# 			message_vision(HIG + "挥起长袖，摆起一阵香风把"+this_object().name()+"刮回武庙。\n" + NOR, this_object());
# 			this_object().move("/d/city/wumiao");
# 			this_object().start_busy(10);
# 			return;

# 		this_object().clear_condition();
# 		this_object().set("dietime",time());
# 		this_object().add("normal_die", 1);
# # /* 杀手本次杀人时间 */
# 		if (userp(this_object())):
# 			killer.set("killertime", time());
# 		set_temp("my_killer", killer.query("id"));
# 		COMBAT_D.killer_reward(killer, this_object());
	
# 	else:
# 		if(userp(this_object())):

# 			this_object().set("last_die_msg","死得很离奇");
# 			reason=this_object().query_temp("die_reason")
# 			if (stringp(reason)):
# 				this_object().set("last_die_msg",reason);
# 			elif (stringp(this_object().query_temp("last_damage_from"))):
# 				reason=this_object().query_temp("last_damage_from")
# 				this_object().set("last_die_msg",reason+"死了");
# 			message("channel:rumor", HIM + "【谣言】"+"听说"+this_object().name()+ NOR + HIM + "死了，而且死得很离奇。\n" + NOR, users());

# 			this_object().delete("last_die_by_name");
# 			this_object().delete("last_die_by_id");
# 			this_object().delete_temp("die_reason");
# 			this_object().delete_temp("last_damage_from");
# 			this_object().add("dietimes",1);

# 	COMBAT_D.announce(this_object(), "dead");
# 	if (this_player().query_condition("huaiyun")):
# 		this_object().clear_condition("huaiyun");
# 	corpse = CHAR_D.make_corpse(this_object(), killer)
# 	if( objectp(corpse) ):
# 		corpse.move(environment());
# # 超度用的经验值
# 		corpse.set("combat_exp", this_object().query("combat_exp"));
# # 死者是玩家
# 		if (userp(this_object())):
# 			corpse.set("userp", 1);
# 		else:
# # 死者是任务对象
# 			if(this_object().query("quest")):
# 				corpse.set("quest", this_object().query("quest"));
# 			if(this_object().query("owner")):
# 				corpse.set("owner", this_object().query("owner"));
		
	

# 	this_object().remove_all_killer();
# 	all_inventory(environment()).remove_killer(this_object());

# 	this_object().dismiss_team();
# 	if( userp(this_object()) ):
# #		if (this_object().is_busy())
# #			this_object().interrupt_me();
# 		this_object().remove_busy();
# 		set("jing", 1);	set("eff_jing", 1);
# 		set("qi", 1);	set("eff_qi", 1);
# 		ghost = 1;
# 		this_object().move(DEATH_ROOM);
# 		DEATH_ROOM.start_death(this_object());
	
# 	else:
# #浩劫系统的触发条件
# 		LOGIN_D.add_dienpc();
# 		destruct(this_object());


func max_food_capacity() :
 	return query_weight() / 200;

func max_water_capacity() :
 	return query_weight() / 200;

# func reincarnate():
# 	ghost = 0;
# 	set("eff_jing", query("max_jing"));
# 	set("eff_qi", query("max_qi"));
# 	set("food",max_food_capacity());
# 	set("water",max_water_capacity());

# func heal_up():
# 	var update_flag
# 	var i
# 	var my

# #	if( this_object().is_fighting() ) return -1;
# 	update_flag = 0;

# 	my = query_entire_dbase();

# 	#就是下面这两句话！！！！！！！！！！！！！
# 	#就是下面这两句话！！！！！！！！！！！！！
# 	#就是下面这两句话！！！！！！！！！！！！！
# 	#就是下面这两句话！！！！！！！！！！！！！

# 	if (environment(this_object()) && environment(this_object()).is_chat_room() && this_object().query("env/halt_age") ):
# 		return 0;

# 	if( my["water"] > 0 ) :
# 		my["water"] -= 1
# 		update_flag += 1
# 	if( my["food"] > 0 ) :
# 		my["food"] -= 1
# 		update_flag += 1
# 	#人和宠物如果没饮水，不能恢复身体。
# 	if( my["water"] < 1 && (userp(this_object()) || this_object().query("ownername")) ):
# 		return update_flag;
# 	#人和宠物如果没食物，不能恢复身体。
# 	if( my["food"] < 1 && (userp(this_object()) || this_object().query("ownername")) ):
# 		return update_flag;

# 	my["jing"] += my["con"] / 3 + my["max_jingli"] / 10;
# 	if( my["jing"] >= my["eff_jing"] ):
# 		my["jing"] = my["eff_jing"];
# 		if( my["eff_jing"] < my["max_jing"] ):
# 			my["eff_jing"] += 1 
# 			update_flag +=1
# 	else :
# 		update_flag +=1

# 	my["qi"] += my["con"] / 3 + my["max_neili"] / 10;
# 	if( my["qi"] >= my["eff_qi"] ):
# 		my["qi"] = my["eff_qi"];
# 		if( my["eff_qi"] < my["max_qi"] ):
# 			my["eff_qi"] +=1 
# 			update_flag+=1
# 	else :
# 		update_flag+=1

# 	if( my["max_jingli"] && my["jingli"] < my["max_jingli"] ):
# 		my["jingli"] += this_object().query_skill("taoism", 1)/20;
# 		if(my["jingli"]>my["max_jingli"]) :
# 			my["jingli"]=my["max_jingli"];
# 		update_flag+=1


# 	if( my["max_neili"] && my["neili"] < my["max_neili"] ):
# 		my["neili"] += this_object().query_skill("force", 1)/2 + this_object().query("sta")/3;
# 		if(my["neili"] > my["max_neili"]) :
# 			my["neili"] = my["max_neili"];
# 		update_flag+=1


# 	if( my["max_tili"] && my["tili"] < my["max_tili"] ):
# 		my["tili"] += this_object().query_skill("parry", 1)/2 + this_object().query("sta")/3;
# 		if(my["tili"] > my["max_tili"]) :
# 			my["tili"] = my["max_tili"];
# 		update_flag+=1


# 	return update_flag;

# ########################################################### F_FINANCE ##############################

# # can_afford() checks if this_object() can afford a price, it returns:
# #
# #	0:	cannot afford.
# #	1:	can afford with proper money(coins).
# #	2: 	can afford, but don't have enough proper money(coins).
# #
# func can_afford(amount):
# 	var total;
# 	var gold
# 	var silver
# 	var coin;

# 	gold = present("gold_money");
# 	silver = present("silver_money");
# 	coin = present("coin_money");

# 	total = 0;
# 	if( gold ) :
# 		total += gold.value();
# 	if( silver ) :
# 		total += silver.value();
# 	if( coin ) :
# 		total += coin.value();

# 	if( total < amount ) :
# 		return 0;

# 	if( coin ) :
# 		amount -= coin.value();
# 	if( amount <= 0 ) :
# 		return 1;
# 	elif( amount % 100 ) :
# 		return 2;

# 	if( silver ) :
# 		amount -= silver.value();
# 	if( amount <= 0 ) :
# 		return 1;
# 	elif( amount % 10000 ) :
# 		return 2;

# 	return 1;


# func pay_money(amount):
# 	var total;
# 	var gold
# 	var silver
# 	var coin;

# 	gold = present("gold_money");
# 	silver = present("silver_money");
# 	coin = present("coin_money");

# 	total = 0;
# 	if( gold ) :
# 		total += gold.value();
# 	if( silver ) :
# 		total += silver.value();
# 	if( coin ) :
# 		total += coin.value();

# 	if( total < amount ) :
# 		return 0;

# 	if( gold && amount > 10000 ) :
# 		if( gold.value() >= amount ) :
# 			gold.add_amount(-amount/10000);
# 			amount %= 10000;
# 		else :
# 			amount -= gold.value();
# 			gold.set_amount(0);


# 	if( silver && amount > 100 ) :
# 		if( silver.value() >= amount ) :
# 			silver.add_amount(-amount/100);
# 			amount %= 100;
# 		else :
# 			amount -= silver.value();
# 			silver.set_amount(0);

# 	if( coin && amount > 0 ) :
# 		if( coin.value() >= amount ) :
# 			coin.add_amount(-amount);
# 			amount = 0;
# 		else :
# 			error("F_FINANCE: Not enough money!\n");

# 	if( amount > 0 ) :
# 		error("F_FINANCE: Not enough money!\n");



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

	# CHAR_D.setup_char( this_object() );

func heart_beat():
	var wimpy_ratio
	var cnd_flag=0;
	var  my = {};
	var  ob;

# 	my = query_entire_dbase();

# 	# If we are dying because of mortal wounds?
# 	if( my["eff_qi"] < 0 || my["eff_jing"] < 0):
# 		remove_all_enemy();
# 		die();
# 		return;
	
# 	# If we're dying or falling unconcious?
# 	if( my["qi"] < 0 || my["jing"] < 0):
# 		remove_all_enemy();
# 		if( !living(this_object()) || this_object().query_temp("noliving") ):
# 			die();
# 		else :
# 			unconcious();
# 		return;
	
# 	# Do attack if we are fighting.
# 	if( is_busy() ):
# 		continue_action();
# 		# We don't want heart beat be halt eventually, so return here.
# 		return;
# 	else:
# 		# Is it time to flee?
# 		wimpy_ratio = int(query("env/wimpy"))
# 		if( is_fighting() && intp(wimpy_ratio) && wimpy_ratio > 0 &&	\
# 			( my["qi"] * 100 / my["max_qi"] <= wimpy_ratio ||			\
# 			my["jing"] * 100 / my["max_jing"] <= wimpy_ratio) ):
# 			GO_CMD.do_flee(this_object());							
# 		# Do attack or clean up enemy if we have fleed.
# 		if( living(this_object()) && !this_object().query_temp("noliving") ):
# 			attack();

# 	if( !userp(this_object()) ):
# 		if( living(this_object()) ):
# 			this_object().chat();
# 		# chat() may do anything -- include destruct(this_object())
# 		if( !this_object() ) :
# 			return;	

# 	if (this_object().query("env/no_fight") && this_object().is_killing()) :
# 		this_object().delete("env/no_fight");
# 	tick = tick - 1
# 	if( tick <=0) :
# 		return;
# 	else:
# 		tick = 5 + random(10);

# 	if (!environment()||!environment().is_chat_room() || !query("env/halt_age")) :
# 		cnd_flag = update_condition();

# 	# If we are compeletely in peace, turn off heart beat.
# 	# heal_up() must be called prior to other two to make sure it is called
# 	# because the && operator is lazy :P
# 	if( ((cnd_flag & CND_NO_HEAL_UP) || !heal_up()) && !is_fighting() && !interactive(this_object())):
# 		if( environment() ) :
# 			ob = first_inventory(environment());
# 			while(ob && !interactive(ob)):
# 				ob = next_inventory(ob);
# 		if( !ob ) :
# 			set_heart_beat(0);

# 	if( !interactive(this_object()) ) :
# 		return;

# 	# Make us a bit older. Only player's update_age is defined.
# 	# Note: update_age() is no need to be called every heart_beat, it
# 	#       remember how much time has passed since last call.
# 	this_object().update_age();

# 	if(query_idle(this_object()) > IDLE_TIMEOUT && !wizardp(this_object())):
# 		this_object().user_dump(DUMP_IDLE);


# ###########	wiz func .not used.


# # func visible(object ob):
# # {
# # 	int lvl, invis;

# # 	lvl = wiz_level(this_object());

# # 	if( lvl > wiz_level(ob) ) return 1;
# # 	if(wizardp(ob)) invis = ob.query("env/invisibility");
# # 	else invis=0;
# # 	if( intp(invis) && (invis > lvl) ) return 0;

# # 	if( ob.is_ghost() ) {
# # 		if( is_ghost() ) return 1;
# # 		if( query_temp("apply/astral_vision") ) return 1;
# # 		return 0;
# # 	}
# # 	return 1;
# # }

# # -------------- props ----------
# #var max_food_capacity
# #var max_water_capacity
# #func max_food_capacity():
# #	max_food_capacity = query("str") * 5 + 300
# #	return max_food_capacity
# #
# #func max_water_capacity():
# #	max_food_capacity = query("int") * 5 + 300
# #	return max_food_capacity
	
# #var skills = {}
# #var test_skills = {}
# #var map_skills = {}
# #var prepare_skills = {}
# #
# #func set_skill(key:String,value):
# ##	if !skills:skills={}
# #	skills[key] = value
# #
# #func get_skill(key:String):
# #	return skills[key]
# #
# #func map_skill( key:String,value):
# ##	if !map_skills:map_skills={}
# #	map_skills[key] = value
# #
# #func prepare_skill(key:String,value):
# ##	if !prepare_skills:prepare_skills={}
# #	prepare_skills[key] = value
# #
# #func query_skill(skill:String,key:String):
# #	if skills.has(skill) and skills[skill].has(key):
# #		return skills[skill][key]
# #	else:
# #		return false
		
		

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
#	print_debug(self.query("objects"),self.query("objects")[path])
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
# #
# #	if( !stringp(string = query("short")) ):
# #		string = name(raw) + "(" + capitalize(query("id")) + ")";
# #
# #	if( !this_object().is_character() ) :
# #		return string;
# #
# #	if (!raw) :
# #		if (query_temp("pending/exercise") != 0):
# #			return name() + "正坐在地下修炼内力。";
# #		elif (query_temp("pending/respirate") != 0):
# #			return name() + "正坐在地下吐纳炼精。";
# #	}
# #
# #        if( !raw && sizeof(mask = query_temp("apply/short")) ):
# #                str = str(mask[sizeof(mask)-1]);
# ##	if( !raw && stringp(str1 = (string)query_temp("apply/short")) ) {
# ##		str = (string)mask[sizeof(mask) - 1];
# ##		return (string)query_temp("apply/short");
# ##		if (stringp(str1))
# ##		  	str += str1;
# ##	}
# #	else: 
# #		if( stringp(nick = query("nickname")) ):
# #			str = sprintf("「%s」%s", nick, str);
# #
# #		if( stringp(title = query("title")) ) :
# #			# 叛师过的无门派人士改称隐士。Modified by Spacenet@FXLT
# #			if (title == "普通百姓" && query("betrayer")):
# #				title = "隐士";
# #			str = sprintf("%s%s%s", title,(nick?"":" "), str);
# #		if ( mapp(party = query("party")) ) :
# #			party_title = party["party_name"] + party["rank"];
# #			str=sprintf("%s%s%s%s", party_title,(title?"":""),(nick?"":" "), str);
# #		if ( stringp(degree = query("degree")) ) :
# #			str = sprintf("%s%s%s%s%s",degree,(party_title?"":""),(title?"":""),(nick?"":" "), str);
# #		if ( stringp(guard = query("guard")) ) :
# #			str = sprintf("%s%s%s%s%s%s",guard,(degree?"":""),(party_title?"":""),(title?"":""),(nick?"":" "), str);
# #
# #	if( !raw ) :
# #		if( this_object().is_ghost() ) :
# #			str = HIB "(鬼气) " NOR + str;
# #		# if( query_temp("netdead") ) :
# #		# 	str += HIG" <断线中>" NOR;
# #		# if( in_input() ) str += HIC" <输入文字中>" NOR;
# #		# if( in_edit() ) str += HIY" <编辑档案中>" NOR;
# #		# if( query_temp("boss_screen") ) :
# #		# 	str += HIG" <逃避老板中>" NOR;
# #		if( query_temp("bixie/cimu") ) :
# #			str += HIR + " <失明中>" + NOR;
# #		if( query_temp("noliving/sleeped") ) :
# #			str += HIR + " <睡梦中>"  + NOR;
# #		if( query_temp("noliving/fakedie") ) :
# #			str += HIR + " <装死中>"  + NOR;
# #		if( query_temp("noliving/jingzuo") ) :
# #			str += HIR + " <静坐中>"  + NOR;
# #		if( query_temp("noliving/journey") ) :
# #			str += HIR + " <旅途中>"  + NOR;
# #		if( query_temp("noliving/unconcious") ):
# #			str += HIR + " <昏迷不醒>" +  NOR;
# #		if( interactive(this_object()) && query_idle(this_object())>120):
# #			str += HIM +  " <发呆中>"  + NOR;
# #		if( !living(this_object()) ):
# #			str += HIR + query("disable_type") + NOR;
# #	return str;
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
	

# ######################################### F_SKILL ########################

var skills;
var learned;
var skill_map;
var skill_prepare;

func query_skills() :
	return skills
func query_learned() :
	return learned

func set_skill(skill:String, val:int = 0):
#	if( !find_object(SKILL_D(skill)) &&	file_size(SKILL_D(skill)+".c") < 0 ):
#		error("F_SKILL: No such skill (" + skill + ")\n");
	if( !mapp(skills) ) :
		skills = {skill: val}
	else :
		skills[skill] = val;

func delete_skill(skill:String):
	if( mapp(skills) ) :
#		map_delete(skills, skill);
		skills.erase(skill)
		if( mapp(learned) ) :
#			map_delete(learned, skill);
			learned.ease(skill)
			return undefinedp(learned[skill]);
		return undefinedp(skills[skill]);
	return 0;

# This function 'map' a skill <skill> to another skill <mapped_to>.
# If 2nd argument not given, cancel the mapped skill <skill>.
func map_skill(skill:String, mapped_to:String):
	if( !mapped_to && mapp(skill_map) ):
#		map_delete(skill_map, skill);
		skill_map.ease(skill)
		return;

# 	if( !find_object(SKILL_D(skill)) &&	file_size(SKILL_D(skill)+".c") < 0 ):
# 		error("F_SKILL: No such skill (" + skill + ")\n");

# 	if( !mapp(skills) || undefinedp(skills[mapped_to]) ):
# 		return;
		
	if( !mapp(skill_map) ) :
		skill_map = {skill: mapped_to}
	else :
		skill_map[skill] = mapped_to;

# This function 'prepare' a skill <skill> to another skill <mapped_to>.
# If 2nd argument not given, cancel the prepared skill <skill>.
func prepare_skill(skill:String, mapped_to:String):
	if( !mapped_to && mapp(skill_prepare) ) :
#		map_delete(skill_prepare, skill);
		skill_prepare.ease(skill)
		return;

# 	if( !find_object(SKILL_D(skill)) && file_size(SKILL_D(skill)+".c") < 0 ):
# 		error("F_SKILL: No such skill (" + skill + ")\n");

# 	if( !mapp(skills) || undefinedp(skills[mapped_to]) ):
# 		return;
		
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

# func query_skill(skill:String, raw:int = 0):
# 	if( !raw ) :
# 		var s;
		
# 		s = query_temp("apply/" + skill);
# 		if( mapp(skills) ) :
# 			s += skills[skill] / 2;
# 			if( mapp(skill_map) ):
# 				s += skills[skill_map[skill]];
# 		return s;
# 	if( mapp(skills) && !undefinedp(skills[skill]) ) :
# 		return skills[skill];
# 	return 0;

func query_skill_map():
	return skill_map;

func query_skill_prepare():
	return skill_prepare;

# func skill_death_penalty():
# 	var sk;
# 	var i;

# 	if( wizardp(this_object()) || !mapp(skills) ) :
# 		return 0;

# 	sk = keys(skills);
# # /*
# # 	if( !mapp(learned) )
# # 		for(i = 0; i<sizeof(sk); i++)
# # 		{
# # 			skills[sk[i]]--;
# # 			if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
# # 		}
# # 	else
# # 		for(i = 0; i<sizeof(sk); i++)
# # 		{
# # #			if( (int)learned[sk[i]] > (skills[sk[i]]+1) * (skills[sk[i]]+1) / 2 )
# # #				map_delete(learned, sk[i]);
# # #			else {
# # #				skills[sk[i]]--;
# # #				if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
# # #			}
# # 			skills[sk[i]]--;
# # 			map_delete(learned,sk[i]);
# # 			if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
# # 		}
# # */
# 		# for(i = 0; i<sizeof(sk); i++)
# 	for i in range(sizeof(sk)) :
# 		skills[sk[i]] = skills[sk[i]] - 1;
# 		if( skills[sk[i]]<0  || (skills[sk[i]]==0 && learned[sk[i]]==0) ):
# 			map_delete(skills, sk[i]);
# 			if (mapp(learned)):
# 				map_delete(learned,sk[i]);


# 	skill_map = 0;
# 	return 1;


# func skillreincarnate():
# 	var sk
# 	var i

# 	sk = keys(skills);
# #	for(i = 0; i<sizeof(sk); i++) :
# 	for i in range(sizeof(sk)) :
# 		skills[sk[i]] = skills[sk[i]] + 1;
# 	log_file("skill_re", sprintf("[%s] %s eat %s \n", ctime(time()), geteuid(this_object()),base_name(previous_object())));
# 	return 1;

# func improve_skill(skill:String, amount:int, weak_mode:int):
# 	var spi;

# #只有玩家和好学的npc才能学习。比如宠物或玩家小孩等。
# 	if (!userp(this_object()) && !this_object().query("curiousness")):
# 		return; 
# 	if( !find_object(SKILL_D(skill)) && file_size(SKILL_D(skill)+".c") < 0 ):
# 		error("F_SKILL: No such skill (" + skill + ")\n");

# 	if( !weak_mode || !userp(this_object()) ) :
# 		if( !mapp(skills) ) :
# 			skills = ([]);
# 		if( undefinedp(skills[skill]) ) :
# 			skills[skill] = 0;


# 	# Give learning penalty to those learning too much skills.
# 	spi = this_object().query_spi();
# 	if( sizeof(learned) > spi ):
# 		amount /= sizeof(learned) - spi;

# 	if( !amount ) :
# 		amount = 1;

# 	if( !mapp(learned) ) :
# 		learned = {skill : amount};
# 	else :
# 		learned[skill] += amount;

# 	if( (!weak_mode || !userp(this_object())) && learned[skill] > (skills[skill] + 1) * (skills[skill] + 1) ) :
# 		skills[skill] = skills[skill] + 1;
# 		learned[skill] = 0;
# 		tell_object(this_object(), HIC + "你的「" + to_chinese(skill) + "」进步了！\n" + NOR);
# 		SKILL_D(skill).skill_improved(this_object());


# ###############################################  F_TEAM #########


# var leader
# var team

# func set_leader(ob):
# 	if( ob==this_object() ):
# 		error("set_leader: Cannot set this_object() as leader.\n");
# 	leader = ob;

# func query_leader() :
# 	return leader

# func follow_path(dir:String):
# 	#if( (origin()==ORIGIN_LOCAL) || (origin()==ORIGIN_CALL_OUT) ) {
# 		this_object().remove_all_enemy();
# 		return GO_CMD.main(this_object(), dir);
# 	#}

# func follow_me(ob, dir:String):
# 	if( !living(this_object()) || this_object().query_temp("noliving") || ob==this_object() ) :
# 		return 0;

# 	if( ob==leader || (query("pursuer") && this_object().is_killing(ob.query("id")))) :
# 		if( random(ob.query_skill("move")) > this_object().query_skill("move") ) :
# 			remove_call_out("follow_path");
# 			call_out("follow_path", 1, dir);
# 			return 1;

# 		return follow_path(dir);


# func add_team_member(ob):
# 	if( ob==this_object() ) :
# 		return 0;

# 	if( arrayp(team) ) :
# 		if( member_array(ob, team)==-1 ) :
# 			team += [ ob ];
# 			# for(int i=sizeof(team)-1; i>=0; i--)
# 			# TODO: TEST
# 			for i in range(team,0) :
# 				team[i].set_team(team);
# 		else:
# 			return 0;
# 	else :
# 		team = [ this_object(), ob ];
# 		ob.set_team(team);

# 	return 1;


# func is_team_leader():
# 	return arrayp(team) && team[0]==this_object();

# func set_team(t):
# 	team = t;



# # TODO: 数组 方法.  应该比这更好实现.	
# func dismiss_team(ob):
# 	var i;

# 	if( !arrayp(team) ) :
# 		return 0;
# 	team -= [ 0 ];
	
# 	if( !ob ) :
# 		if( team[0]==this_object() ) :
# 			# for(i=1; i<sizeof(team); i++)
# 			for i in range(team):
# 				team[i].set_team(0);
# 		else :
# 			# for(i=0; i<sizeof(team); i++)
# 			for i in range(team) :
# 				team[i].dismiss_team( this_object() );
		
# 		team = 0;
# 	else :
# 		team -= [ ob ];

# 	return 1;

# func query_team():
# 	return team;




##################### tools ##############

func this_player():
	return self
	
func call_out(arg1=1,arg2=1,agr3=1):
	pass	

# 将整数数字转为中文文字	
func chinese_number(n:int):
	var number_str = str(n)
	var l = number_str.length()
	var output = []
	for i in range(l):
		number_str[i] = swap_to_font(number_str[i])
	return number_str
	
# 配合上面转化
func swap_to_font(number):
	match number:
		"1":return "一"
		"2":return "二"
		"3":return "三"
		"4":return "四"
		"5":return "五"
		"6":return "六"
		"7":return "七"
		"8":return "八"
		"9":return "九"
		"0":return "〇"
		_:return "X"	
	
	
func member_array(ob,m_array:Array):
	var num = m_array.find(ob)
	return num
func this_object(ob=self):
	return ob
	
### todo	
# func this_player(ob=self):
# 	return ob	
	
# func call_out(funcname, delay, fun):
# 	pass
			
# func random(n:int):
# 	return randi()%n
	
# func dir(ob = self):
# 	return ob.get_script().get_path().get_base_dir() + "/"	

# func file_name(ob = self):
# 	return ob.get_script().get_path()
	
# func arrayp(a):
# 	return a is Array	
	
# func mapp(d):
# 	return d is Dictionary
	
# func stringp(s):
# 	return s is String	

# func intp(i):
# 	return i is int
	
# func undefinedp(u):
# 	return !u		
	
# func objectp(ob):
# 	return true
	
# # todo	
# func userp(ob):
# 	return false
		
# func functionp(fun,ob=self):
# 	return ob.has_method(fun)		
	
# func evaluate(interrupt,fun,args=[],ob=self):	
# 	if ob.has_method(fun) :
# 		call(fun,args)
		
# func keys(d:Dictionary):
# 	return d.keys()

# # todo test
# func sprintf(string,arg1=null,arg2=null,arg3=null,arg4=null):
# 	string.format(arg1,arg2,arg3,arg4)
# 	print_debug(string)
# 	return string

# # todo 
# func living(ob):
# 	return true
	
# # todo
# var fighting = false	
# func is_fighting():
# 	return fighting	or query("fighting")
	
# func sizeof(a):
# 	return a.size()	