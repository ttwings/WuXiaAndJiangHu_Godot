extends Node

class_name Global
# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var actors = load_data("res://data/actorDataNew.json")
var player_data = actors[0]
var skills = load_data("res://data/attackSkillData.json")
var deffence_skills
var foods
var herbs


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
func save():
	var  save_dict = {
		"filename" : get_filename(),
		"parent" : get_parent(),
		#"pos_x" : position.x,
		#"pos_y" : position.y,
		
		}
	return save_dict

func save_game():
	var save_game = File.new()
	save_game.open("user://savegame.save",File.WRITE)
	var save_nodes = get_tree().get_nodes_in_group("Persist")
	for i in save_nodes:
		var node_data = i.call("save")
		save_game.store_line(to_json(node_data))
	save_game.close()
	
func load_game():
	var save_game = File.new()
	if not save_game.file_exists("user://savegame.save"):
		return
	
	var save_nodes = get_tree().get_nodes_in_group("Persist")
	for i in save_nodes:
		i.queue_free()
	
	save_game.open("user://savegame.save",File.READ)
	while not save_game.eof_reached():
		var current_line = parse_json(save_game.get_line())
		var new_object = load(current_line["filename"]).instance()
		get_node(current_line["parent"].add_child(new_object))
		new_object.position = Vector2(current_line["pos_x"],current_line["pos_y"])
		for i in current_line.keys():
			if i == "filename" or i== "parent" or i == "pos_x" or i == "pos_y" :
				continue
			new_object.set(i,current_line[i])
	save_game.close()
	
	
func load_data(path:String):
	var load_data = File.new()
	if not load_data.file_exists(path):
		print_debug("not exists file")
		return
	
	load_data.open(path,File.READ)

	var data_str = load_data.get_as_text()
	var p = JSON.parse(data_str)
	return p.result
				