extends Node2D

class_name Skill

export(String,DIR) var path
export(String,"png","jpg","jpeg") var suffix

var frame_list = []
var can_play_anim = true

func _ready():
	pass

func _input(event):
	if event.is_action_pressed("A") and can_play_anim:
		can_play_anim = false
		$AnimatedSprite.frames = Global.creat_sprite_frames_from_path("default",path,"png")
		$AnimatedSprite.frame = 1
		$AnimatedSprite.speed_scale = 5
		$AnimatedSprite.show()
		$AnimatedSprite.play("default")
		yield($AnimatedSprite,"animation_finished")
		$AnimatedSprite.hide()
		can_play_anim = true