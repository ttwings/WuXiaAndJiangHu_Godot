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
	
var _heartbeat_active = false
var _heartbeat_interval = 2.0  # 心跳间隔（秒）

func set_heart_beat(i: int) -> void:
	if i > 0:
		if not _heartbeat_active:
			_heartbeat_active = true
			_start_heartbeat_loop()
	else:
		_heartbeat_active = false

func _start_heartbeat_loop() -> void:
	while _heartbeat_active:
		var tree = Engine.get_main_loop()
		await tree.create_timer(_heartbeat_interval).timeout
		if _heartbeat_active:
			heart_beat()

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
	
## 新入门的弟子的title是“弟子”，privs是0
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
	family["enter_time"] = Time.get_time_dict_from_system();
	ob.set("family", family);
	ob.assign_apprentice("弟子", 0);
	return 1;


######################################### F_ATTACK #############################

# const MAX_OPPONENT = 4
var enemy = [];
var killer = [];

# prototypes

func query_enemy():
	return enemy

func query_killer():
	return killer

# 是否在战斗中（或与某对象战斗）
func is_fighting(ob = self) -> bool:
	if not ob:
		return enemy.size() > 0
	return ob in enemy

# 是否在杀某人
func is_killing(id: String = "") -> bool:
	if id == "":
		return killer.size() > 0
	return id in killer

# 发起搏斗
func fight_ob(ob) -> void:
	if not ob or ob == self:
		return
	if ob.environment() != self.environment():
		return
	set_heart_beat(1)
	if ob not in enemy:
		enemy.append(ob)

# 发起击杀
func kill_ob(ob) -> void:
	if not ob or ob == self:
		return
	if query_temp("guardfor") == ob:
		tell_object(self, HIR + "不能杀你要保护的人！\n" + NOR)
		return
	var env = self.environment()
	if env and env.query("no_fight"):
		tell_object(self, "这里不能战斗。\n")
		return
	if env != ob.environment():
		return

	var ob_id = ob.query("id")
	if is_killing(ob_id) and is_fighting(ob):
		return

	tell_object(ob, HIR + "看起来" + name() + "想杀死你！\n" + NOR)
	if ob_id not in killer:
		killer.append(ob_id)
	delete("env/no_fight")
	if ob.has_method("delete"):
		ob.delete("env/no_fight")

	fight_ob(ob)

# 清理无效敌人
func clean_up_enemy() -> void:
	if enemy.size() <= 0:
		return
	var my_env = self.environment()
	var new_enemy = []
	for ob in enemy:
		if ob == null:
			continue
		if not ob is Char:
			continue
		if ob.environment() != my_env:
			continue
		if not ob.living() and not is_killing(ob.query("id")):
			continue
		new_enemy.append(ob)
	enemy = new_enemy

# 选择一个攻击目标
func select_opponent():
	clean_up_enemy()
	if enemy.size() <= 0:
		return null
	if enemy.size() == 1:
		return enemy[0]
	# 优先攻击正在杀我的人
	for ob in enemy:
		if is_killing(ob.query("id")):
			return ob
	return enemy[randi() % enemy.size()]

# 停止与某对象战斗
func remove_enemy(ob) -> bool:
	if is_killing(ob.query("id")):
		return false
	if ob in enemy:
		enemy.erase(ob)
	return true

# 停止杀某对象
func remove_killer(ob) -> bool:
	var ob_id = ob.query("id")
	if is_killing(ob_id):
		killer.erase(ob_id)
		remove_enemy(ob)
		return true
	return remove_enemy(ob)

# 停止所有战斗（killer 保留）
func remove_all_enemy() -> void:
	var size = enemy.size()
	for i in range(size):
		var ob = enemy[i]
		if ob and ob is Char:
			ob.remove_enemy(self)
	enemy = []

# 停止所有战斗和击杀
func remove_all_killer() -> void:
	killer = []
	var size = enemy.size()
	for i in range(size):
		var ob = enemy[i]
		if ob and ob is Char:
			ob.remove_killer(self)
	enemy = []

# 攻击 - 在心跳中调用
func attack() -> void:
	clean_up_enemy()
	if enemy.size() <= 0:
		return
	var victim = select_opponent()
	if not victim:
		return
	if not victim.living():
		remove_enemy(victim)
		return
	COMBAT_D.fight(self, victim)


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
# 膂力 -- 出手重
func query_str() -> int:
	return int(query("str")) + int(query_temp("apply/strength"))

# 悟性 -- 学习和读书快
func query_int() -> int:
	return int(query("int")) + int(query_temp("apply/intelligence"))

# 根骨 -- 气血恢复快
func query_con() -> int:
	return int(query("con")) + int(query_temp("apply/constitution"))

# 身法 -- 躲避快
func query_dex() -> int:
	return int(query("dex")) + int(query_temp("apply/dexerity"))

# 耐力 -- 内力恢复快
func query_sta() -> int:
	return int(query("sta")) + int(query_temp("apply/stamina"))

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
var ghost = 0

func is_ghost():
	return ghost

func set_ghost(i):
	ghost = i

# receive_damage - 受到伤害（扣气血/精气）
func receive_damage(type: String, damage: int, who = null) -> int:
	if damage < 0:
		push_error("F_DAMAGE: 伤害值为负值。")
		return 0
	if type != "jing" and type != "qi":
		push_error("F_DAMAGE: 伤害种类错误(只能是 jing, qi 其中之一)。")
		return 0

	if who != null:
		if typeof(who) == TYPE_OBJECT:
			set_temp("last_damage_from", who)
		elif typeof(who) == TYPE_STRING:
			set_temp("die_reason", who)

	var imp = damage / 5
	if query("max_nuqi") and is_fighting():
		add("nuqi", imp)
		if query("nuqi") > query("max_nuqi"):
			set("nuqi", query("max_nuqi"))

	var val = query(type) - damage
	if val >= 0:
		set(type, val)
	else:
		set(type, -1)

	set_heart_beat(1)
	return damage


# receive_wound - 受到重伤（扣有效气血）
func receive_wound(type: String, damage: int, who = null) -> int:
	if damage < 0:
		push_error("F_DAMAGE: 伤害值为负值。")
		return 0
	if type != "jing" and type != "qi":
		push_error("F_DAMAGE: 伤害种类错误(只能是 jing, qi 其中之一)。")
		return 0

	if who != null:
		if typeof(who) == TYPE_OBJECT:
			set_temp("last_damage_from", who)
		elif typeof(who) == TYPE_STRING:
			set_temp("die_reason", who)

	var imp = damage / 3
	if query("max_nuqi") and is_fighting():
		add("nuqi", imp)
		if query("nuqi") > query("max_nuqi"):
			set("nuqi", query("max_nuqi"))

	var val = query("eff_" + type) - damage
	if val >= 0:
		set("eff_" + type, val)
	else:
		set("eff_" + type, -1)
		val = -1

	if query(type) > val:
		set(type, val)

	set_heart_beat(1)
	return damage


# receive_heal - 恢复气血/精气（不超过有效上限）
func receive_heal(type: String, heal: int) -> int:
	if heal < 0:
		push_error("F_DAMAGE: 恢复值为负值。")
		return 0
	if type != "jing" and type != "qi":
		push_error("F_DAMAGE: 恢复种类错误(只能是 jing, qi 其中之一)。")
		return 0
	var val = query(type) + heal
	if val > query("eff_" + type):
		set(type, query("eff_" + type))
	else:
		set(type, val)
	return heal


# receive_curing - 治疗（恢复有效气血上限）
func receive_curing(type: String, heal: int) -> int:
	if heal < 0:
		push_error("F_DAMAGE: 恢复值为负值。")
		return 0
	if type != "jing" and type != "qi":
		push_error("F_DAMAGE: 恢复种类错误(只能是 jing, qi 其中之一)。")
		return 0

	var val = query("eff_" + type)
	var max_ = query("max_" + type)

	if val + heal > max_:
		set("eff_" + type, max_)
		return max_ - val
	else:
		set("eff_" + type, val + heal)
		return heal


# unconcious - 昏迷
func unconcious():
	var defeater = query_temp("last_damage_from")
	if defeater and typeof(defeater) == TYPE_OBJECT:
		if COMBAT_D and COMBAT_D.has_method("winner_reward"):
			COMBAT_D.winner_reward(defeater, self)

	remove_all_enemy()
	set_temp("faint_by", query_temp("last_damage_from"))

	tell_object(self, HIR + "\n你的眼前一黑，接着什么也不知道了....\n\n" + NOR)
	set("jing", 0)
	set("qi", 0)

	set_temp("block_msg/all", 1)
	if COMBAT_D and COMBAT_D.has_method("announce"):
		COMBAT_D.announce(self, "unconcious")

	# 30~100 秒后苏醒（取决于体质）
	var con = query("con")
	if con == null or con == 0:
		con = 10
	var delay = max(30, 100 - con)
	call_deferred("_delayed_revive", delay)


func _delayed_revive(delay: int):
	var tree = Engine.get_main_loop()
	await tree.create_timer(delay).timeout
	revive(0)


# revive - 苏醒
func revive(quiet: int = 0):
	set_temp("block_msg/all", 0)
	if not quiet:
		if COMBAT_D and COMBAT_D.has_method("announce"):
			COMBAT_D.announce(self, "revive")
		tell_object(self, HIY + "\n慢慢地你终于又有了知觉....\n\n" + NOR)


# die - 死亡
func die():
	var killer = query_temp("last_damage_from")
	var env = environment()

	# 清除战斗状态
	remove_all_killer()
	remove_all_enemy()

	if killer and typeof(killer) == TYPE_OBJECT:
		set_temp("my_killer", killer.query("id"))
		if COMBAT_D and COMBAT_D.has_method("killer_reward"):
			COMBAT_D.killer_reward(killer, self)

	if COMBAT_D and COMBAT_D.has_method("announce"):
		COMBAT_D.announce(self, "dead")

	# 玩家死亡：变为鬼魂，NPC 死亡：销毁
	if userp(self):
		set("jing", 1)
		set("eff_jing", 1)
		set("qi", 1)
		set("eff_qi", 1)
		ghost = 1
		tell_object(self, HIR + "\n你死了....\n\n" + NOR)
	else:
		# NPC 死亡：从环境移除
		message_vision("$N死了！\n", self)
		if env:
			env.remove_object(self)
		set_heart_beat(0)


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

# heal_up - 心跳恢复（消耗食物水，恢复气血/内力）
func heal_up() -> int:
	var update_flag = 0
	var my = query_entire_dbase()
	if not my is Dictionary:
		return 0

	if my.get("water", 0) > 0:
		my["water"] -= 1
		update_flag += 1
	if my.get("food", 0) > 0:
		my["food"] -= 1
		update_flag += 1

	# 没水/没食物不能恢复（人和宠物）
	if my.get("water", 0) < 1 and (userp(self) or query("ownername")):
		return update_flag
	if my.get("food", 0) < 1 and (userp(self) or query("ownername")):
		return update_flag

	# 恢复精气
	my["jing"] += int(my.get("con", 0)) / 3 + int(my.get("max_jingli", 0)) / 10
	if my["jing"] >= my.get("eff_jing", 0):
		my["jing"] = my.get("eff_jing", 0)
		if my.get("eff_jing", 0) < my.get("max_jing", 0):
			my["eff_jing"] += 1
			update_flag += 1
	else:
		update_flag += 1

	# 恢复气血
	my["qi"] += int(my.get("con", 0)) / 3 + int(my.get("max_neili", 0)) / 10
	if my["qi"] >= my.get("eff_qi", 0):
		my["qi"] = my.get("eff_qi", 0)
		if my.get("eff_qi", 0) < my.get("max_qi", 0):
			my["eff_qi"] += 1
			update_flag += 1
	else:
		update_flag += 1

	# 恢复精力
	if my.get("max_jingli", 0) and my.get("jingli", 0) < my.get("max_jingli", 0):
		my["jingli"] += int(query_skill("taoism", 1)) / 20
		if my["jingli"] > my["max_jingli"]:
			my["jingli"] = my["max_jingli"]
		update_flag += 1

	# 恢复内力
	if my.get("max_neili", 0) and my.get("neili", 0) < my.get("max_neili", 0):
		my["neili"] += int(query_skill("force", 1)) / 2 + int(query("sta")) / 3
		if my["neili"] > my["max_neili"]:
			my["neili"] = my["max_neili"]
		update_flag += 1

	# 恢复体力
	if my.get("max_tili", 0) and my.get("tili", 0) < my.get("max_tili", 0):
		my["tili"] += int(query_skill("parry", 1)) / 2 + int(query("sta")) / 3
		if my["tili"] > my["max_tili"]:
			my["tili"] = my["max_tili"]
		update_flag += 1

	return update_flag

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

func heart_beat() -> void:
	if not living():
		return

	var my = query_entire_dbase()
	if not my is Dictionary:
		return

	# 死亡检测
	var eff_qi = int(my.get("eff_qi", 0))
	var eff_jing = int(my.get("eff_jing", 0))
	if eff_qi < 0 or eff_jing < 0:
		remove_all_enemy()
		die()
		return

	var qi = int(my.get("qi", 0))
	var jing = int(my.get("jing", 0))
	if qi < 0 or jing < 0:
		remove_all_enemy()
		unconcious()
		return

	# 忙碌中
	if is_busy():
		continue_action()
		return

	# 战斗中：攻击
	if living() and not query_temp("noliving"):
		if is_fighting():
			attack()

	# NPC 聊天
	if not userp(self) and living():
		if has_method("chat"):
			call("chat")

	# 恢复气血
	heal_up()


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

func query_skill(skill: String, raw: int = 0) -> int:
	if not raw:
		var s = 0
		s = int(query_temp("apply/" + skill))
		if skills is Dictionary and skills.has(skill):
			s += int(skills[skill]) / 2
			if skill_map is Dictionary and skill_map.has(skill):
				s += int(skills.get(skill_map[skill], 0))
		return s
	if skills is Dictionary and skills.has(skill):
		return int(skills[skill])
	return 0

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

###############################################################
# 命令处理方法 - 由 COMMAND_D 映射动词到这些方法
# 按钮控件通过 actor.command("动词 目标") 触发这些逻辑
###############################################################

# 查找当前环境中 id 匹配的对象
func _find_obj_by_id(id: String):
	# 1. 先从自身携带物品查找
	var my_objs = query_temp("objects")
	if my_objs:
		var found = _match_id_in(my_objs, id)
		if found:
			return found
	# 2. 再从当前环境(房间)查找
	var env = environment()
	if env and env.has_method("query_temp"):
		var env_objs = env.query_temp("objects")
		if env_objs:
			var found2 = _match_id_in(env_objs, id)
			if found2:
				return found2
	return null

# 在对象集合中查找 id 匹配的对象（兼容单个对象或数组）
func _match_id_in(objs, id: String):
	if objs is Array:
		for o in objs:
			if o and o.has_method("query") and o.query("id") == id:
				return o
	elif objs and objs.has_method("query"):
		if objs.query("id") == id:
			return objs
	return null

# look - 查看目标
func do_look(arg: String = "") -> void:
	if arg == "":
		# 查看当前房间
		var env = environment()
		if env and env.has_method("query"):
			var short = env.query("short")
			var long = env.query("long")
			tell_object(self, "%s\n%s" % [short, long])
		return
	var ob = _find_obj_by_id(arg)
	if ob and ob.has_method("long"):
		tell_object(self, ob.long())
	else:
		notify_fail("这里没有这个东西。\n")

# eat - 吃食物
func do_eat(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要吃什么？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("你要吃什么？\n")
		return
	if ob.has_method("do_eat"):
		var msg = ob.do_eat(self)
		if msg and msg is String:
			tell_object(self, msg)
	else:
		notify_fail(ob.name() + "不能吃。\n")

# drink - 喝东西
func do_drink(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要喝什么？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("你要喝什么？\n")
		return
	if ob.has_method("do_drink"):
		var msg = ob.do_drink(self)
		if msg and msg is String:
			tell_object(self, msg)
	else:
		notify_fail(ob.name() + "不能喝。\n")

# get - 拾取物品
func do_get(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要拿什么？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("这里没有这个东西。\n")
		return
	ob.move(self)
	message_vision("$N拿起了$n。\n", self, ob)

# drop - 丢弃物品
func do_drop(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要丢什么？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("你身上没有这个东西。\n")
		return
	var env = environment()
	if env:
		ob.move(env)
		message_vision("$N丢下了$n。\n", self, ob)

# kill - 杀死目标
func do_kill(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要杀谁？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("这里没有这个人。\n")
		return
	if not (ob is Char):
		notify_fail(ob.name() + "不是活物。\n")
		return
	if ob == self:
		notify_fail("自杀？\n")
		return
	kill_ob(ob)
	set_heart_beat(1)

# fight - 与目标搏斗
func do_fight(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要和谁搏斗？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("这里没有这个人。\n")
		return
	if not (ob is Char):
		notify_fail(ob.name() + "不是活物。\n")
		return
	fight_ob(ob)
	set_heart_beat(1)

# ask - 询问NPC
func do_ask(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要问谁？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("这里没有这个人。\n")
		return
	# 打开对话面板由 UI 层处理，这里只做消息提示
	message_vision("$N向$n打听消息。\n", self, ob)

# give - 给予物品
func do_give(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要给什么？\n")
		return
	# arg 格式可能是 "物品id 给 目标id"，简化处理
	var parts = arg.split(" ")
	if parts.size() < 1:
		return
	var ob = _find_obj_by_id(parts[0])
	if ob == null:
		notify_fail("你身上没有这个东西。\n")
		return
	message_vision("$N拿出了$n。\n", self, ob)

# follow - 跟随
func do_follow(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要跟随谁？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("这里没有这个人。\n")
		return
	message_vision("$N开始跟随$n。\n", self, ob)

# wield - 装备武器
func do_wield(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要装备什么武器？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("你身上没有这个东西。\n")
		return
	if ob.has_method("wield"):
		ob.wield(self)
	else:
		message_vision("$N装备了$n。\n", self, ob)

# wear - 穿戴
func do_wear(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要穿戴什么？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("你身上没有这个东西。\n")
		return
	if ob.has_method("wear"):
		ob.wear(self)
	else:
		message_vision("$N穿上了$n。\n", self, ob)

# remove - 取下装备
func do_remove(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要取下什么？\n")
		return
	var ob = _find_obj_by_id(arg)
	if ob == null:
		notify_fail("你身上没有这个东西。\n")
		return
	if ob.has_method("unequip"):
		ob.unequip()
	message_vision("$N取下了$n。\n", self, ob)

# perform - 施展技能
func do_perform(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要施展什么？\n")
		return
	message_vision("$N开始施展「%s」！\n" % arg, self)

# exert - 运功
func do_exert(arg: String = "") -> void:
	if arg == "":
		notify_fail("你要运什么功？\n")
		return
	message_vision("$N开始运功「%s」。\n" % arg, self)

# say - 说话
func do_say(arg: String = "") -> void:
	if arg == "":
		return
	message_vision("$N说道：「%s」\n" % arg, self)

# inventory - 查看背包
func do_inventory(arg: String = "") -> void:
	var objs = query_temp("objects")
	if not objs or (objs is Array and objs.size() == 0):
		tell_object(self, "你身上什么也没有。\n")
		return
	var msg := "你身上带着：\n"
	if objs is Array:
		for o in objs:
			if o and o.has_method("name"):
				msg += "  " + o.name() + "\n"
	tell_object(self, msg)

# score - 查看属性
func do_score(arg: String = "") -> void:
	var msg := "【人物属性】\n"
	msg += "臂力: %s\n" % str(query("str"))
	msg += "悟性: %s\n" % str(query("int"))
	msg += "体质: %s\n" % str(query("con"))
	msg += "身法: %s\n" % str(query("dex"))
	msg += "容貌: %s\n" % str(query("per"))
	msg += "福缘: %s\n" % str(query("cps"))
	tell_object(self, msg)

# skills - 查看武功
func do_skills(arg: String = "") -> void:
	if skills and skills is Dictionary:
		var msg := "【已学武功】\n"
		for k in skills.keys():
			msg += "%s: %s\n" % [k, str(skills[k])]
		tell_object(self, msg)
	else:
		tell_object(self, "你还没有学会任何武功。\n")

# 通用命令分发（供按钮直接调用）
func run_command(verb: String, target = null) -> void:
	if target and target.has_method("query"):
		var tid = target.query("id")
		if tid and tid != "" and tid != 0:
			command("%s %s" % [verb, tid])
			return
	command(verb)
# 	return a.size()	
