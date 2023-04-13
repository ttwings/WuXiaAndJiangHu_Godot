extends Node2D
# const color -----------------------------------
const NOR = "[/color]"
const BLK = "[color=#000000]"
const RED = "[color=#ff0000]"
const GRN = "[color=#00ff00]"
const YEL = "[color=#ffff00]"
const BLU = "[color=#0000ff]"
const MAG = "[color=#ff00ff]"
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

var player_save_data = gdutils.utils.json.load_json("user://save/1/player.json")

var Room_gd
var current_room
var rooms = {}
var map_file = File.new()
# 1  2  3
# 4  5  6
# 7  8  9 
var neighbor_rooms = {}
# ------------------ test -------------------------
var food
var npc

func _ready():
	player.dbase = player_save_data.dbase
	
	# 初始房间. 等角色创建登录功能完成后.这里根据角色的home 属性,设置.
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
	$RoomPanel/VBoxContainer/RoomName.text = "[center]" + current_room.query("short") +"[/center]"
	$RoomPanel/VBoxContainer/Description.text  = current_room.query("long")
	# load map
	map_file.open("res://doc/map/changan",File.READ)
#	print(map_file.get_as_text())
	$RoomMessage/VBoxContainer/RichTextLabel.text = map_file.get_as_text()
#	current_room.get_dir()
	food = load("res://clone/food/apple.gd").new()

#	player = Player.new().creat_user("res://data/user/l/lijia.gd")
	player = Char.new()
	player.dbase = player_save_data.dbase
	player.carry_object("/clone/food/apple")

#	npc test 对话
	npc = load("res://d/baihuagu/npc/zhou.gd").new()
	creat_chat_panel(npc)
#  	链接房间按钮.
	pressed_connect()

# 信号链接一次就好
func pressed_connect():
	for direct in rooms:	
		rooms[direct].connect("pressed", Callable(self, "move_to_room").bind(direct))
# 生成出口
func creat_exits(room:GameObject,neighbor_rooms):
	var x
	var line = Line2D.new()
	var exits = room.query("exits")
	$Rooms/room.show()
	$Rooms/room/RichTextLabel.text = "[center]" + room.query("short") +"[/center]"
	for direct in exits:
		if exits[direct] :
			neighbor_room_creat(room,direct,neighbor_rooms)	
# 生成相邻房间			
func neighbor_room_creat(room,direct,neighbor_rooms):
#	print(exits[direct] + ".gd")
	var exits = room.query("exits")
	# neighbor_rooms[direct] = load(exits[direct] + ".gd").new()
	neighbor_rooms[direct] = Global.load_room(exits[direct] + ".gd")
	rooms[direct].show()
	rooms[direct].get_child(0).text = "[center]" + neighbor_rooms[direct].query("short") +"[/center]"
#	rooms[direct].get_child().(neighbor_rooms[direct].query("short"))
	pass			
# 房间之间的移动
func move_to_room(direct):
	current_room = neighbor_rooms[direct]
	neighbor_rooms = {}
	for i in rooms:
		rooms[i].hide()
	creat_exits(current_room,neighbor_rooms)
	$RoomPanel/VBoxContainer/RoomName.text = "[center]" + current_room.query("short") +"[/center]"
	$RoomPanel/VBoxContainer/Description.text = current_room.query("long")
#	生成房间固定物品 如牌子类
	create_room_items()
#	生成房间包含对象,如物品,人物等
	create_room_objects()
	pass
		
func creat_character_props(ob:Char):
	var props = []
	for k in ob.dbase:
		match k:
			"str":
#				props.append(GRN + "臂力:" + "[" + str(ob.query(k)) + "]" + NOR)
				props.append("臂力:" + str(ob.query(k)))
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
#			"food":
#				props.append("食物:" + str(ob.query(k)))
#			"water":
#				props.append("饮水:" + str(ob.query(k)))
#			"max_liquid":
#				props.append("容量:" + str(ob.query(k)))
#			"max_liquid":
#				props.append("容量:" + str(ob.query(k)))
			"liquid":
				var liquid = ob.query("liquid")
				for l in liquid:
					match l:
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
# 消息的接受与发送		
func notify_fail(message:String):
	$AcceptDialog.show()
	$AcceptDialog.dialog_text = message
	pass
	
func message_ob(msg,ob):
	$ObjectMessage/RichTextLabel.text = msg
	
	
func _process(delta):
#	$RichTextLabelCharacter.bbcode_text = character_panel(me)
#	player_status(player)
	pass	
# ----------------------------------------------------- 对话窗口 -------------------------------------
# 根据人物信息显示基本窗口
func creat_chat_panel(actor:Char):
	$ChatMessagePanel/ChatMessage/names.text = ""
	$ChatMessagePanel/ChatMessage/Description.text = ""
	$ChatMessagePanel/ChatMessage/Chat.text = ""
	$ChatMessagePanel.show()
#	print_debug("chat panel message")
	print_debug(actor.name())
	$ChatMessagePanel/ChatMessage/names.text = actor.query("nickname") + "\n"  + actor.name()+ "\n" + actor.query("title")
	$ChatMessagePanel/ChatMessage/Description.text = actor.query("long")
	
	creat_chat_inquiry_button(actor.query("inquiry"),actor)
	print_debug("chat panel message")
# 根据对话判断生成各种功能
# 深入判断看自己是否有了解到的内容.

func create_chat_inquiry(inquiry,key,ob):
#	var inquiry = actor.query("inquiry")
	
	if inquiry and inquiry.has(key):
		if inquiry[key] is String:
			$ChatMessagePanel/ChatMessage/Chat.text ="[" +  key  + "]\n" + inquiry[key]
		elif inquiry[key] is Array:
			$ChatMessagePanel/ChatMessage/Chat.text ="[" +  key  + "]\n" + inquiry_func(inquiry[key],ob)
			pass
#	else:
#		$ChatMessagePanel/ChatMessage/Chat.bbcode_text = ""
#		pass			

func creat_chat_inquiry_button(inquiry,ob=null):
	if inquiry and inquiry.size()>0 :
		for i in inquiry :
			var action_button = Button.new()
			action_button.text = i
			action_button.custom_minimum_size = Vector2(200,30)
			action_button.connect("pressed", Callable(self, "create_chat_inquiry").bind(inquiry,i,ob))
			$ChatMessagePanel/Actions.add_child(action_button)
	else:
		var actions = $ChatMessagePanel/Actions
		for each in actions.get_children():
			each.queue_free()	

func inquiry_func(array:Array,ob=null):
	if ! ob :
		ob = Global.this_player()
		
	var func_name = array[0]
	# var args = array[1]
	ob.call_func(func_name)
			
# -------------------------------------------------------------room 内物品互动 ------------		
# 根据房间信息生成互动物品
func create_room_items():
	var room = current_room
	var items = room.query("item_desc")
	if !items :
		for i in $RoomPanel/VBoxContainer/Items.get_child_count():
			var button = $RoomPanel/VBoxContainer/Items.get_child(0)
			$RoomPanel/VBoxContainer/Items.remove_child(button)
		return
	for i in items :
		var item_button = Button.new()
		item_button.text = i
		item_button.custom_minimum_size = Vector2(30,30)
		item_button.connect("pressed", Callable(self, "create_room_item_desc").bind(items,i))
		$RoomPanel/VBoxContainer/Items.add_child(item_button)		

func create_room_item_desc(items,key):
	if items and items.has(key):
		$RoomMessage/VBoxContainer/RichTextLabel.text ="[" +  key  + "]\n" + items[key]

# 生成房间内的 objects 

func create_room_objects():
	var room = current_room
	var objects = room.query("objects")
	if !objects :
		for i in $RoomPanel/Objects.get_child_count():
			var button = $RoomPanel/Objects.get_child(0)
			$RoomPanel/Objects.remove_child(button)
		return
	for o in objects :
		var obj_button = Button.new()
		print_debug(o + ".gd")
		var ob = load(o + ".gd").new()
		obj_button.text = ob.name()
		obj_button.custom_minimum_size = Vector2(30,30)
		obj_button.connect("pressed", Callable(self, "create_room_object_panel").bind(ob))
		$RoomPanel/Objects.add_child(obj_button)			

func create_room_object_panel(ob):
	# print_debug(ob.name())
#	ob as Char
#	var ob = load("res://d/changan/npc/feng.gd").new()
#	creat_chat_panel(ob)
	if ob is Char:
		creat_chat_panel(ob)
#	TODO all object except food use only 1 panel
#	elif ob is Food:
#		object_panel(ob)
#		object_panel(o)
#		creat_chat_panel(objects[o])
#	包裹ItemList 生成
func create_itemlist(ob:Char):
	var list = $CharacterPanel/PropContainer/ItemList
	var objs = ob.query_temp("objects")
	for ob in objs :
		var item_str = ""
		list.add(ob.name())


func _on_ChatClose_pressed():
	$ChatMessagePanel.hide()
	pass # Replace with function body.

#
#func _on_ActionButton1_pressed():
#	# food.do_eat(player)
#	var msg = food.do_eat(player)
#	var old_msg = $ObjectMessage/RichTextLabel.bbcode_text
#	# print_debug(old_msg)
#	object_panel(food)
#	var time = OS.get_datetime()
#	$ObjectMessage/RichTextLabel.bbcode_text =old_msg + "[%2d:%2d:%2d] " % [time.hour,time.minute,time.second] +  msg
#	pass # Replace with function body.


func _on_ObjectPanelButton_pressed():
	$ObjectPanel.hide()
	pass # Replace with function body.

#
#func _on_ItemList_item_selected(list):
#	var item = $CharacterPanel/PropContainer/ItemList.get_item_text(list)
#	var objs = player.query("objects")
#	print_debug(objs)
#	var ob
#	for o in objs:
#		ob = o
#	print_debug(ob)	
##	object_panel(ob)
#	$ObjectPanel.show()
	
	pass # Replace with function body.
# Replace with function body.
