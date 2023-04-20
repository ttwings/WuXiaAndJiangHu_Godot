extends Node

const ICON_PATH = "res://inventory/icons/"
const ITEMS = {
	"sword":{
		"icon":ICON_PATH + "sword.png",
		"slot":"MAIN_HAND"
	},
	"cloth" :{
		"icon":ICON_PATH + "cloth.png",
		"slot":"CHEST"
	},
	"potato":{
		"icon":ICON_PATH + "potato.png",
		"slot":"NONE"
	},
	"error":{
		"icon":ICON_PATH + "error.png",
		"slot":"NONE"
	}
}

func get_item(item_id):
	if item_id in ITEMS :
		return ITEMS[item_id]
	else:
		return ITEMS["error"]
		
		 