extends Reference

class_name Trigger

# 指定角色
var actor
# 指定技能、buff、物品等
var item
# 事件
var event = ""
# 条件
func condition(eventArg):
	pass

func action(eventArg):
	pass
	
func start(actor,item):
	self.actor = actor
	self.item = item
	