extends Node2D

class_name Room
# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var pos_n = Vector2()
var pos_en = Vector2()
var pos_e = Vector2()
var pos_es = Vector2()
var pos_s = Vector2()
var pos_ws = Vector2()
var pos_w = Vector2()
var pos_wn = Vector2()

export var pos_1 = Vector2()
export var pos_2 = Vector2()

var id:String
var name_cn:String
var description:String
var x:int
var y:int
var inside:bool
var safe:bool
var actions:Array
var objs:Array
var actors:Array
# Called when the node enters the scene tree for the first time.
func _init():
	id = "wuguan_cai_yuan"
	name_cn = "菜园"
	x = 32
	y = 32
	inside = false
	safe = false
	actions = ["浇水"]
	objs = ["水缸"]
	actors = ["管家"]
	description = """这里是一座极大的菜园，种满了油菜，萝卜，茄子，丝瓜之类。
	周围的篱笆都破了，看来要整修了。菜园旁有几口大缸，里面盛满了水，可是菜地看起来都干裂了，几棵菜蔫蔫的长着，是缺水太多了"""

func _ready():
	$Label.text = name_cn
	position.x = x
	position.y = y
	$ColorRect/Panel/Description.text = description
	for i in objs:
		$ColorRect/Panel/ItemList.add_item(i)
		
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _on_ColorRect_mouse_entered():
	$ColorRect/Panel.show()
	pass # Replace with function body.
	
	


func _on_Panel_mouse_exited():
	$ColorRect/Panel.hide()
	pass # Replace with function body.


func _on_Action1_pressed():
	pass # Replace with function body.
