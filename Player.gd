extends Node
class_name Player
var player
# 从数据字典,生成角色
func creat_user(file):
	var user = load(file).new()
	var player = Char.new()
	player.dbase = user.dbase
	return player

# Called when the node enters the scene tree for the first time.
func _ready():
	player = creat_user("res://data/user/l/lijia.gd")
	pass # Replace with function body.