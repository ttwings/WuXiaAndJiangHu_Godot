extends NinePatchRect

var player
var item
	
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
	$Name.text = ""
	$Type.text = ""
	$Description.text = ""

func get_item_info(item):
	init_item_info()
	$Name.text = item.query("name")
	$Type.text = str(item.query("type")) if item.query("type") else "物品"
	$Description.text = item.query("long")
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
			button.connect("pressed", Callable(item, key).bind(actor))	
			$HBoxContainer.add_child(button)

func _on_CloseButton_pressed():
	hide()
	pass # Replace with function body.
