extends Node2D

func _ready():
	call_out("test",0.5)
		
		
		
#onready var timer = get_tree().create_timer()

func call_out(func_name,time):
	var timer = get_tree().create_timer(time)
	timer.connect("timeout",self,func_name)
	
var i = 1	
func test():
	i = i+1
	print_debug(str(i))
	call_out("test",0.5)