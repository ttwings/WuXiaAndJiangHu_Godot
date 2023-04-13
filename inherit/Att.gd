extends RefCounted

class_name Att

signal on_change(key,old_val)

var hp = -1: set = set_hp
var hp_max = 0: set = set_hp_max
var atk = 0: set = set_atk
var arm = 0: set = set_arm

func set_hp(val):
	hp = val
	
func set_hp_max(val):
	hp_max = val

func set_atk(val):
	atk = val
	
func set_arm(val):
	arm = val
