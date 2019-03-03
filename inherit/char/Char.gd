extends GameObject

class_name Char

func _ready():
	var dir = Directory.new()
	var dirs = get_path()
	print(dirs)