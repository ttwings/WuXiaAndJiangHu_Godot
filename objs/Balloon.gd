extends Sprite

func _ready():
	.hide()


func _on_AnimationPlayer_animation_finished():
	.hide()


func _on_AnimationPlayer_animation_started():
	.show()
