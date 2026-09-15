# ActionButton.gd - 可复用的动作按钮控件
# 绑定命令动词与目标对象，点击后触发命令

extends Button
class_name ActionButton

@export var verb: String = ""
@export var target_id: String = ""
@export var actor = null  # 执行命令的角色

func _ready():
	pressed.connect(_on_pressed)

func setup(verb_name: String, target: String, actor_ref) -> void:
	verb = verb_name
	target_id = target
	actor = actor_ref
	text = verb_name

func _on_pressed() -> void:
	if actor == null or verb == "":
		return
	var arg = target_id
	if target_id != "":
		actor.command(verb + " " + target_id)
	else:
		actor.command(verb)
