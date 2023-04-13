extends Sprite2D

func _ready():
	super.hide()



func _on_AnimationPlayer_animation_finished(anim_name):
	super.hide()


func _on_AnimationPlayer_animation_started(anim_name):
	super.show()
