extends Reference
class_name Item
signal number_change

var type = 0
var name_cn = ""
var owner
var property = {}
var trigger_list = []
var description = ""
var cost = 0
var cd = 10
var cd_timer  = 0
var number = 1 setget set_number
var is_consume = false
var will_disappear = false
var is_show_number = false

var can_battle_use = true
var can_map_use = true

func set_number(value:int):
	number = value
	emit_signal("number_change")
	
func use():
	pass
	
func start():
	self.owner = owner
	for trigger in trigger_list :
		trigger.start(owner,self)	
