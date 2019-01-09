extends Node2D



func _on_AnimationPlayer_animation_finished(anim_name):
	$Label.hide()


func _on_AnimatedSprite_animation_finished():
	$AnimatedSprite.hide()
