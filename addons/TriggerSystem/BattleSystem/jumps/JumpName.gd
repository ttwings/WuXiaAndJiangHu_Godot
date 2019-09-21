extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var name_label
var timer = 0.5
var color = Color(1,1,0,1)

# Called when the node enters the scene tree for the first time.
func _ready():
	name_label = $Label
	name_label.text = "test"
	modulate = color
	pass # Replace with function body.

func _process(delta):
	timer = timer - delta
	if timer <= 0:
		queue_free()
	position.y = position.y - 100 * delta
	pass
	
func start(name_cn,pos,color):
#	name_label.text = name_cn
#	name_label.font_color = color
	modulate = color
	name_label.text = name_cn
	position = pos
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
