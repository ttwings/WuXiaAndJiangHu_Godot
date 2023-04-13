extends Control

# Declare member variables here. Examples:
# var a: int = 2
# var b: String = "text"
var path = "res://kungfu/skill/cookery.gd"
var skill
# Called when the node enters the scene tree for the first time.
func _ready() -> void:
#	skill.help()
#	print(skill.get_info())
	skill = load(path).new()
	$NinePatchRect/RichTextLabel.text = skill.get_info()
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta: float) -> void:
#	pass
