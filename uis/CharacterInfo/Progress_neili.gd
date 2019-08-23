extends TextureProgress
var v

func _ready():
	v = int(get_node("../../Label_max_qi/value").text)
	max_value = v if v >0 else 1 
	value = int(get_node("../../Label_qi/value").text)
	pass
