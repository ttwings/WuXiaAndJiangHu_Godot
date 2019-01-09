extends Sprite

func _ready():
	.hide()



func _on_AnimationPlayer_animation_finished(anim_name):
	.hide()


func _on_AnimationPlayer_animation_started(anim_name):
	.show()
