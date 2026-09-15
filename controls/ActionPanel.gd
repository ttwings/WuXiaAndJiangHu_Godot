# ActionPanel.gd - 上下文动作面板
# 根据目标对象类型自动生成操作按钮

extends PanelContainer
class_name ActionPanel

# Preload types to avoid class_name resolution issues
const WeaponScript = preload("res://inherit/Weapon.gd")
const FoodScript = preload("res://inherit/Food.gd")

var actor = null
var target = null
var buttons_container: VBoxContainer

func _ready():
	buttons_container = VBoxContainer.new()
	add_child(buttons_container)

func setup(actor_ref, target_ref) -> void:
	actor = actor_ref
	target = target_ref
	_refresh()

func _refresh() -> void:
	# 清空旧按钮
	for child in buttons_container.get_children():
		child.queue_free()
	if target == null:
		return

	var verbs = _get_verbs_for_target(target)
	for verb in verbs:
		var btn = ActionButton.new()
		btn.setup(verb, target.query("id") if target.has_method("query") else "", actor)
		btn.custom_minimum_size = Vector2(120, 36)
		buttons_container.add_child(btn)

# 根据目标类型返回可用动词
func _get_verbs_for_target(obj) -> Array:
	var verbs = []

	# 判断对象类型
	var obj_type = ""
	if obj.has_method("query"):
		obj_type = obj.query("type")

	if obj_type == "food" or obj is FoodScript:
		verbs = ["eat", "get", "drop"]
	elif obj_type == "weapon" or obj is WeaponScript:
		verbs = ["wear", "get", "drop"]
	elif obj is Npc or obj is Char:
		if obj != actor:
			verbs = ["ask", "kill", "fight"]
		else:
			verbs = ["look", "inventory", "score"]
	else:
		verbs = ["get", "drop"]

	return verbs
