extends Node2D

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

# 1  2  3
# 4  5  6
# 7  8  9 
var neighbor_rooms = {}
func creat_exits(exits):
	var x
	var line = Line2D.new()
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
	$room.show()
	$room/RichTextLabel.bbcode_text = current_room.query("short")
	for direct in exits:
		if exits[direct] :
			match direct:
				"east" : 
					neighbor_rooms[direct] = load(exits[direct] + ".gd")
					$NinePatchRect2/GridContainer/Door04.text = "东"
					$NinePatchRect2/GridContainer/Door04.connect("pressed",self,"on_exit_pressed",[direct])
					$room_e.show()
#					$room_e/RichTextLabel.bbcode_text = neighbor_rooms[direct].query("short")
#					var line = Line2D.new()
					$room_e.add_child(line)
					line.width = 40
					line.points.append($room/Position2D.position)
					line.points.append($room_e/Position2D.position)
				"west":
					neighbor_rooms[direct] = load(exits[direct] + ".gd")
					$NinePatchRect2/GridContainer/Door06.text = "西"
					$NinePatchRect2/GridContainer/Door06.connect("pressed",self,"on_exit_pressed",[direct])
					$room_w.show()
#					$room_w/RichTextLabel.bbcode_text = neighbor_rooms[direct].query("short")
#					var line = Line2D.new()
					$room_w.add_child(line)
					line.width = 40
					line.points.append($room/Position2D.position)
					line.points.append($room_w/Position2D.position)
				"south":
					neighbor_rooms[direct] = load(exits[direct] + ".gd").new()
					$NinePatchRect2/GridContainer/Door08.text = "南"
					$NinePatchRect2/GridContainer/Door08.connect("pressed",self,"on_exit_pressed",[direct])
					$room_s.show()
					$room_s/RichTextLabel.bbcode_text = neighbor_rooms[direct].query("short")
					
					$room_s.add_child(line)
					line.show()
					line.width = 40
					line.points.append($room/Position2D.position)
					line.points.append($room_s/Position2D.position)
				"north":
					neighbor_rooms[direct] = load(exits[direct] + ".gd")
					$NinePatchRect2/GridContainer/Door02.text = "北"
					$NinePatchRect2/GridContainer/Door02.connect("pressed",self,"on_exit_pressed",[direct])
				"out":
					neighbor_rooms[direct] = load(exits[direct] + ".gd").new()
					$NinePatchRect2/GridContainer/Door09.text = "出去"
					$NinePatchRect2/GridContainer/Door09.connect("pressed",self,"on_exit_pressed",[direct])
					$room_out.show()
					$room_out/RichTextLabel.bbcode_text = neighbor_rooms[direct].query("short")
#					var line = Line2D.new()
					$room_out.add_child(line)
					line.width = 40
					line.points.append($room/Position2D.position)
					line.points.append($room_out/Position2D.position)
				"in":
					neighbor_rooms[direct] = load(exits[direct] + ".gd")
					$NinePatchRect2/GridContainer/Door05.text = exits[direct]
				x:
					neighbor_rooms[direct] = load(exits[direct] + ".gd")
					$NinePatchRect2/GridContainer/Door03.text = exits[direct]
		else:
			neighbor_rooms[direct] = null

func _ready():

	var dir = filename.get_base_dir()
	print(dir)
	creat_exits(current_room.query("exits"))
	$RoomName.bbcode_text = current_room.query("short")
	$NinePatchRect/Description.bbcode_text = current_room.query("long")
	pass
		
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
	
func _process(delta):
	$RichTextLabelCharacter.bbcode_text = character_panel(me)
	pass	

func on_exit_pressed(direct):
	print("test")
	if neighbor_rooms[direct] != null:
		print(neighbor_rooms[direct])
		current_room = neighbor_rooms[direct]
		$RoomName.bbcode_text = current_room.query("short")
		$NinePatchRect/Description.bbcode_text = current_room.query("long")
		creat_exits(current_room.query("exits"))
	pass # Replace with function body.