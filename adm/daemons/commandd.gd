# commandd.gd - 命令注册中心
# 将 MUD 命令动词映射到 Char 上的处理方法

extends Node

# 命令动词 -> 处理方法名 的映射
var command_table = {
	# 移动
	"north": "_do_move", "south": "_do_move", "east": "_do_move", "west": "_do_move",
	"northeast": "_do_move", "northwest": "_do_move", "southeast": "_do_move", "southwest": "_do_move",
	"up": "_do_move", "down": "_do_move", "enter": "_do_move", "out": "_do_move",
	"n": "_do_move", "s": "_do_move", "e": "_do_move", "w": "_do_move",
	"ne": "_do_move", "nw": "_do_move", "se": "_do_move", "sw": "_do_move",
	"u": "_do_move", "d": "_do_move",

	# 观察
	"look": "do_look", "l": "do_look", "i": "do_inventory", "inventory": "do_inventory",
	"score": "do_score", "skills": "do_skills", "sk": "do_skills",

	# 交互
	"get": "do_get", "drop": "do_drop", "eat": "do_eat", "drink": "do_drink",
	"wear": "do_wear", "remove": "do_remove", "give": "do_give", "put": "do_put",

	# 战斗
	"kill": "do_kill", "k": "do_kill", "fight": "do_fight",
	"perform": "do_perform", "exert": "do_exert",

	# 社交
	"say": "do_say", "ask": "do_ask", "answer": "do_answer",
	"whisper": "do_whisper", "tell": "do_tell",

	# 其他
	"save": "do_save", "quit": "do_quit", "help": "do_help",
}

# 方向映射（简写 -> 完整方向）
var dir_map = {
	"n": "north", "s": "south", "e": "east", "w": "west",
	"ne": "northeast", "nw": "northwest", "se": "southeast", "sw": "southwest",
	"u": "up", "d": "down",
}

# 注册自定义命令
func register_command(verb: String, handler: String) -> void:
	command_table[verb] = handler

# 查找命令对应的处理方法
func query_command(verb: String) -> String:
	if command_table.has(verb):
		return command_table[verb]
	return ""

# 执行命令
func do_command(actor, verb: String, arg: String = "") -> bool:
	var handler = query_command(verb)
	if handler == "":
		return false
	if not actor.has_method(handler):
		return false
	if handler == "_do_move":
		actor._do_move(dir_map.get(verb, verb))
	else:
		actor.call(handler, arg)
	return true

# 获取所有可用命令
func get_all_commands() -> Array:
	return command_table.keys()
