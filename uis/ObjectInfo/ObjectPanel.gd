extends NinePatchRect

var player
var item
#
#func _ready() -> void:
#	TranslationServer.set_locale("zh_CN")
#	player = load("res://d/baihuagu/npc/zhou.gd").new()
##	player.creat_user("res://data/user/l/lijia.gd")
#	item = load("res://clone/food/apple.gd").new()
#	get_item_info(item)
#	connect_action(item,player)
	
func start(item):
	get_item_info(item)
	connect_action(item,null)	

var actions = {
	do_eat = "吃",
	do_drink = "喝",
	do_read = "读",
	do_look = "看",
}

func init_item_info():
	$Name.bbcode_text = ""
	$Type.bbcode_text = ""
	$Description.bbcode_text = ""

func get_item_info(item):
	init_item_info()
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
			button.text = tr(key)
			button.connect("pressed",item,key,[actor])	
			$HBoxContainer.add_child(button)

func _on_CloseButton_pressed():
	hide()
	pass # Replace with function body.
