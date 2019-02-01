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
	name_cn = "菜园 ceshi"
	x = 32
	y = 32
	inside = false
	safe = false
	actions = ["浇水"]
	objs = ["水缸"]
	actors = ["管家"]
	description = """ceshi这里是一座极大的菜园，种满了油菜，萝卜，茄子，丝瓜之类。
	周围的篱笆都破了，看来要整修了。菜园旁有几口大缸，里面盛满了水，可是菜地看起来都干裂了，几棵菜蔫蔫的长着，是缺水太多了"""

func _ready():
	$Label.text = name_cn
	position.x = x
	position.y = y
	$Button/Panel/Description.text = description
	pass # Replace with function body.

func _process(delta):
	var line = Line2D.new()
	line.width = 10
	$Lines.add_child(line)
	line.add_point(pos_1)
	line.add_point(pos_2)
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
