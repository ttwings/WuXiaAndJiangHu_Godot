extends Control

# Declare member variables here. Examples:
# var a: int = 2
# var b: String = "text"
@onready var container = $Panel/ScrollContainer/VBoxContainer

var objects = {}
# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	objects["res://clone/food/apple.gd"] = 1
	objects["res://clone/food/baijiu.gd"] = 2
	init_objects(objects)
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta: float) -> void:
#	pass

func init_objects(objects):
	for k in objects :
		add_obj_button(k)

func add_obj_button(ob):
	var button = Button.new()
	var _ob = load(ob).new()
	button.text = _ob.name()
	button.connect("pressed", Callable(self, "show_ob").bind(_ob))
	container.add_child(button)
	
func show_ob(ob):
	$ObjectPanel.start(ob)
	