extends Panel

onready var slots = get_children()
var items = {}

func _ready() -> void:
	for slot in slots:
		items[slot.name] = null
		
func insert_item(item):
	var item_pos = item.rect_global_position + item.rect_size/2
	var slot = get_slot_under_pos(item_pos)
	if slot == null:
		return false
		
	var item_slot = ItemDB.get_item(item.get_meta("id"))["slot"]	
	if item_slot != slot.name:
		return false
	if items[item_slot] != null:
		return false
	items[item_slot] = item
	item.rect_global_position = slot.rect_global_position + slot.rect_size / 2 - item.rect_size / 2
	return true
	
func grab_item(pos): 
	var item = get_item_under_pos(pos)
	if item == null:
		return
	
	var item_slot = ItemDB.get_item(item.get_meta("id"))["slot"]
	items[item_slot] = null
	return item
	
	
	
func get_slot_under_pos(pos):
	return get_thing_under_pos(slots,pos)

func get_item_under_pos(pos):
	return get_thing_under_pos(items.values(),pos)
	
func get_thing_under_pos(arr,pos):
	for thing in arr:
		if thing != null and thing.get_global_rect().has_point(pos):
			return thing		
	return null			
		