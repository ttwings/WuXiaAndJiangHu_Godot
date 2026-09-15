extends Control

var json_data
var current_path
var path = "user://save/1/player.json"
var pool = {path=""}

func _save_json(data, file_path: String):
	var f = FileAccess.open(file_path, FileAccess.WRITE)
	if f:
		f.store_string(JSON.stringify(data, "\t"))
		f.close()

func _load_json(file_path: String):
	if FileAccess.file_exists(file_path):
		var f = FileAccess.open(file_path, FileAccess.READ)
		if f:
			var data = JSON.parse_string(f.get_as_text())
			f.close()
			return data
	return null

func _ready() -> void:
	pass

func _on_Save_pressed() -> void:
	json_data.dbase["food"] = 100
	var id = json_data.dbase["id"]
	_save_json(json_data,"user://save/1/player.json")
	print(json_data)
	print(path)
	pass


func _on_Load_pressed() -> void:
	json_data = _load_json(path)
	$Panel/TextEdit.text = str(json_data)
	pass


func _on_FileDialog_file_selected(path: String) -> void:
	current_path = $Panel/FileDialog.current_path
	pool.path = current_path
	print(current_path)
	json_data = _load_json(path)
	$Panel/TextEdit.text = str(json_data)
	pass


func _on_TextEdit_text_changed() -> void:
	path = pool.path
	$Panel/LabelMessage.text = "注意：文件内容已经发生修改。"
	print(path)
	pass
