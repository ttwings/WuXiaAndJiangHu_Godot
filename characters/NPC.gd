extends "res://characters/Character.gd"

var textures = ['actor_001.png', 'actor_005.png',
				'actor_006.png', 'actor_013.png',
				'actor_014.png', 'actor_015.png']

func _ready():
	randomize()
	var texture = textures[randi() % textures.size()]
	texture = load("res://assets/graphics/characters/%s" % texture)
	$Sprite.texture = texture
	facing = moves.keys()[randi() % 4]

func _process(delta):
	if can_move:
		if not move(facing) or randi() % 10 > 5:
			facing = moves.keys()[randi() % 4]
