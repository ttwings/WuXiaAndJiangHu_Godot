# commandd.gd
# 命令注册中心 - 将 MUD 命令动词映射到角色对象上的处理方法
# 原版 MUD 通过文件系统查找 /cmds/ 下的命令文件，这里改用注册表方式，
# 便于按钮控件直接调用 command("动词 目标") 来触发对应逻辑。

extends Node

# 动词 -> 处理方法名 的映射表
# key: 命令动词（英文/拼音），value: 角色对象上的处理方法名
var command_map := {
	# 移动
	"go": "do_go",
	"north": "do_go_north",
	"south": "do_go_south",
	"east": "do_go_east",
	"west": "do_go_west",
	"n": "do_go_north",
	"s": "do_go_south",
	"e": "do_go_east",
	"w": "do_go_west",
	"up": "do_go_up",
	"down": "do_go_down",
	"in": "do_go_in",
	"out": "do_go_out",
	"enter": "do_go_enter",
	"bei": "do_go_north",
	"nan": "do_go_south",
	"dong": "do_go_east",
	"xi": "do_go_west",
	"shang": "do_go_up",
	"xia": "do_go_down",
	"jin": "do_go_in",
	"chu": "do_go_out",

	# 观察
	"look": "do_look",
	"l": "do_look",
	"kan": "do_look",
	"cha": "do_look",

	# 物品操作
	"get": "do_get",
	"na": "do_get",
	"drop": "do_drop",
	"diu": "do_drop",
	"fang": "do_drop",
	"eat": "do_eat",
	"chi": "do_eat",
	"drink": "do_drink",
	"he": "do_drink",

	# 装备
	"wield": "do_wield",
	"wear": "do_wear",
	"dai": "do_wear",
	"remove": "do_remove",
	"qu": "do_remove",
	"unequip": "do_unequip",

	# 战斗
	"kill": "do_kill",
	"sha": "do_kill",
	"fight": "do_fight",
	"dou": "do_fight",
	"hit": "do_hit",
	"da": "do_hit",

	# 技能
	"perform": "do_perform",
	"exert": "do_exert",
	"yun": "do_exert",

	# 学习修炼
	"practice": "do_practice",
	"lian": "do_practice",
	"study": "do_study",
	"du": "do_study",
	"learn": "do_learn",
	"xue": "do_learn",

	# 社交
	"say": "do_say",
	"shuo": "do_say",
	"ask": "do_ask",
	"wen": "do_ask",
	"tell": "do_tell",
	"gaosu": "do_tell",
	"give": "do_give",
	"gei": "do_give",
	"follow": "do_follow",
	"gen": "do_follow",

	# 交易
	"buy": "do_buy",
	"mai": "do_buy",
	"sell": "do_sell",

	# 状态
	"inventory": "do_inventory",
	"i": "do_inventory",
	"score": "do_score",
	"hp": "do_hp",
	"skills": "do_skills",
	"equip": "do_equip",
}

# 命令的中文显示名（用于按钮文本）
var command_cn_name := {
	"go": "前往",
	"look": "查看",
	"get": "拾取",
	"drop": "丢弃",
	"eat": "吃",
	"drink": "喝",
	"wield": "装备武器",
	"wear": "穿戴",
	"remove": "取下",
	"kill": "杀死",
	"fight": "搏斗",
	"hit": "攻击",
	"perform": "施展",
	"exert": "运功",
	"practice": "练习",
	"study": "研读",
	"learn": "学习",
	"say": "说",
	"ask": "询问",
	"tell": "告诉",
	"give": "给予",
	"follow": "跟随",
	"buy": "购买",
	"sell": "出售",
	"inventory": "背包",
	"score": "属性",
	"skills": "武功",
	"equip": "装备",
}

# 注册一个新命令
func register_command(verb: String, handler: String, cn_name: String = "") -> void:
	command_map[verb] = handler
	if cn_name != "":
		command_cn_name[verb] = cn_name

# 查找命令对应的处理方法名
func find_command(verb: String) -> String:
	if command_map.has(verb):
		return command_map[verb]
	return ""

# 获取命令的中文显示名
func get_cn_name(verb: String) -> String:
	if command_cn_name.has(verb):
		return command_cn_name[verb]
	return verb

# 判断动词是否是移动命令
func is_move_command(verb: String) -> bool:
	var move_verbs := ["go", "north", "south", "east", "west", "n", "s", "e", "w",
		"up", "down", "in", "out", "enter", "bei", "nan", "dong", "xi", "shang", "xia", "jin", "chu"]
	return move_verbs.has(verb)
