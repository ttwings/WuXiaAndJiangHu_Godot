extends RefCounted
class_name HealObj

var from = null
var to = null
var heal = 0

func _init(dict = null):
	if dict == null :
		return
	var keys = dict.keys()
	for key in keys :
		set(key,dict[key])

