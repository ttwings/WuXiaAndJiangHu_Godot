# COMBAT_D.gd - 战斗守护进程
# 负责战斗中的攻击、伤害计算、胜负判定
# 由 Char.heart_beat() -> attack() -> COMBAT_D.fight() 调用

extends Node

# ============== 战斗常量 ==============
# 技能用途
const SKILL_USAGE_ATTACK = 1
const SKILL_USAGE_DEFENSE = 2

# 攻击类型
const TYPE_REGULAR = 0
const TYPE_QUICK = 1
const TYPE_RIPOSTE = 2

# 战斗结果
const RESULT_DODGE = -1
const RESULT_PARRY = -2

# 伤害类型
const DAMAGE_SLASH = "割伤"
const DAMAGE_STAB = "刺伤"
const DAMAGE_BRUISE = "瘀伤"
const DAMAGE_INTERNAL = "内伤"
const DAMAGE_SCRATCH = "抓伤"
const DAMAGE_DEFAULT = "伤害"

# 默认攻击动作（无武器时）
const DEFAULT_UNARMED_ACTION = {
	"action": "$N一拳向$n打了过去",
	"damage_type": DAMAGE_BRUISE,
	"weapon": "拳头",
	"dodge": 0,
	"parry": 0,
	"damage": 0,
	"force": 0,
}

# ============== 消息模板 ==============
var guard_msg = [
	"$N注视着$n的行动，企图寻找机会出手。\n",
	"$N正盯着$n的一举一动，随时准备发动攻势。\n",
	"$N缓缓地移动脚步，想要找出$n的破绽。\n",
	"$N目不转睛地盯着$n的动作，寻找进攻的最佳时机。\n",
	"$N慢慢地移动着脚步，伺机出手。\n",
]

var winner_msg = [
	"\n$N哈哈大笑，说道：承让了！\n\n",
	"\n$N双手一拱，笑着说道：承让！\n\n",
	"\n$N胜了这招，向后跃开三尺，笑道：承让！\n\n",
	"\n$N双手一拱，笑着说道：知道我的利害了吧！\n\n",
	"\n$n向后退了几步，说道：这场比试算我输了，下回看我怎么收拾你！\n\n",
	"\n$n向后一纵，恨恨地说道：君子报仇，十年不晚！\n\n",
	"\n$n脸色一寒，说道：算了算了，就当是我让你吧！\n\n",
	"\n$n纵声而笑，叫道：你运气好！你运气好！一面身子向后跳开。\n\n",
	"\n$n脸色微变，说道：佩服，佩服！\n\n",
	"\n$n向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n",
	"\n$n向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n",
]

# ============== 伤害描述 ==============
func damage_msg(damage: int, type: String) -> String:
	if damage == 0:
		return "结果没有造成任何伤害。\n"

	match type:
		DAMAGE_SLASH, "擦伤", "劈伤":
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
		DAMAGE_STAB:
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
		DAMAGE_BRUISE, "挫伤":
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
		DAMAGE_INTERNAL:
			if damage < 10:
				return "结果只是把$n打得退了半步，毫发无损。\n"
			elif damage < 20:
				return "结果$n痛哼一声，在$p的$l造成一处瘀伤。\n"
			elif damage < 40:
				return "结果一击命中，把$n打得痛得弯下腰去！\n"
			elif damage < 80:
				return "结果$n闷哼了一声，脸上一阵青一阵白，显然受了点内伤！\n"
			elif damage < 120:
				return "结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n"
			elif damage < 160:
				return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n"
			elif damage < 240:
				return "结果「轰」地一声，$n全身气血倒流，口中鲜血狂喷而出！\n"
			else:
				return "结果只听见几声喀喀轻响，$n一声惨叫，像滩软泥般塌了下去！！\n"
		DAMAGE_SCRATCH:
			if damage < 10:
				return "结果只是轻轻地抓破$p的皮肉。\n"
			elif damage < 20:
				return "结果在$p$l抓出一道细长血痕。\n"
			elif damage < 40:
				return "结果抓出一道长长的血口！\n"
			elif damage < 80:
				return "结果抓出一道血淋淋的伤口！\n"
			elif damage < 160:
				return "结果抓出一道又长又深的伤口，$N满手沾满了鲜血！\n"
			else:
				return "结果只听见$n一声惨嚎，$p$l被抓出一道深及见骨的可怕伤口！！\n"
		_:
			var t = type if type else DAMAGE_DEFAULT
			var str = ""
			if damage < 10:
				str = "结果只是勉强造成一处轻微"
			elif damage < 20:
				str = "结果造成轻微的"
			elif damage < 30:
				str = "结果造成一处"
			elif damage < 50:
				str = "结果造成一处严重"
			elif damage < 80:
				str = "结果造成颇为严重的"
			elif damage < 120:
				str = "结果造成相当严重的"
			elif damage < 170:
				str = "结果造成十分严重的"
			elif damage < 230:
				str = "结果造成极其严重的"
			else:
				str = "结果造成非常可怕的严重"
			return str + t + "！\n"
	return "结果造成了一些伤害。\n"

# ============== 状态描述 ==============
func eff_status_msg(ratio: int) -> String:
	if ratio == 100:
		return "看起来气血充盈，并没有受伤。"
	elif ratio > 95:
		return "似乎受了点轻伤，不过光从外表看不大出来。"
	elif ratio > 90:
		return "看起来可能受了点轻伤。"
	elif ratio > 80:
		return "受了几处伤，不过似乎并不碍事。"
	elif ratio > 60:
		return "受伤不轻，看起来状况并不太好。"
	elif ratio > 40:
		return "气息粗重，动作开始散乱，看来所受的伤着实不轻。"
	elif ratio > 30:
		return "已经伤痕累累，正在勉力支撑着不倒下去。"
	elif ratio > 20:
		return "受了相当重的伤，只怕会有生命危险。"
	elif ratio > 10:
		return "伤重之下已经难以支撑，眼看就要倒在地上。"
	elif ratio > 5:
		return "受伤过重，已经奄奄一息，命在旦夕了。"
	else:
		return "受伤过重，已经有如风中残烛，随时都可能断气。"

func report_status(ob, wounded: int) -> void:
	var max_qi = ob.query("max_qi")
	if max_qi <= 0:
		return
	var ratio = ob.query("eff_qi") * 100 / max_qi
	var msg = "( " + str(ob.query("name")) + eff_status_msg(ratio) + " )\n"
	if ob.has_method("message_sent"):
		ob.message_sent.emit(msg)

# ============== 技能威力计算 ==============
func skill_power(ob, skill: String, usage: int) -> int:
	if ob == null or not is_instance_valid(ob):
		return 0
	if not ob.has_method("query") or not ob.has_method("query_skill"):
		return 0

	var level = ob.query_skill(skill)
	if level == 0:
		# 无对应技能，用经验/2 作为基础威力
		return int(ob.query("combat_exp") / 2)

	# 攻防加成
	if usage == SKILL_USAGE_ATTACK:
		level += ob.query_temp("apply/attack")
	elif usage == SKILL_USAGE_DEFENSE:
		level += ob.query_temp("apply/defense")

	# 防止负攻防
	if level > 800:
		level = 800
	if level < 1:
		level = 1

	var str_val = ob.query_str() if ob.has_method("query_str") else 10
	var dex_val = ob.query_dex() if ob.has_method("query_dex") else 10
	if str_val < 10:
		str_val = 10
	if str_val > 200:
		str_val = 200
	if dex_val < 10:
		dex_val = 10
	if dex_val > 200:
		dex_val = 200

	var exp = ob.query("combat_exp")
	var power = (level / 6) * level * level

	if usage == SKILL_USAGE_ATTACK:
		return int((power + exp) / 80 * (str_val + ob.query("str")))
	else:
		return int((power + exp) / 80 * (dex_val + ob.query("dex")))

# ============== 选择攻击技能 ==============
func _get_attack_skill(me) -> String:
	var weapon = me.query_temp("weapon")
	if weapon and weapon.has_method("query"):
		var st = weapon.query("skill_type")
		if st:
			return st

	var prepare = me.query_skill_prepare()
	if not prepare or prepare.size() == 0:
		return "unarmed"
	elif prepare.size() == 1:
		return prepare.keys()[0]
	else:
		var flag = me.query_temp("action_flag")
		var keys = prepare.keys()
		if flag < keys.size():
			return keys[flag]
		return keys[0]

# ============== 获取攻击动作 ==============
func _get_action(me, attack_skill: String) -> Dictionary:
	var action = me.query("actions")
	if action is Dictionary and action.size() > 0:
		return action
	return DEFAULT_UNARMED_ACTION.duplicate()

# ============== 执行一次攻击 ==============
func do_attack(me, victim, weapon, attack_type: int = TYPE_REGULAR, msg: String = "") -> int:
	if me == null or victim == null:
		return 0
	if not is_instance_valid(me) or not is_instance_valid(victim):
		return 0

	var my = me.query_entire_dbase()
	var your = victim.query_entire_dbase()

	# (0) 选择攻击技能
	var attack_skill = _get_attack_skill(me)

	# (1) 获取攻击动作
	var action = _get_action(me, attack_skill)
	var result = action.get("action", "$N向$n发起了攻击")
	if msg != "":
		result = msg

	# (2) 准备攻防参数
	var limbs = victim.query("limbs")
	if not limbs or not (limbs is Array) or limbs.size() == 0:
		limbs = ["胸口", "头部", "左臂", "右臂", "左腿", "右腿"]
	var limb = limbs[randi() % limbs.size()]

	# 替换占位符
	result = result.replace("$l", limb)
	var victim_weapon = victim.query_temp("weapon")
	if victim_weapon and victim_weapon.has_method("name"):
		result = result.replace("$W", str(victim_weapon.name()))
	else:
		result = result.replace("$W", "拳脚")
	if weapon and weapon.has_method("name"):
		result = result.replace("$w", str(weapon.name()))
	elif action.get("weapon", ""):
		result = result.replace("$w", str(action["weapon"]))
	elif attack_skill == "finger":
		result = result.replace("$w", "手指")
	else:
		result = result.replace("$w", "拳脚")

	# 发送出招消息
	me.message_vision(result, me, victim)
	result = ""

	# (3) 计算攻防
	var ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK)
	if ap < 1:
		ap = 1
	if ap > 200000000:
		ap = 200000000

	var dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE)
	if dp < 1:
		dp = 1
	if dp > 200000000:
		dp = 200000000
	if victim.has_method("is_busy") and victim.is_busy():
		dp = int(dp / 3)

	var damage = 0
	var wounded = 0

	# (4) 判断是否命中
	var total = ap + dp
	if total <= 0:
		total = 1
	var roll = randi() % total

	if roll < dp:
		# 对手躲开了
		result = "$n侧身闪开了$N的攻势。\n"
		damage = RESULT_DODGE
	else:
		# 命中，判断是否招架
		var pp = 0
		if victim_weapon:
			pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE)
			if not weapon:
				pp *= 2
		else:
			if weapon:
				pp = 0
			else:
				pp = skill_power(victim, "unarmed", SKILL_USAGE_DEFENSE)

		if victim.has_method("is_busy") and victim.is_busy():
			pp = int(pp / 3)
		if pp < 1:
			pp = 1
		if pp > 200000000:
			pp = 200000000

		var parry_total = ap + pp
		if parry_total <= 0:
			parry_total = 1
		var parry_roll = randi() % parry_total

		if parry_roll < pp:
			# 招架住了
			result = "$n架住了$N的攻势。\n"
			damage = RESULT_PARRY
		else:
			# 真正打中！计算伤害
			if weapon and weapon.has_method("query"):
				damage = me.query_temp("apply/damage")
			else:
				damage = me.query_temp("apply/unarmed_damage")

			if damage == 0:
				# 基础伤害 = 膂力 / 2
				damage = int(me.query_str() / 2) if me.has_method("query_str") else 5

			# 伤害波动
			if damage > 300:
				damage = 300 + randi() % (damage - 300)
			damage = int((damage + randi() % max(damage, 1)) / 2)

			# 动作伤害加成
			var action_dmg = action.get("damage", 0)
			if action_dmg > 0:
				damage += int(action_dmg * damage / 200)

			# 护甲减伤
			var defense_factor = victim.query_temp("apply/armor")
			if defense_factor > 0:
				if defense_factor > 300:
					defense_factor = 300 + randi() % (defense_factor - 300)
				defense_factor = int((defense_factor + randi() % max(defense_factor, 1)) / 2)
				damage -= defense_factor

			if damage < 0:
				damage = 0

			# 膂力加伤
			var damage_bonus = me.query_str() if me.has_method("query_str") else 10
			if damage_bonus > 0:
				damage_bonus = int((damage_bonus + randi() % max(damage_bonus, 1)) / 2)
			else:
				damage_bonus = 0
			damage += damage_bonus

			if damage < 0:
				damage = 0

			# 经验修正
			var my_exp = me.query("combat_exp")
			var your_exp = victim.query("combat_exp")
			var factor = your_exp
			while factor > 0 and randi() % factor > my_exp:
				damage = int(damage - damage / 3)
				factor = int(factor / 2)

			# 施加伤害
			var final_damage = victim.receive_damage("qi", damage, me)
			damage = final_damage

			# 有几率造成创伤
			var armor = victim.query_temp("apply/armor")
			if randi() % max(damage, 1) > armor:
				victim.receive_wound("qi", max(damage - armor, 0), me)
				wounded = 1

			# 伤害描述
			var damage_type = action.get("damage_type", DAMAGE_BRUISE)
			result += damage_msg(damage, damage_type)

	# 替换消息中的占位符并发送
	result = result.replace("$l", limb)
	if victim_weapon and victim_weapon.has_method("name"):
		result = result.replace("$W", str(victim_weapon.name()))
	else:
		result = result.replace("$W", "拳脚")
	if weapon and weapon.has_method("name"):
		result = result.replace("$w", str(weapon.name()))
	else:
		result = result.replace("$w", "拳脚")
	result = result.replace("$p", str(victim.query("name")))
	result = result.replace("$P", str(victim.query("name")))

	me.message_vision(result, me, victim)

	# 报告状态
	if damage > 0:
		report_status(victim, wounded)

		# 非杀戮模式下，如果对方气血过半，自动结束战斗
		var victim_max_qi = victim.query("max_qi")
		var victim_qi = victim.query("qi")
		if victim_max_qi > 0 and victim_qi * 2 <= victim_max_qi:
			if not me.is_killing(victim.query("id")) and not victim.is_killing(me.query("id")):
				me.remove_enemy(victim)
				victim.remove_enemy(me)
				var win_msg = winner_msg[randi() % winner_msg.size()]
				me.message_vision(win_msg, me, victim)
				return 1

	return damage

# ============== 战斗主循环（由 heart_beat 调用） ==============
func fight(me, victim) -> void:
	if me == null or victim == null:
		return
	if not is_instance_valid(me) or not is_instance_valid(victim):
		return
	if not me.has_method("query") or not victim.has_method("query"):
		return

	# 检查是否还活着
	if not me.has_method("living") or not me.living():
		return
	if me.query_temp("noliving"):
		return

	var weapon = me.query_temp("weapon")

	# 如果对手忙/昏迷，直接攻击
	var victim_busy = victim.has_method("is_busy") and victim.is_busy()
	var victim_living = victim.has_method("living") and victim.living()
	var victim_noliving = victim.query_temp("noliving")

	if victim_busy or not victim_living or victim_noliving:
		me.set_temp("guarding", 0)
		if not victim.is_fighting(me):
			victim.fight_ob(me)
		do_attack(me, victim, weapon, TYPE_QUICK)
		return

	# 判断是否主动攻击
	var victim_cps = victim.query_cps() if victim.has_method("query_cps") else 10
	var me_cor = me.query_cor() if me.has_method("query_cor") else 10

	if randi() % max(victim_cps * 3, 1) > me_cor:
		# 主动攻击
		me.set_temp("guarding", 0)
		if not victim.is_fighting(me):
			victim.fight_ob(me)
		do_attack(me, victim, weapon, TYPE_REGULAR)
	else:
		# 防御姿态
		if not me.query_temp("guarding"):
			me.set_temp("guarding", 1)
			var gmsg = guard_msg[randi() % guard_msg.size()]
			me.message_vision(gmsg, me, victim)

# ============== 自动战斗（NPC） ==============
func auto_fight(me, obj, type: String) -> void:
	if me == null or obj == null:
		return
	# 不让 NPC 自动打 NPC（简化）
	if not me.has_method("userp") and not obj.has_method("userp"):
		return

	match type:
		"aggressive":
			me.kill_ob(obj)
		"hatred":
			me.kill_ob(obj)
		"vendetta":
			me.kill_ob(obj)
		_:
			me.fight_ob(obj)

# ============== 战斗事件播报 ==============
func announce(ob, event: String) -> void:
	if ob == null:
		return
	match event:
		"dead":
			var msg = ob.query("dead_message")
			if not msg:
				msg = str(ob.query("name")) + "死了！\n"
			ob.message_vision(msg, ob)
		"unconcious":
			var msg = ob.query("unconcious_message")
			if not msg:
				msg = str(ob.query("name")) + "晕倒了！\n"
			ob.message_vision(msg, ob)
		"revive":
			var msg = ob.query("revive_message")
			if not msg:
				msg = str(ob.query("name")) + "醒了过来。\n"
			ob.message_vision(msg, ob)

# ============== 胜负奖励 ==============
func winner_reward(killer, victim) -> void:
	if killer and killer.has_method("defeated_enemy"):
		killer.defeated_enemy(victim)

func killer_reward(killer, victim) -> void:
	if killer and killer.has_method("killed_enemy"):
		killer.killed_enemy(victim)
