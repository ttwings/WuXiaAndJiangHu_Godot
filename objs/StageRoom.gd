extends Node2D

# Preload custom control scripts (avoids class_name resolution issues)
const ActionPanel = preload("res://controls/ActionPanel.gd")
const ActionButton = preload("res://controls/ActionButton.gd")

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

var player_save_data = _load_player_save()

func _load_player_save():
	var path = "user://save/1/player.json"
	if FileAccess.file_exists(path):
		var f = FileAccess.open(path, FileAccess.READ)
		if f:
			var data = JSON.parse_string(f.get_as_text())
			f.close()
			if data and data.has("dbase"):
				return data
	# 默认玩家数据
	return {
		"dbase": {
			"name": "玩家",
			"id": "player",
			"str": 20, "int": 20, "con": 20, "dex": 20,
			"per": 20, "cps": 20, "cor": 20, "kar": 20, "spi": 20, "sta": 20, "obe": 20,
			"qi": 100, "max_qi": 100, "eff_qi": 100,
			"jing": 100, "max_jing": 100, "eff_jing": 100,
			"neili": 0, "max_neili": 100,
			"jingli": 0, "max_jingli": 100,
			"combat_exp": 1000,
			"potential": 0, "learned_points": 0,
			"shen": 0, "score": 0,
			"food": 100, "water": 100,
			"limbs": ["头部", "胸口", "左臂", "右臂", "左腿", "右腿"],
		}
	}

var Room_gd
var current_room
var rooms = {}
var map_file: FileAccess
# 1  2  3
# 4  5  6
# 7  8  9 
var neighbor_rooms = {}
# ------------------ test -------------------------
var food
var npc

# 心跳计时
var _heartbeat_timer = 0.0
const HEARTBEAT_INTERVAL = 1.0

func _ready():
	player.dbase = player_save_data.dbase
	player.set_temp("environment", null)
	# 连接玩家消息信号
	player.message_sent.connect(_on_player_message)
	# 初始化玩家技能
	player.set_skill("unarmed", 10)
	player.set_skill("dodge", 10)
	player.set_skill("parry", 10)
	player.set_skill("force", 10)
	player.set_skill("literate", 5)
	
	# 初始房间. 等角色创建登录功能完成后.这里根据角色的home 属性,设置.
	current_room = Global.load_room("res://d/changan/shuyuan.gd")
	player.set_temp("environment", current_room)
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
	if FileAccess.file_exists("res://doc/map/changan"):
		map_file = FileAccess.open("res://doc/map/changan", FileAccess.READ)
		if map_file:
			$RoomMessage/VBoxContainer/RichTextLabel.text = map_file.get_as_text()

	# 初始化房间对象
	create_room_objects()

	player.carry_object("/clone/food/apple")

	# npc test 对话
	npc = _create_npc()
	if npc:
		npc.message_sent.connect(_on_npc_message)
		creat_chat_panel(npc)
		# 把 npc 放入房间对象列表
		current_room.set_temp("objects", [npc])

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
	# 更新玩家环境
	player.set_temp("environment", current_room)
	player.remove_all_enemy()
#	生成房间固定物品 如牌子类
	create_room_items()
#	生成房间包含对象,如物品,人物等
	create_room_objects()
	# 显示房间信息
	player.message_sent.emit("你来到了" + str(current_room.query("short")) + "。\n")
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
	# 心跳循环：定期调用角色的 heart_beat
	_heartbeat_timer += delta
	if _heartbeat_timer >= HEARTBEAT_INTERVAL:
		_heartbeat_timer = 0.0
		# 玩家心跳
		if player.query_temp("heart_beat"):
			player.heart_beat()
		# NPC 心跳
		if npc and is_instance_valid(npc) and npc.query_temp("heart_beat"):
			npc.heart_beat()

# ----------------------------------------------------- 消息处理 -------------------------------------
func _on_player_message(msg: String):
	var old = $ObjectMessage/RichTextLabel.text
	$ObjectMessage/RichTextLabel.text = old + msg

func _on_npc_message(msg: String):
	var old = $ObjectMessage/RichTextLabel.text
	$ObjectMessage/RichTextLabel.text = old + msg

# ----------------------------------------------------- NPC 创建 -------------------------------------
func _create_npc():
	# 尝试加载测试 NPC，失败则创建默认 NPC
	var npc_path = "res://d/baihuagu/npc/zhou.gd"
	if ResourceLoader.exists(npc_path):
		var n = load(npc_path).new()
		return n
	# 默认 NPC
	var n = Npc.new()
	n.set_attr("name", "周伯通")
	n.set_attr("id", "zhou")
	n.set_attr("str", 30)
	n.set_attr("int", 25)
	n.set_attr("con", 30)
	n.set_attr("dex", 30)
	n.set_attr("qi", 200)
	n.set_attr("max_qi", 200)
	n.set_attr("eff_qi", 200)
	n.set_attr("jing", 200)
	n.set_attr("max_jing", 200)
	n.set_attr("eff_jing", 200)
	n.set_attr("combat_exp", 5000)
	n.set_attr("limbs", ["头部", "胸口", "左臂", "右臂", "左腿", "右腿"])
	n.set_skill("unarmed", 30)
	n.set_skill("dodge", 30)
	n.set_skill("parry", 30)
	n.set_temp("environment", current_room)
	return n
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
	# 清空旧按钮
	for child in $RoomPanel/Objects.get_children():
		child.queue_free()
	if !objects:
		return
	# 实例化房间对象并存入 temp
	var ob_list = []
	for o in objects:
		var path = o
		if not path.ends_with(".gd"):
			path = o + ".gd"
		if ResourceLoader.exists(path):
			var ob = load(path).new()
			ob.set_temp("environment", room)
			ob_list.append(ob)
	room.set_temp("objects", ob_list)
	# 生成按钮
	for ob in ob_list:
		var obj_button = Button.new()
		obj_button.text = ob.name()
		obj_button.custom_minimum_size = Vector2(120, 30)
		obj_button.connect("pressed", Callable(self, "create_room_object_panel").bind(ob))
		$RoomPanel/Objects.add_child(obj_button)

func create_room_object_panel(ob):
	if ob is Char:
		creat_chat_panel(ob)
	# 为对象创建动作面板（ActionPanel）
	_show_action_panel(ob)

func _show_action_panel(ob):
	# 使用 ObjectPanel 作为动作面板容器
	var panel = $ObjectPanel
	if panel == null:
		return
	for child in panel.get_children():
		child.queue_free()
	if ob == null:
		panel.hide()
		return
	panel.show()
	# 使用 ActionPanel 生成上下文按钮
	var action_panel = ActionPanel.new()
	action_panel.setup(player, ob)
	panel.add_child(action_panel)
#	包裹ItemList 生成
func create_itemlist(ob:Char):
	var list = $CharacterPanel/PropContainer/ItemList
	var objs = ob.query_temp("objects")
	for item in objs :
		var item_str = ""
		list.add(item.name())


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
