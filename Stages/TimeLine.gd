extends TextureProgress

# Declare member variables here. Examples:
# var a: int = 2
# var b: String = "text"
onready var player1_start_pos = $PositionPlayer.position
onready var player2_start_pos = $PositionPlayer.position
onready var player1_pos = $PositionPlayer.position
onready var player2_pos = $PositionPlayer.position
onready var enemy1_start_pos = $PositionEnemy.position
onready var enemy2_start_pos = $PositionEnemy.position
onready var enemy1_pos = $PositionEnemy.position
onready var enemy2_pos = $PositionEnemy.position

var player1 = {
	"speed":100
}
var player2 = {
	"speed":120
}
var enemy1 = {
	"speed":110
}
var enemy2 = {
	"speed":130
}

var battlers = []
# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	battlers.append(player1)
	battlers.append(player2)
	battlers.append(enemy1)
	battlers.append(enemy2)
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta: float) -> void:
#	pass
func _process(delta: float) -> void:
	player1_pos.x += player1.speed * delta
	if player1_pos.x > 100 :
		player1_pos.x = player1_start_pos.x
	$Player1Head.position = player1_pos
	
func update_battlers_cd():
	for i in range(battlers.size()) :
		battlers[i]	