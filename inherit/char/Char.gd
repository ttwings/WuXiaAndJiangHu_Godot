extends GameObject

class_name Char

func _ready():
	var dir = Directory.new()
	var file = filename.get_base_dir()
	var dirs = get_path()
	print(file)