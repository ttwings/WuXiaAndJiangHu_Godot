extends VBoxContainer
class_name ActionPanel

# ActionPanel - 上下文动作面板
# 根据目标对象的类型，自动生成对应的操作按钮，替代 MUD 中的文字命令输入。
#
# 用法：
#   var panel = ActionPanel.new()
#   panel.setup(target_object, player)
#   add_child(panel)

const ActionButtonScript = preload("res://controls/ActionButton.gd")

var actor = null
var target = null

# 按钮容器
var _btn_container: HBoxContainer = null

func _ready() -> void:
	# 创建按钮行容器
	_btn_container = HBoxContainer.new()
	_btn_container.add_theme_constant_override("separation", 8)
	add_child(_btn_container)

# 设置目标对象并生成按钮
func setup(p_target, p_actor = null) -> void:
	target = p_target
	actor = p_actor
	refresh()

# 清空并重新生成按钮
func refresh() -> void:
	# 清空旧按钮
	if _btn_container:
		for c in _btn_container.get_children():
			c.queue_free()
	else:
		_btn_container = HBoxContainer.new()
		_btn_container.add_theme_constant_override("separation", 8)
		add_child(_btn_container)

	if target == null:
		return

	var verbs := _get_verbs_for_target(target)
	for v in verbs:
		var btn: ActionButton = ActionButtonScript.new()
		btn.setup(v, target, actor)
		_btn_container.add_child(btn)

# 根据目标类型返回可用的命令动词列表
func _get_verbs_for_target(ob) -> Array:
	var verbs: Array = []

	# 通用：查看
	verbs.append("look")

	# 判断对象类型，添加对应操作
	if ob is Food:
		verbs.append("eat")
		verbs.append("drop")
	elif ob is Weapon:
		verbs.append("wield")
		verbs.append("drop")
	elif ob is Armor:
		verbs.append("wear")
		verbs.append("drop")
	elif ob is Equip:
		verbs.append("wear")
		verbs.append("drop")
	elif ob is Npc or ob is Char:
		verbs.append("ask")
		verbs.append("kill")
		verbs.append("give")
		verbs.append("follow")
	elif ob is Room:
		pass  # 房间只有 look，移动由出口按钮处理
	else:
		# 通用物品
		verbs.append("get")
		verbs.append("drop")

	return verbs
