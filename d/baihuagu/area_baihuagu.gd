extends Node2D

func _ready():
	print(self.get_script().get_path().get_base_dir())