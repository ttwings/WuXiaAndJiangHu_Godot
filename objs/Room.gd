extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var pos_n = Vector2()
var pos_en = Vector2()
var pos_e = Vector2()
var pos_es = Vector2()
var pos_s = Vector2()
var pos_ws = Vector2()
var pos_w = Vector2()
var pos_wn = Vector2()

export var pos_1 = Vector2()
export var pos_2 = Vector2()

# Called when the node enters the scene tree for the first time.
func _ready():
	
	pass # Replace with function body.

func _process(delta):
	var line = Line2D.new()
	line.width = 10
	$Lines.add_child(line)
	line.add_point(pos_1)
	line.add_point(pos_2)
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
