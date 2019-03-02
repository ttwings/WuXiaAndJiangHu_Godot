extends Node2D

func _ready():
	pass

func _input(event):
	if event.is_action_pressed("A"):
		$ActorAnimatedSprite.frame = 1
		$ActorAnimatedSprite.play()
		yield($ActorAnimatedSprite,"animation_finished")
		$Sprite.show()
		$Sprite/AnimationPlayer.play()