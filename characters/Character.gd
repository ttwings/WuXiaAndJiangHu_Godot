extends Area2D

@export var head_id: int = 0
var tile_size = 32
var can_move = true
var can_attack = false
var facing = 'right'
var moves = {'right': Vector2(1, 0),
			 'left': Vector2(-1, 0),
			 'up': Vector2(0, -1),
			 'down': Vector2(0, 1)}
var raycasts = {'right': 'RayCastRight',
				'left' : 'RayCastLeft',
				'up': 'RayCastUp',
				'down': 'RayCastDown'}
var attack_raycasts = {'right': 'AttackRayCastRight',
				'left' : 'AttackRayCastLeft',
				'up': 'AttackRayCastUp',
				'down': 'AttackRayCastDown'}

func move(dir):
	if get_node(raycasts[facing]).is_colliding():
		return
	facing = dir
	can_move = false
	$AnimationPlayer.play(facing)
	$MoveTween.interpolate_property(self, "position", position,
			position + moves[facing] * tile_size, 0.6,
			Tween.TRANS_LINEAR, Tween.EASE_IN_OUT)
	$MoveTween.start()
	#position = position + moves[facing] * tile_size * 0.16
	return true

func attack(dir):
	if get_node(attack_raycasts[facing]).is_colliding():
		return
	facing = dir
	can_move = false
	$AnimationPlayer.play(facing)
	$AttackTween.interpolate_property(self, "position", position,
			position + moves[facing] * tile_size * 1, 0.4,
			Tween.TRANS_SINE, Tween.EASE_IN_OUT)
	# $MoveTween.interpolate_property(self, "position", position,
	#							position - moves[facing] * tile_size * 2, 0.4,
	#							Tween.TRANS_SINE, Tween.EASE_IN_OUT)
	$AttackTween.start()
	return true


func _on_MoveTween_tween_completed( object, key ):
	can_move = true
