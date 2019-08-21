extends Control

var can_pressed = true

func _ready():
	pass

func _process(delta):
	$ProgressBar.value += 1
	if $ProgressBar.value == $ProgressBar.max_value :
		can_pressed = true

func _on_Button_pressed():
	if can_pressed:
		print_debug("action")
		can_pressed = false
		$ProgressBar.value = 0
	else:
		print_debug("busying")
	pass # Replace with function body.
