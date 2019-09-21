extends Reference

class_name Skill

var lv = 1
var type = 0
var name_cn = ""
var owner
var property_list =[{},{},{}]
var property setget ,get_property
var trigger_list_list = [[],[],[]]
var trigger_list setget ,get_trigger_list
var description_list = ["","",""]
var description setget ,get_description
var cost_list = [60,60,60]
var cost setget ,get_cost
var cd_list = [10,10,10]
var cd setget ,get_cd
var cd_timer = 0

func get_property():
	return property_list[lv - 1]
	
func get_cost():
	return cost_list[lv - 1]
	
func get_cd():
	return cd_list[lv - 1]

func get_trigger_list():
	return trigger_list_list[lv - 1]
	
func get_description():
	return description
	
func use():
	pass
	
func start(owner):
	self.owner = owner
	# 初始化触发器变量，不会把触发器添加到触发器系统
	for trigger in get_trigger_list() :
		trigger.start(owner,self)	