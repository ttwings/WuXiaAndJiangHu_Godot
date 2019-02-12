extends Button

# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var can_pressed = true
# Called when the node enters the scene tree for the first time.
func _ready():

	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _process(delta):
		if $ProgressBar.value == $ProgressBar.max_value :
			can_pressed = true


func _on_ProgressButton_pressed():
	if can_pressed:
		print("action")
		$ProgressBar.value += 1
	else:
		print("busying")
	pass # Replace with function body.
