extends Node2D

export(String,DIR) var path
export(String,"png","jpg","jpeg") var suffix

var frame_list = []
var actors = []

func _ready():
	print(suffix)
	$AnimatedSprite.frames = Global.creat_sprite_frames_from_path("default",path,"png")
	$AnimatedSprite.set_frame(1)
	$AnimatedSprite.play()
	print(actors.size())
	print(frame_list.size())
	
	$AnimatedSprite2.play()
	yield($AnimatedSprite2,"animation_finished")
	$AnimatedSprite2.hide()
	pass
