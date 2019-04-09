extends Control

# Declare member variables here. Examples:
# var a: int = 2
# var b: String = "text"

# Called when the node enters the scene tree for the first time.
onready var list = $ItemList
var objects = {
	"物品1":1,
	"物品2":2,
	"物品3":3,
}
func _ready() -> void:
	for o in objects :
		list.add_item(o)
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta: float) -> void:
#	pass
