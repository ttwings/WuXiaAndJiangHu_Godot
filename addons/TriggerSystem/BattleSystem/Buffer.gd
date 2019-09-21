extends Reference

class_name Buffer

signal property_change
signal number_change

var property:Dictionary = {}
var name_cn = ""
var target
var trigger_list = []
var life = 3
var descrption = ""
var is_show = true
# 叠加类型分为 single,cover,increase
var add_type = "single"
var number = 1 setget set_number
var number_max = 5
func set_number(value:int):
	number = value
	number_change()
	emit_signal("number_change")

# 重写用，当层数变更时要做的事情
func number_change():
	pass
	
# 附加到目标上
func start(target):
	self.target = target
	# 把触发器添加到触发器系统
	for trigger in trigger_list :
		trigger.start(target,self)
		TriggerSystem.appendTrigger(trigger)
	
	# 结束buff，把触发器从触发器系统中移除

func end():
	for trigger in trigger_list :
		TriggerSystem.removeTrigger(trigger)
				
func set_property(pr:String,value):
	property[pr] = value
	emit_signal("property_change")
	
func increase_property(pr:String,value):
	if !property.has(pr):
		property[pr] = 0
	set_property(pr,property[pr] + value)	