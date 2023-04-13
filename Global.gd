extends Node

var deffence_skills
var foods
var herbs
var user_class
# 全局房间字典，key为房间路径，v为实例

var all_current_rooms = {}
	
func load_room(path:String):
	if all_current_rooms.has(path):
		return all_current_rooms[path]
	else:
		var room = load(path).new()
		all_current_rooms[path] = room
		return room

# 保存房间数据
func save_current_rooms():
	for path in all_current_rooms:
		ResourceSaver.save(path,all_current_rooms[path])		

func save():
	var  save_dict = {
		"filename" : get_scene_file_path(),
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
		save_game.store_line(JSON.new().stringify(node_data))
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
		var test_json_conv = JSON.new()
		test_json_conv.parse(save_game.get_line())
		var current_line = test_json_conv.get_data()
		var new_object = load(current_line["filename"]).instantiate()
		get_node(current_line["parent"].add_child(new_object))
		new_object.position = Vector2(current_line["pos_x"],current_line["pos_y"])
		for i in current_line.keys():
			if i == "filename" or i== "parent" or i == "pos_x" or i == "pos_y" :
				continue
			new_object.set(i,current_line[i])
	save_game.close()
	
# 读取JSON格式的数据文件	
func load_data(path:String):
	var load_data = File.new()
	if not load_data.file_exists(path):
		print_debug("not exists file")
		return
	
	load_data.open(path,File.READ)

	var data_str = load_data.get_as_text()
	var test_json_conv = JSON.new()
	test_json_conv.parse(data_str)
	var p = test_json_conv.get_data()
	return p.result
	

func dir_contents(path):
	var dir = DirAccess.new()
	if dir.open(path) == OK:
		dir.list_dir_begin() # TODOGODOT4 fill missing arguments https://github.com/godotengine/godot/pull/40547
		var file_name = dir.get_next()
		while (file_name != ""):
			if dir.current_is_dir():
				print("Found directory: " + file_name)
			else:
				print("Found file: " + file_name)
			file_name = dir.get_next()
	else:
		print("An error occurred when trying to access the path.")

# 获取path目录下特定后缀suffix文件

func dir_files(path,suffix):
	var dir = DirAccess.new()
	var files = []
	if dir.open(path) == OK:
		dir.list_dir_begin() # TODOGODOT4 fill missing arguments https://github.com/godotengine/godot/pull/40547
		var file_name = dir.get_next()
		while (file_name!= ""):
			if dir.current_is_dir():
				print("Found directory" + file_name)
			elif file_name.split(".")[-1] == suffix:
				files.append(file_name)
				print("Found file: " + file_name)
			else:
				pass
				#print("Found file: " + file_name)
			file_name = dir.get_next()
	else:
		print("An error ccurred when trying to access the path.")
	return files	

# 获取目录path下的suffix后缀图片文件生成anim名称的 sprite frames	
func creat_sprite_frames_from_path(anim:String,path:String,suffix:String):
	var sprite_files = dir_files(path,suffix)
	var sprite_frames = SpriteFrames.new()
	var texture_files = []
	var texture
	#sprite_frames.add_animation(anim)
	for i in sprite_files.size() :
		texture_files.append(path + "/" + sprite_files[i])
	texture_files.sort()
	for i in texture_files.size() :
		texture = load(texture_files[i])
		sprite_frames.add_frame(anim,texture)
	return sprite_frames
						
# 依据数值 改变颜色名称
func get_number_color(number):
	if number < 0: 
		return "red" 
	else:
		return "green"
		
# 将整数数字转为中文文字	
func chinese_number(n:int):
	var number_str = str(n)
	var l = number_str.length()
	var output = []
	for i in range(l):
		number_str[i] = swap_to_font(number_str[i])
	return number_str
	
# 配合上面转化
func swap_to_font(number):
	match number:
		"1":return "一"
		"2":return "二"
		"3":return "三"
		"4":return "四"
		"5":return "五"
		"6":return "六"
		"7":return "七"
		"8":return "八"
		"9":return "九"
		"0":return "〇"
		_:return "X"	
