extends Node2D
# const color -----------------------------------
const NOR = "[/color]"
const BLK = "[color=#000000]"
const RED = "[color=#ff0000]"
const GRN = "[color=#00ff00]"
const YEL = "[color=#ffff00]"
const BLU = "[color=#0000ff]"
const MAG = "[color=#ff0.0ff]"
const CYN = "[color=#00ffff]"
const WHT = "[color=#ffffff]"   
const HIR = "[color=#ff0000]"
const HIG = "[color=#00ff00]"
const HIY = "[color=#ffff00]"
const HIB = "[color=#44cef6]"
const HIM = "[color=#ff00ff]"
const HIC = "[color=#177cb0]"
const HIW = "[color=#e9e7ef]"
const BRED = "[color=#ff2121]"
const BGRN = "[color=#00e500]"
const BYEL = "[color=#ffb61e]"
const BBLU = "[color=#4b5cc4]"
const BMAG = "[color=#8d4bbb]"
const BCYN = "[color=#1685a9]"
const HBRED = "[color=#ff2121]"
const HBGRN = "[color=#40de5a]"
const HBYEL = "[color=#eacd76]"
const HBBLU = "[color=#3b2e7e]"
const HBMAG = "[color=#815463]"
const HBCYN = "[color=#00e09e]"
const HBWHT = "[color=#f0fcff]"


var player = Char.new()
var Room_gd
var current_room
var rooms = {}
var map_file = File.new()
# 1  2  3
# 4  5  6
# 7  8  9 
var neighbor_rooms = {}
var food

func _ready():
	current_room = Global.load_room("res://d/changan/shuyuan.gd")
	# 不同方向的房间房间太多,后期考虑精简. up 与 north  west up 和 north west等.
	rooms.current = $Rooms/room
	rooms.north = $Rooms/room_n
	rooms.south = $Rooms/room_s
	rooms.west = $Rooms/room_w
	rooms.east = $Rooms/room_e
	rooms.out = $Rooms/room_out
	rooms.in = $Rooms/room_in
	rooms.enter = $Rooms/room_enter
	rooms.westup = $Rooms/room_wu
	rooms.southwest = $Rooms/room_sw
	rooms.westdown = $Rooms/room_wd
	rooms.northwest = $Rooms/room_nw
	rooms.eastup = $Rooms/room_eu
	rooms.northeast = $Rooms/room_ne
	rooms.eastdown = $Rooms/room_ed
	rooms.southeast = $Rooms/room_se
	rooms.up = $Rooms/room_u
	rooms.down  = $Rooms/room_d
	
	creat_exits(current_room,neighbor_rooms)
	$RoomPanel/VBoxContainer/RoomName.bbcode_text = "[center]" + current_room.query("short") +"[/center]"
	$RoomPanel/VBoxContainer/Description.bbcode_text  = current_room.query("long")
	# load map
	map_file.open("res://doc/map/changan",File.READ)
#	print(map_file.get_as_text())
	$RoomMessage/VBoxContainer/RichTextLabel.bbcode_text = map_file.get_as_text()
#	current_room.get_dir()
	food = load("res://clone/food/apple.gd").new()
	object_panel(food)
	player = Global.this_player()
	# print_debug(player is GameObject)
	player.carry_object("/clone/food/apple")
#	print_debug(player.dbase["objects"])
	print_debug(player.objects)
	character_panel(player)
	pressed_connect()

# 信号链接一次就好
func pressed_connect():
	for direct in rooms:	
		rooms[direct].connect("pressed",self,"move_to_room",[direct])

func creat_exits(room:GameObject,neighbor_rooms):
	var x
	var line = Line2D.new()
	var exits = room.query("exits")
	$Rooms/room.show()
	$Rooms/room/RichTextLabel.bbcode_text = "[center]" + room.query("short") +"[/center]"
	for direct in exits:
		if exits[direct] :
			neighbor_room_creat(room,direct,neighbor_rooms)	
			
func neighbor_room_creat(room,direct,neighbor_rooms):
#	print(exits[direct] + ".gd")
	var exits = room.query("exits")
	# neighbor_rooms[direct] = load(exits[direct] + ".gd").new()
	neighbor_rooms[direct] = Global.load_room(exits[direct] + ".gd")
	rooms[direct].show()
	rooms[direct].get_child(0).bbcode_text = "[center]" + neighbor_rooms[direct].query("short") +"[/center]"
#	rooms[direct].get_child().(neighbor_rooms[direct].query("short"))
	pass			

func move_to_room(direct):
	current_room = neighbor_rooms[direct]
	neighbor_rooms = {}
	for i in rooms:
		rooms[i].hide()
	creat_exits(current_room,neighbor_rooms)
	$RoomPanel/VBoxContainer/RoomName.bbcode_text = "[center]" + current_room.query("short") +"[/center]"
	$RoomPanel/VBoxContainer/Description.bbcode_text = current_room.query("long")
	pass

		
func notify_fail(message:String):
	$AcceptDialog.show()
	$AcceptDialog.dialog_text = message
	pass
	
func message_ob(msg,ob):
	$ObjectMessage/RichTextLabel.bbcode_text = msg
#  object panel 	
func object_panel(ob:GameObject):
#		$ObjectRect.show()
		$ObjectRect/Name.bbcode_text = ob.query("name")
		$ObjectRect/Type.text = ob.query("type")
		$ObjectRect/Description.bbcode_text = ob.query("long")
		var props = []
		var prop_nodes = []
		prop_nodes.append($ObjectRect/GridContainer/Prop1)
		prop_nodes.append($ObjectRect/GridContainer/Prop2)
		prop_nodes.append($ObjectRect/GridContainer/Prop3)
		prop_nodes.append($ObjectRect/GridContainer/Prop4)
		prop_nodes.append($ObjectRect/GridContainer/Prop5)
		prop_nodes.append($ObjectRect/GridContainer/Prop6)
		prop_nodes.append($ObjectRect/GridContainer/Prop7)
		prop_nodes.append($ObjectRect/GridContainer/Prop8)
		
		props = creat_props(ob)
		for i in props.size() :
#			if props[i]:
#			var path = "ObjectRect/GridContainer/Prop" + str(1)
			prop_nodes[i].show()
			prop_nodes[i].text = props[i]
	
func creat_props(ob:GameObject):
	var props = []
	for k in ob.dbase:
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
			$CharacterPanel/PropContainer/HBoxContainer/VBoxContainer/Nackname.bbcode_text = ob.query("name")
			$CharacterPanel/PropContainer/HBoxContainer/VBoxContainer/Title.text = ob.query("titile")
			$CharacterPanel/PropContainer/HBoxContainer/VBoxContainer/Nackname.text = ob.query("nackname")
#			$CharacterRect/Description.bbcode_text = ob.query("long")
			var props = []
			var prop_nodes = []
			prop_nodes.append($CharacterPanel/PropContainer/GridContainer/Prop1)
			prop_nodes.append($CharacterPanel/PropContainer/GridContainer/Prop2)
			prop_nodes.append($CharacterPanel/PropContainer/GridContainer/Prop3)
			prop_nodes.append($CharacterPanel/PropContainer/GridContainer/Prop4)
			prop_nodes.append($CharacterPanel/PropContainer/GridContainer/Prop5)
			prop_nodes.append($CharacterPanel/PropContainer/GridContainer/Prop6)
			prop_nodes.append($CharacterPanel/PropContainer/GridContainer/Prop7)
			prop_nodes.append($CharacterPanel/PropContainer/GridContainer/Prop8)
#
			props = creat_character_props(ob)
			for i in props.size() :
	#			if props[i]:
	#			var path = "CharacterRect/GridContainer/Prop" + str(1)
				prop_nodes[i].show()
				prop_nodes[i].bbcode_text = props[i]
		
func creat_character_props(ob:GameObject):
	var props = []
	for k in ob.dbase:
		match k:
			"str":
				props.append(GRN + "臂力:" + "[" + str(ob.query(k)) + "]" + NOR)
			"int":
				props.append("悟性:" + str(ob.query(k)))
			"con":
				props.append("体质:" + str(ob.query(k)))
			"dex":
				props.append("身法:" + str(ob.query(k)))
			"per":
				props.append("容貌:" + str(ob.query(k)))
			"cps":
				props.append("福源:" + str(ob.query(k)))
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

#------------------------------------- signl	

func _process(delta):
#	$RichTextLabelCharacter.bbcode_text = character_panel(me)
	player_status(player)
	pass	

func player_status(player):
	var qi = player.query("qi")
	var max_qi = player.query("max_qi")
	var jing = player.query("jing")
	var max_jing = player.query("max_jing")
	var neili = player.query("neili")
	var max_neili = player.query("max_neili")
	$ActorStatus/VBoxContainer/Qibox/ProgressBar.value = int(qi)
	$ActorStatus/VBoxContainer/Qibox/ProgressBar.max_value = max_qi
	$ActorStatus/VBoxContainer/Qibox/Label2.text = "[" + str(qi) + "/" + str(max_qi) + "]"
	$ActorStatus/VBoxContainer/Jingbox/ProgressBar.value  = jing
	$ActorStatus/VBoxContainer/Jingbox/ProgressBar.max_value  = max_jing
	$ActorStatus/VBoxContainer/Jingbox/Label2.text  = "[" + str(jing) + "/" + str(max_jing) + "]"
	$ActorStatus/VBoxContainer/Neibox/ProgressBar.value = neili
	$ActorStatus/VBoxContainer/Neibox/ProgressBar.max_value = max_neili
	$ActorStatus/VBoxContainer/Neibox/Label2.text  = "[" + str(neili) + "/" + str(max_neili) + "]"
	$ActorStatus/VBoxContainer/FoodBox/ProgressBar.value = player.query("food")
	$ActorStatus/VBoxContainer/WaterBox/ProgressBar.value = player.query("water")

var player_objects = {}
func init_player_objects(player):
	var objects = player.query("objects")
	for ob in objects:
		player_objects[ob] = player.carry_object(objects[ob])
	


func _on_ChatClose_pressed():
	$ChatMessagePanel.hide()
	pass # Replace with function body.


func _on_ActionButton1_pressed():
	# food.do_eat(player)
	var msg = food.do_eat(player)
	var old_msg = $ObjectMessage/RichTextLabel.bbcode_text
	# print_debug(old_msg)
	object_panel(food)
	var time = OS.get_datetime()
	$ObjectMessage/RichTextLabel.bbcode_text =old_msg + "[%2d:%2d:%2d] " % [time.hour,time.minute,time.second] +  msg
	pass # Replace with function body.


func _on_ObjectRectButton_pressed():
	$ObjectRect.hide()
	pass # Replace with function body.


func _on_ItemList_item_selected(list):
	var item = $CharacterPanel/PropContainer/ItemList.get_item_text(list)
	var objs = player.objects
	var ob
	for o in objs:
		ob = load(o).new()
	print_debug(ob)	
	object_panel(ob)
	$ObjectRect.show()
	
	pass # Replace with function body.
# Replace with function body.