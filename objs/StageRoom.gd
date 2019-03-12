extends Node2D

# person

var player = Char.new()
# Called when the node enters the scene tree for the first time.

var Room_gd = load("res://d/baihuagu/baihuagu.gd")
var current_room = Room_gd.new()
var rooms = {}
var map_file = File.new()
# 1  2  3
# 4  5  6
# 7  8  9 
var neighbor_rooms = {}
func creat_exits(room:GameObject,neighbor_rooms):
	var x
	var line = Line2D.new()
	var exits = room.query("exits")
#	neighbor_rooms = {}
	$room.show()
	$room/RichTextLabel.bbcode_text = "[center]" + room.query("short") +"[/center]"
	for direct in exits:
		if exits[direct] :
			neighbor_room_creat(room,direct,neighbor_rooms)	
			# match direct:
			# 	var new_dir:
			# 		print_debug("new dir")
			# 		neighbor_room_creat(room,new_dir,neighbor_rooms)	
#		else:
#			neighbor_rooms[direct] = null
#			rooms[direct].hide()
			
func neighbor_room_creat(room,direct,neighbor_rooms):
#	print(exits[direct] + ".gd")
	var exits = room.query("exits")
	neighbor_rooms[direct] = load("res:/" + exits[direct] + ".gd").new()
	rooms[direct].show()
	rooms[direct].connect("pressed",self,"move_to_room",[direct])
	rooms[direct].get_child(0).bbcode_text = "[center]" + neighbor_rooms[direct].query("short") +"[/center]"
#	rooms[direct].get_child().(neighbor_rooms[direct].query("short"))
	pass			

func move_to_room(direct):
	current_room = neighbor_rooms[direct]
	neighbor_rooms = {}
	for i in rooms:
		rooms[i].hide()
	creat_exits(current_room,neighbor_rooms)
	$RoomName.bbcode_text = "[center]" + current_room.query("short") +"[/center]"
	$NinePatchRect/Description.bbcode_text = current_room.query("long")
	pass

func _ready():
	rooms.current = $room
	rooms.north = $room_n
	rooms.south = $room_s
	rooms.west = $room_w
	rooms.east = $room_e
	rooms.out = $room_out
	rooms.in = $room_in
	rooms.enter = $room_enter
	rooms.westup = $room_wu
	rooms.westdown = $room_wd
	rooms.eastup = $room_eu
	rooms.eastdown = $room_ed
	creat_exits(current_room,neighbor_rooms)
	$RoomName.bbcode_text = "[center]" + current_room.query("short") +"[/center]"
	$NinePatchRect/Description.bbcode_text = current_room.query("long")
	# load map
	map_file.open("res://doc/map/baihuagu",File.READ)
#	print(map_file.get_as_text())
	$RichTextLabelCharacter.bbcode_text = map_file.get_as_text()
	current_room.get_dir()
	object_panel(load("res://clone/food/baijiu.gd").new())
	var user = load("res://data/user/l/lijia.gd").new()
	player = Global.creat_user(user.dbase)
	for i in player.attributes :
		print_debug(i + ":" + str(player.attributes[i]))
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

	
#  object panel 	
func object_panel(ob:GameObject):
#		$ObjcetRect.show()
		$ObjcetRect/Name.bbcode_text = ob.query("name")
		$ObjcetRect/Type.text = ob.query("type")
		$ObjcetRect/Description.bbcode_text = ob.query("long")
		var props = []
		var prop_nodes = []
		prop_nodes.append($ObjcetRect/GridContainer/Prop1)
		prop_nodes.append($ObjcetRect/GridContainer/Prop2)
		prop_nodes.append($ObjcetRect/GridContainer/Prop3)
		prop_nodes.append($ObjcetRect/GridContainer/Prop4)
		prop_nodes.append($ObjcetRect/GridContainer/Prop5)
		prop_nodes.append($ObjcetRect/GridContainer/Prop6)
		prop_nodes.append($ObjcetRect/GridContainer/Prop7)
		prop_nodes.append($ObjcetRect/GridContainer/Prop8)
		
		props = creat_props(ob)
		for i in props.size() :
#			if props[i]:
#			var path = "ObjcetRect/GridContainer/Prop" + str(1)
			prop_nodes[i].show()
			prop_nodes[i].text = props[i]
	
func creat_props(ob:GameObject):
	var props = []
	for k in ob.attributes:
		match k:
			"unit":
				props.append("单位:" + ob.query(k))
			"value":
				props.append("价值:" + str(ob.query(k)))
			"material":
				props.append("材质:" + ob.query(k))
			"food_remaining":
				props.append("分量:" + str(ob.query(k)))
			"food_supply":
				props.append("饱腹:" + str(ob.query(k)))
			"water_supply":
				props.append("解渴:" + str(ob.query(k)))
			"max_liquid":
				props.append("容量:" + str(ob.query(k)))
			"liquid":
				var liquid = ob.query("liquid")
				for k in liquid:
					match k:
						"name":
							props.append("盛装:" + str(liquid.name))
						"remaining":
							props.append("分量:" + str(liquid.remaining))
						"drunk_supply":
							props.append("饮酒:" + str(liquid.drunk_supply))
						"water_supply":
							props.append("解渴:" + str(liquid.water_supply))
	return props
	

# cha panel

func character_panel(ob:GameObject):
	#		$CharacterRect.show()
			$CharacterRect/Name.bbcode_text = ob.query("name")
			$CharacterRect/Title.text = ob.query("titile")
			$CharacterRect/Description.bbcode_text = ob.query("long")
			var props = []
			var prop_nodes = []
			prop_nodes.append($CharacterRect/GridContainer/Prop1)
			prop_nodes.append($CharacterRect/GridContainer/Prop2)
			prop_nodes.append($CharacterRect/GridContainer/Prop3)
			prop_nodes.append($CharacterRect/GridContainer/Prop4)
			prop_nodes.append($CharacterRect/GridContainer/Prop5)
			prop_nodes.append($CharacterRect/GridContainer/Prop6)
			prop_nodes.append($CharacterRect/GridContainer/Prop7)
			prop_nodes.append($CharacterRect/GridContainer/Prop8)
			
			props = creat_character_props(ob)
			for i in props.size() :
	#			if props[i]:
	#			var path = "CharacterRect/GridContainer/Prop" + str(1)
				prop_nodes[i].show()
				prop_nodes[i].text = props[i]
		
	func creat_character_props(ob:GameObject):
		var props = []
		for k in ob.attributes:
			match k:
				"unit":
					props.append("单位:" + ob.query(k))
				"value":
					props.append("价值:" + str(ob.query(k)))
				"material":
					props.append("材质:" + ob.query(k))
				"food_remaining":
					props.append("分量:" + str(ob.query(k)))
				"food_supply":
					props.append("饱腹:" + str(ob.query(k)))
				"water_supply":
					props.append("解渴:" + str(ob.query(k)))
				"max_liquid":
					props.append("容量:" + str(ob.query(k)))
				"liquid":
					var liquid = ob.query("liquid")
					for k in liquid:
						match k:
							"name":
								props.append("盛装:" + str(liquid.name))
							"remaining":
								props.append("分量:" + str(liquid.remaining))
							"drunk_supply":
								props.append("饮酒:" + str(liquid.drunk_supply))
							"water_supply":
								props.append("解渴:" + str(liquid.water_supply))
		return props


func _process(delta):
#	$RichTextLabelCharacter.bbcode_text = character_panel(me)
	pass	