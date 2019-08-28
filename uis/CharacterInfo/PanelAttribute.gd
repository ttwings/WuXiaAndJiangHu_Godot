tool
extends Control

#var player_data setget ,get_player_data

var player_data = gdutils.utils.json.load_json("user://data/user/id.json")

var player = Char.new()

func _ready():
#	player_data = gdutils.utils.json.load_json("res://data/user/l/lijia.json")
#	print(player_data)
#	$RichTextLabel.bbcode_text =  dic2bbcode(player_data.dbase)
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
#
#func get_player_data():
#	return player_data
