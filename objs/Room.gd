extends Node2D

#class_name Room
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
var exits = {}
# person
var weapon1 = {id = "piao",name = "瓢"}
var mark1 = { jiao = 0}
var me = {
	name_cn = "孙悟",
	weapon = weapon1,
	mark = mark1,
	job_name = "浇灌菜地",
	is_busy = false,
	is_fighting = false,
	Con = 8,
	Str = 3,
	Int = 12,
	jingli = 10,
	qi = 2,
	force = 10
		}
# Called when the node enters the scene tree for the first time.

var Room_gd = load("res://d/baihuagu/baihuagu.gd")
var current_room = Room_gd.new()
func create():
	id = "wuguan_cai_yuan"
	name_cn = "菜园"
	x = 32
	y = 32
	inside = false
	safe = true
	actions = ["浇水"]
	objs = ["水缸"]
	actors = ["管家"]
	description = """这里是一座极大的菜园，种满了油菜，萝卜，茄子，丝瓜之类。
	周围的篱笆都破了，看来要整修了。菜园旁有几口大缸，里面盛满了水，可是菜地看起来都干裂了，几棵菜蔫蔫的长着，是缺水太多了"""
	# test 
# 1  2  3
# 4  5  6
# 7  8  9 
var neighbor_rooms = {}
func creat_exits(exits):
	neighbor_rooms = {}
	$NinePatchRect2/GridContainer/Door01.text = ""
	$NinePatchRect2/GridContainer/Door02.text = ""
	$NinePatchRect2/GridContainer/Door03.text = ""
	$NinePatchRect2/GridContainer/Door04.text = ""
	$NinePatchRect2/GridContainer/Door05.text = ""
	$NinePatchRect2/GridContainer/Door06.text = ""
	$NinePatchRect2/GridContainer/Door07.text = ""
	$NinePatchRect2/GridContainer/Door08.text = ""
	$NinePatchRect2/GridContainer/Door09.text = ""
	for direct in exits:
		if exits[direct] :
			match direct:
				"east" : 
					neighbor_rooms[direct] = load(exits[direct] + ".gd")
					$NinePatchRect2/GridContainer/Door04.text = "东"
				"west":
					neighbor_rooms[direct] = load(exits[direct] + ".gd")
					$NinePatchRect2/GridContainer/Door06.text = "西"
				"south":
					neighbor_rooms[direct] = load(exits[direct] + ".gd").new()
					$NinePatchRect2/GridContainer/Door08.text = "南"
#					if $NinePatchRect2/GridContainer/Door08.is_pressed() :
#						current_room = neighbor_rooms[direct]
#						print(current_room.query("short"))
				"north":
					$NinePatchRect2/GridContainer/Door02.text = "北"
				"out":
					neighbor_rooms[direct] = load(exits[direct] + ".gd").new()
					$NinePatchRect2/GridContainer/Door09.text = "出去"
				"in":
					$NinePatchRect2/GridContainer/Door05.text = exits[direct]
				x:
					$NinePatchRect2/GridContainer/Door03.text = exits[direct]
				

func _ready():
#	$RoomName.bbcode_text = name_cn
#	position.x = x
#	position.y = y
	var dir = filename.get_base_dir()
	print(dir)
	create()
	creat_exits(current_room.query("exits"))
	$RoomName.bbcode_text = current_room.query("short")
	$NinePatchRect/Description.bbcode_text = current_room.query("long")
	$NinePatchRect4/VBoxContainer/ActionButton01.text = "浇水"

	pass # Replace with function body.

func do_jiao():
	var me = self.me
	var weapon
	var costj
	var costq
	if me.job_name != "浇灌菜地" :
		return notify_fail("你必须跟馆主领了这工作才能在这里干!")
	if me.is_busy :
		return notify_fail("你现在正忙着呢!")
	if me.is_fighting :
		return notify_fail("你正在战斗中！")
	weapon = me.weapon
	if me.weapon.id != "piao" :
		return notify_fail("你想用什么来舀水浇，用手吗？")
	costj = int(rand_range(1,(me.Con/3)))
	costq = int(rand_range(1,(me.Str/3)))
	if me.jingli < costj or me.qi < costq :
		message_vision("[color=red]{name_cn}弯腰到大缸里舀水，结果失足栽到缸里。[/color]".format(me),null)
		return
	me.jingli = max(0,me.jingli - costj)
	me.qi = max(0,me.qi - costq)
	if me.mark.jiao and me.mark.jiao > 15 + int(rand_range(0,5)) :
		me.mark.wanle = 1
		message_vision("[color=red]菜园管事说：干的不错，好了，你可以到大师兄鲁坤那里去覆命了！[/color]",null)
		return 1
	message_vision("[color=green]你用瓢从缸里舀起水，在菜地里浇起水来。[/color]",null)
	add_busy(5.0)
	me.mark.jiao += 1
	if me.force < 20 and rand_range(0,10) < 6 :
		message_vision("[color=yellow]你在浇水中对于内功的用法有些体会[/color]",null)
		me.force = me.force + int(me.Int/10)
		return 1
		
func notify_fail(message:String):
	$AcceptDialog.show()
	$AcceptDialog.dialog_text = message
	pass
	
func message_vision(message:String,null):
	$RichTextLabel.bbcode_enabled = true
	$RichTextLabel.bbcode_text = message
	pass	
	
func character_panel(me):
	var msg:String
	msg = """	名字:""" + me.name_cn + """
	手持:""" + me.weapon.name + """
	精力:""" + str(me.jingli) + """
	气血:""" + str(me.qi) + """
	内力:""" + str(me.force) + """
	臂力:""" + str(me.Str) + """
	悟性:""" + str(me.Int) + """
	体质:""" + str(me.Con) + """
	工作:""" + me.job_name
	return msg
	
func add_busy(time:float):
	yield(get_tree().create_timer(time),"timeout")
	
func _process(delta):
	$RichTextLabelCharacter.bbcode_text = character_panel(me)
	pass	

func _on_ActionButton01_pressed():
	do_jiao()
	pass # Replace with function body.


func _on_Door01_pressed():
	pass # Replace with function body.


func _on_Door08_pressed():
	current_room = neighbor_rooms["south"]
	$RoomName.bbcode_text = current_room.query("short")
	$NinePatchRect/Description.bbcode_text = current_room.query("long")
	creat_exits(current_room.query("exits"))
	pass # Replace with function body.


func _on_Door09_pressed():
	current_room = neighbor_rooms["out"]
	$RoomName.bbcode_text = current_room.query("short")
	$NinePatchRect/Description.bbcode_text = current_room.query("long")
	creat_exits(current_room.query("exits"))
	pass # Replace with function body.
