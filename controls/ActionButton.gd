extends Button
class_name ActionButton

# ActionButton - 可复用的动作按钮控件
# 将 MUD 命令（动词 + 目标）封装成按钮，点击即执行，替代文字输入。
#
# 用法：
#   var btn = ActionButton.new()
#   btn.setup("eat", food_item, player)
#   add_child(btn)

# 命令动词，如 "eat", "drink", "kill", "look"
var verb: String = ""
# 命令的目标对象（物品/NPC/房间等），可为空
var target = null
# 执行命令的角色（通常是玩家）
var actor = null
# 额外参数字符串，如技能名
var extra_arg: String = ""

signal action_executed(verb: String, target, actor)

func _ready() -> void:
	if not text.is_empty():
		pass  # 保留已有文本
	custom_minimum_size = Vector2(80, 32)
	pressed.connect(_on_pressed)

# 配置按钮
func setup(p_verb: String, p_target = null, p_actor = null, p_extra: String = "") -> void:
	verb = p_verb
	target = p_target
	actor = p_actor
	extra_arg = p_extra
	# 自动设置按钮文本为命令中文名
	var cn := COMMAND_D.get_cn_name(verb) if COMMAND_D else verb
	if target and target.has_method("name"):
		var tn = target.name()
		if tn and tn != "":
			text = "%s %s" % [cn, tn]
		else:
			text = cn
	else:
		text = cn

func _on_pressed() -> void:
	execute()

# 执行绑定的命令
func execute() -> void:
	if actor == null:
		# 尝试从全局获取玩家
		if Global and Global.has_method("this_player"):
			actor = Global.this_player()
	if actor == null:
		push_warning("ActionButton: 没有指定执行者(actor)")
		return

	# 构造命令字符串：动词 [目标id] [额外参数]
	var cmd := verb
	if target and target.has_method("query"):
		var tid = target.query("id")
		if tid and tid != "" and tid != 0:
			cmd = "%s %s" % [verb, tid]
	if extra_arg != "":
		cmd = "%s %s" % [cmd, extra_arg]

	actor.command(cmd)
	emit_signal("action_executed", verb, target, actor)
