extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
var current_time = 0
var max_time = 100
var step_time
var texture_length

var player_turn = 0.0
var enemy_turn = 0.0

var player_dex = 5
var enemy_dex = 4

var bar_pos = Vector2()
func _ready():
	$TimeLine.value = current_time
	bar_pos = $TimeLine.rect_position
	pass # Replace with function body.

func _process(delta):
	if current_time > max_time:
		current_time = 0
	current_time = current_time + delta*5
	player_turn = player_turn + delta*player_dex
	enemy_turn = enemy_turn + delta*enemy_dex
	$TimeLine.value = current_time
	$TimeLine/Label.text = str(int(current_time))
	
	$TimeLine/PlayerHead.position = Vector2(player_turn,-28)
	# print(int(current_time))
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
