extends Reference
class_name DmgObj

var from = null
var to = null
var dmg = 0
var isCrit = false
var canCrit = false
var critBaseDmg = 0
var critPower = 1
var type = 1
var rebound = true
var canDodge = false
var isDodge = false
var isNormalAttack = false

func _init(dict = null):
	if dict == null :
		return
	var keys = dict.keys()
	for key in keys :
		set(key,dict[key])

func _ready():
	pass # Replace with function body.
