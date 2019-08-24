extends Control

# Declare member variables here. Examples:
# var a: int = 2
# var b: String = "text"
var json_data
var current_path
var path = "user://data/user/id.json"
var pool = {path=""}
# Called when the node enters the scene tree for the first time.
func _ready() -> void:
#	TranslationServer.set_locale("zh_CN")
	
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta: float) -> void:
#	pass


func _on_Save_pressed() -> void:
	json_data.dbase["food"] = 100
	var id = json_data.dbase["id"]
	gdutils.utils.json.save_json(json_data,"user://data/user/id.json")
	print(json_data)
	print(path)
	pass


func _on_Load_pressed() -> void:
#	$Panel/FileDialog.show()
	json_data = gdutils.utils.json.load_json(path)
	$Panel/TextEdit.text = str(json_data)
	pass


func _on_FileDialog_file_selected(path: String) -> void:
	current_path = $Panel/FileDialog.current_path
	pool.path = current_path
	print(current_path)
	json_data = gdutils.utils.json.load_json(path)
	$Panel/TextEdit.text = str(json_data)
	pass


func _on_TextEdit_text_changed() -> void:
#	json_data = JSON.print($Panel/TextEdit.text)
#	print($Panel/TextEdit.text as Dictionary)
#	print(pool.pop_back())
	path = pool.path
	$Panel/LabelMessage.text = "注意：文件内容已经发生修改。"
	print(path)
	pass # Replace with function body.
