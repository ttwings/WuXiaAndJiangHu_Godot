@tool
extends Control

#var player_data setget ,get_player_data

func _load_player_save():
	var path = "user://save/1/player.json"
	if FileAccess.file_exists(path):
		var f = FileAccess.open(path, FileAccess.READ)
		if f:
			var data = JSON.parse_string(f.get_as_text())
			f.close()
			return data
	return null

var player_data = _load_player_save()

var player = Char.new()

func _ready():
	if player_data and player_data.has("dbase"):
		player.dbase = player_data.dbase
	player.carry_object("/clone/food/apple")
	dic2bbcode(player.dbase)
	pass
#
func dic2bbcode(char_dic:Dictionary):
	for key in char_dic.keys() :
		var path = "Label_" + key + "/value"
		if has_node(path) :
			if get_node(path) as Label :
				get_node(path).text = str(char_dic[key])
