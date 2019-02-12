extends "res://characters/Character.gd"

var skill_anim = null
var actor_data = Global.player_data
func _ready():
	# $Balloon.hide()
	print(actor_data)
	pass
	

	
func _process(delta):
	if can_move:
		for dir in moves.keys():
			if Input.is_action_pressed(dir):
				facing = dir
				if dir == 'left':
					$Balloon.flip_h = true
					$Balloon.offset = Vector2(-16,0)
				elif dir == 'right':
					$Balloon.flip_h = false
					$Balloon.offset = Vector2(16,0)
				else:
					$Balloon.flip_h = false
					$Balloon.offset = Vector2(0,0)
				move(facing)
	
	if Input.is_action_pressed("A"):
		#attack(facing)
#		var sprite_frames = Global.creat_sprite_frames_from_path()
		$"Balloon/AnimationPlayer".play("ballon05")
		#$"Skill/AnimatedSprite".play('default')
		# $Balloon.hide()
	if Input.is_action_just_pressed("B"):
		skill_anim = $Skill/Area2D/AnimatedSprite
		#skill_anim.show()
		skill_anim.position = moves[facing]*48
		skill_anim.play('default')
		skill_anim.frame = 0
		$Skill/Label/AnimationPlayer.play("anim_skill")
		#skill_anim.hide()
	