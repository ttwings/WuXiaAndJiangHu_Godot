extends Node2D

export(String,DIR) var path
export(String,"png","jpg","jpeg") var suffix

var frame_list = []
var actors = []
var can_play_anim = true

func _ready():
	$AnimatedSprite.frames = Global.creat_sprite_frames_from_path("default",path,"png")
	$AnimatedSprite.frame = 1
	$AnimatedSprite.play()
	#print($AnimatedSprite.frames.size())
	pass

func _input(event):
	if event.is_action_pressed("A") and can_play_anim:
		can_play_anim = false
		$AnimatedSprite2.frame = 1
		$AnimatedSprite2.show()
		$AnimatedSprite2.play()
		yield($AnimatedSprite2,"animation_finished")
		$AnimatedSprite2.hide()
		can_play_anim = true