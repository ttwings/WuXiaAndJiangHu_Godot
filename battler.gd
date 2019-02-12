extends Node

class_name Battler
# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var hp
var mp
var ap
var _str

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func onHit(from,to):
	playAnimation(from,to)
	hpChange(from,to)
	pass
	
func playAnimation(from,to):
	pass
	
func hpChange(from,to):
	pass