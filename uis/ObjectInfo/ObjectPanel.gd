extends NinePatchRect

var player
var item

func _ready() -> void:
	TranslationServer.set_locale("en")
	player = load("res://d/baihuagu/npc/zhou.gd").new()
#	player.creat_user("res://data/user/l/lijia.gd")
	item = load("res://clone/food/apple.gd").new()
	get_item_info(item)
	connect_action(item,player)
	
func start(item):
	get_item_info(item)
#	connect_action(item)	

var actions = {
	do_eat = "吃",
	do_drink = "喝",
	do_read = "读",
	do_look = "看",
}

var classes = {
	Food = "食物",
	
}

var translates = {
	unit = "单位",
	value = "价格",
	food_remaining = "份数",
	food_supply = "饱腹"
}

func get_item_info(item):
	$Name.bbcode_text = item.query("name")
	$Type.bbcode_text = str(item.query("type")) if item.query("type") else "物品"
	$Description.bbcode_text = item.query("long")
#	var label = Label.new()
	for key in item.dbase :
#		print(key)
#		var label = Label.new()
		match key:
			"unit","value","food_remaining","food_supply":
				var label = Label.new()
				label.text = tr(key) + ":" + str(item.dbase[key])
				$GridContainer.add_child(label)
	
func connect_action(item,actor):
	for key in actions :
		if item.has_method(key):
			var button = Button.new()
			button.text = actions[key]
			button.connect("pressed",item,key,[actor])	
			$HBoxContainer.add_child(button)

func _on_CloseButton_pressed():
	hide()
	pass # Replace with function body.
