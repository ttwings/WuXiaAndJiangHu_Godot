extends Node2D

export(String) var label_name = ""

func _ready():
	$Label.hide()


func _on_Area2D_mouse_entered():
	$Label.show() # Replace with function body.


func _on_Area2D_mouse_exited():
	$Label.hide() # Replace with function body.
