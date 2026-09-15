# COMBAT_D.gd - 战斗守护进程
# 由 C 源码 combatd.c 转换而来，核心战斗逻辑

extends Node

# ============================================================
# 战斗常量
# ============================================================
const SKILL_USAGE_ATTACK = 1
const SKILL_USAGE_DEFENSE = 2

const RESULT_DODGE = -1
const RESULT_PARRY = -2

const TYPE_REGULAR = 0
const TYPE_QUICK = 1
const TYPE_RIPOSTE = 2

# 伤害类型
const DAMAGE_TYPE_SLASH = "割伤"
const DAMAGE_TYPE_PIERCE = "刺伤"
const DAMAGE_TYPE_BLUNT = "瘀伤"
const DAMAGE_TYPE_INTERNAL = "内伤"
const DAMAGE_TYPE_SCRATCH = "抓伤"

# ANSI 颜色（用于战斗消息）
const NOR = ""
const HIR = ""
const HIY = ""
const HIG = ""
const HIB = ""
const HIM = ""
const HIC = ""
const HIW = ""
const CYN = ""
const YEL = ""
const GRN = ""
const WHT = ""
const BLU = ""
const MAG = ""
const RED = ""

# 防御（观望）消息
var guard_msg = [
	CYN + "$N注视着$n的行动，企图寻找机会出手。\n" + NOR,
	CYN + "$N正盯着$n的一举一动，随时准备发动攻势。\n" + NOR,
	CYN + "$N缓缓地移动脚步，想要找出$n的破绽。\n" + NOR,
	CYN + "$N目不转睛地盯着$n的动作，寻找进攻的最佳时机。\n" + NOR,
	CYN + "$N慢慢地移动着脚步，伺机出手。\n" + NOR,
]

# 胜利消息
var winner_msg = [
	CYN + "\n$N哈哈大笑，说道：承让了！\n\n" + NOR,
	CYN + "\n$N双手一拱，笑着说道：承让！\n\n" + NOR,
	CYN + "\n$N胜了这招，向后跃开三尺，笑道：承让！\n\n" + NOR,
	CYN + "\n$N双手一拱，笑着说道：知道我的利害了吧！\n\n" + NOR,
	CYN + "\n$n向后退了几步，说道：这场比试算我输了，下回看我怎么收拾你！\n\n" + NOR,
	CYN + "\n$n向后一纵，恨恨地说道：君子报仇，十年不晚！\n\n" + NOR,
	CYN + "\n$n脸色一寒，说道：算了算了，就当是我让你吧！\n\n" + NOR,
	CYN + "\n$n纵声而笑，叫道：你运气好！你运气好！一面身子向后跳开。\n\n" + NOR,
	CYN + "\n$n脸色微变，说道：佩服，佩服！\n\n" + NOR,
	CYN + "\n$n向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" + NOR,
	CYN + "\n$n向后一纵，躬身作揖说道：阁下武艺不凡，果然高明！\n\n" + NOR,
]


# ============================================================
# 伤害描述文案
# ============================================================
func damage_msg(damage: int, type: String) -> String:
	if damage == 0:
		return "结果没有造成任何伤害。\n"

	match type:
		"割伤", "擦伤", "劈伤":
			if damage < 10:
				return "结果只是轻轻地划破$p的皮肉。\n"
			elif damage < 20:
				return "结果在$p$l划出一道细长血痕。\n"
			elif damage < 40:
				return "结果「嗤」一声划出一道伤口！\n"
			elif damage < 80:
				return "结果「嗤」地一声划出一道血淋淋的伤口！\n"
			elif damage < 160:
				return "结果「嗤」地一声划出一道又长又深的伤口，溅得$N满脸鲜血！\n"
			else:
				return "结果只听见$n一声惨嚎，$w已在$p$l划出一道深及见骨的可怕伤口！！\n"

		"刺伤":
			if damage < 10:
				return "结果只是轻轻地刺破$p的皮肉。\n"
			elif damage < 20:
				return "结果在$p$l刺出一个创口。\n"
			elif damage < 40:
				return "结果「噗」地一声刺入了$n$l寸许！\n"
			elif damage < 80:
				return "结果「噗」地一声刺进$n的$l，使$p不由自主地退了几步！\n"
			elif damage < 160:
				return "结果「噗嗤」地一声，$w已在$p$l刺出一个血肉模糊的血窟窿！\n"
			else:
				return "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！！\n"

		"瘀伤", "挫伤":
			if damage < 10:
				return "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n"
			elif damage < 20:
				return "结果在$p的$l造成一处瘀青。\n"
			elif damage < 40:
				return "结果一击命中，$n的$l登时肿了一块老高！\n"
			elif damage < 80:
				return "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n"
			elif damage < 120:
				return "结果「砰」地一声，$n退了两步！\n"
			elif damage < 160:
				return "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n"
			elif damage < 240:
				return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n"
			else:
				return "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！！\n"

		"内伤":
			if damage < 10:
				return "结果只是把$n打得退了半步，毫发无损。\n"
			elif damage < 20:
				return "结果$n被震得胸口一阵闷痛。\n"
			elif damage < 40:
				return "结果$n只觉得呼吸一滞，差点闭过气去！\n"
			elif damage < 80:
				return "结果$n闷哼一声，脸色发青，显然受了点内伤！\n"
			elif damage < 160:
				return "结果$n「哇」地一声喷出一口鲜血！\n"
			else:
				return "结果$n眼前一黑，一口鲜血狂喷而出，看来伤得不轻！！\n"

		"抓伤":
			if damage < 10:
				return "结果只是在$p的$l留下一道抓痕。\n"
			elif damage < 20:
				return "结果在$p的$l抓出几道血痕。\n"
			elif damage < 40:
				return "结果「嘶啦」一声，在$p$l抓破一道口子！\n"
			elif damage < 80:
				return "结果「嘶啦」一声，$p的$l已被抓得皮开肉绽！\n"
			elif damage < 160:
				return "结果「嘶啦」一声，$p的$l已被抓得血肉模糊！\n"
			else:
				return "结果只听见$n一声惨嚎，$p的$l已被抓得筋断骨折！！\n"

		_:
			return "结果造成了 " + str(damage) + " 点伤害。\n"


# ============================================================
# 攻防威力计算
# ============================================================
func skill_power(ob, skill: String, usage: int) -> int:
	if not ob or not ob.has_method("living") or not ob.living():
		return 0

	var level = ob.query_skill(skill)
	if usage == SKILL_USAGE_ATTACK:
		level += int(ob.query_temp("apply/attack"))
	elif usage == SKILL_USAGE_DEFENSE:
		level += int(ob.query_temp("apply/defense"))

	if level <= 0:
		return int(ob.query("combat_exp")) / 2

	# 限制攻防范围
	level = clamp(level, 1, 800)

	var str_ = ob.query_str()
	str_ = clamp(str_, 10, 200)
	var dex = ob.query_dex()
	dex = clamp(dex, 10, 200)
	var exp = int(ob.query("combat_exp"))

	var power = (level / 6) * level * level

	if usage == SKILL_USAGE_ATTACK:
		return (power + exp) / 80 * (str_ + int(ob.query("str")))
	else:
		return (power + exp) / 80 * (dex + int(ob.query("dex")))


# ============================================================
# 执行一次攻击
# ============================================================
func do_attack(me, victim, weapon, attack_type: int, msg = "") -> void:
	if not me or not victim:
		return

	var my = me.query_entire_dbase()
	var your = victim.query_entire_dbase()
	if not my is Dictionary or not your is Dictionary:
		return

	# (0) 选择攻击技能
	var prepare = me.query_skill_prepare()
	var attack_skill = "unarmed"
	if weapon and weapon.has_method("query"):
		attack_skill = weapon.query("skill_type")
		if not attack_skill:
			attack_skill = "unarmed"
	elif prepare is Dictionary and prepare.size() > 0:
		attack_skill = prepare.keys()[0]

	# (1) 攻击动作描述
	var weapon_name = "拳脚"
	if weapon and weapon.has_method("name"):
		weapon_name = weapon.name()
	elif attack_skill == "finger":
		weapon_name = "手指"

	var action_desc = msg
	if action_desc == "":
		if attack_type == TYPE_QUICK:
			action_desc = "\n$N迅速地向$n发起了攻击！\n"
		else:
			action_desc = "\n$N大喝一声，向$n扑了过去！\n"

	# 替换消息中的变量
	action_desc = action_desc.replace("$N", me.name())
	action_desc = action_desc.replace("$n", victim.name())
	action_desc = action_desc.replace("$p", victim.name())
	action_desc = action_desc.replace("$w", weapon_name)

	me.tell_object(me, action_desc)
	if victim != me:
		victim.tell_object(victim, action_desc)

	# (2) 计算 AP / DP
	var ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK)
	ap = clamp(ap, 1, 200000000)

	var dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE)
	dp = clamp(dp, 1, 200000000)
	if victim.has_method("is_busy") and victim.is_busy():
		dp /= 3

	# (3) 命中判定
	if randi() % (ap + dp) < dp:
		# 躲闪成功
		var dodge_msg = "$n身形一晃，闪开了$N的攻势。\n"
		dodge_msg = dodge_msg.replace("$N", me.name()).replace("$n", victim.name())
		me.tell_object(me, dodge_msg)
		if victim != me:
			victim.tell_object(victim, dodge_msg)
		# 躲闪成功有概率获得经验
		if dp < ap:
			victim.add("combat_exp", 1)
		return

	# (4) 招架判定
	var pp = 0
	if victim.query_temp("weapon"):
		pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE)
		if not weapon:
			pp *= 2
	else:
		if not weapon:
			pp = skill_power(victim, "unarmed", SKILL_USAGE_DEFENSE)
	pp = clamp(pp, 1, 200000000)
	if victim.has_method("is_busy") and victim.is_busy():
		pp /= 3

	if randi() % (ap + pp) < pp:
		# 招架成功
		var parry_msg = "$n连忙招架，挡住了$N的攻势。\n"
		parry_msg = parry_msg.replace("$N", me.name()).replace("$n", victim.name())
		me.tell_object(me, parry_msg)
		if victim != me:
			victim.tell_object(victim, parry_msg)
		return

	# (5) 命中 - 计算伤害
	var damage = 0
	if weapon and weapon.has_method("query"):
		damage = int(weapon.query("damage"))
	if damage <= 0:
		damage = int(me.query_temp("apply/damage"))
	if damage <= 0:
		damage = int(me.query_skill(attack_skill)) / 2 + 5

	# 膂力加成
	var damage_bonus = me.query_str()
	damage += damage_bonus

	# 内力加成（加力）
	var jiali = int(my.get("jiali", 0))
	var neili = int(my.get("neili", 0))
	if jiali > 0 and neili > jiali:
		damage += jiali / 2
		me.set("neili", neili - jiali)

	# 护甲减免
	var armor = int(victim.query_temp("apply/armor"))
	damage -= armor
	if damage < 0:
		damage = 0

	# 伤害波动
	damage = (damage + randi() % (damage + 1)) / 2
	if damage < 1:
		damage = 1

	# (6) 造成伤害
	var dmg_type = DAMAGE_TYPE_BLUNT
	if weapon and weapon.has_method("query"):
		var wt = weapon.query("damage_type")
		if wt:
			dmg_type = wt

	var dmg_text = damage_msg(damage, dmg_type)
	dmg_text = dmg_text.replace("$N", me.name())
	dmg_text = dmg_text.replace("$n", victim.name())
	dmg_text = dmg_text.replace("$p", victim.name())
	dmg_text = dmg_text.replace("$w", weapon_name)
	dmg_text = dmg_text.replace("$l", "身上")

	me.tell_object(me, dmg_text)
	if victim != me:
		victim.tell_object(victim, dmg_text)

	# 气血伤害为主，精气伤害为辅
	var qi_damage = damage
	var jing_damage = damage / 5

	victim.receive_damage("qi", qi_damage, me)
	if jing_damage > 0:
		victim.receive_damage("jing", jing_damage, me)

	# 攻击者获得经验
	me.add("combat_exp", 1)

	# (7) 检查死亡/昏迷
	var victim_qi = int(victim.query("qi"))
	var victim_jing = int(victim.query("jing"))

	if victim_qi <= 0 or victim_jing <= 0:
		victim.unconcious()
	elif victim_qi < -int(victim.query("max_qi")) / 2:
		victim.die()


# ============================================================
# 战斗循环入口
# ============================================================
func fight(me, victim) -> void:
	if not me or not victim:
		return
	if not me.has_method("living") or not me.living():
		return

	if me.query("env/no_fight"):
		return

	# 如果目标忙或昏迷，快速攻击
	var victim_busy = victim.has_method("is_busy") and victim.is_busy()
	var victim_living = victim.has_method("living") and victim.living()

	if victim_busy or not victim_living:
		me.set_temp("guarding", 0)
		if not victim.is_fighting(me):
			victim.fight_ob(me)
		do_attack(me, victim, me.query_temp("weapon"), TYPE_QUICK)
	else:
		# 正常攻击
		me.set_temp("guarding", 0)
		if not victim.is_fighting(me):
			victim.fight_ob(me)
		do_attack(me, victim, me.query_temp("weapon"), TYPE_REGULAR)


# ============================================================
# 战斗状态公告
# ============================================================
func announce(ob, event: String) -> void:
	if not ob:
		return
	var env = ob.environment()
	if not env:
		return

	var msg = ""
	match event:
		"unconcious":
			msg = ob.name() + "晕倒了！\n"
		"revive":
			msg = ob.name() + "苏醒了过来。\n"
		"dead":
			msg = HIR + ob.name() + "死了！\n" + NOR

	if msg != "":
		# 向房间内所有人广播
		var objs = env.all_inventory()
		for o in objs:
			if o and o.has_method("tell_object"):
				o.tell_object(o, msg)


# ============================================================
# 胜利奖励（昏迷）
# ============================================================
func winner_reward(killer, victim) -> void:
	if not killer or not victim:
		return
	# 经验奖励
	var exp = int(victim.query("combat_exp")) / 100
	if exp < 1:
		exp = 1
	killer.add("combat_exp", exp)
	killer.tell_object(killer, HIC + "你击败了" + victim.name() + "，获得 " + str(exp) + " 点实战经验。\n" + NOR)


# ============================================================
# 击杀奖励
# ============================================================
func killer_reward(killer, victim) -> void:
	if not killer or not victim:
		return
	# 经验奖励
	var exp = int(victim.query("combat_exp")) / 50
	if exp < 1:
		exp = 1
	killer.add("combat_exp", exp)
	killer.tell_object(killer, HIR + "你杀死了" + victim.name() + "，获得 " + str(exp) + " 点实战经验！\n" + NOR)


# ============================================================
# 自动战斗（NPC AI）
# ============================================================
func auto_fight(me, obj, type: String) -> void:
	if not me or not obj:
		return
	# 不让 NPC 自动打 NPC（避免无限循环）
	if not me.userp(me) and not obj.userp(obj):
		return
	if me.query_temp("looking_for_trouble"):
		return
	me.set_temp("looking_for_trouble", 1)
	# 延迟触发
	me.call_deferred("_start_auto_fight", obj, type)


func _start_auto_fight(me, obj, type: String) -> void:
	if not me or not obj:
		return
	me.set_temp("looking_for_trouble", 0)
	if me.is_fighting(obj):
		return
	if not me.living() or not obj.living():
		return
	if me.environment() != obj.environment():
		return
	# 发起攻击
	me.kill_ob(obj)


# ============================================================
# 状态消息（调试用）
# ============================================================
func status_msg(me, victim) -> String:
	if not me or not victim:
		return ""
	return me.name() + " vs " + victim.name()
