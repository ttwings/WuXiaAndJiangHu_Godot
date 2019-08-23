extends ProgressBar

func _ready():
	max_value = int(get_node("../../Label_max_qi/value").text)
	value = int(get_node("../../Label_qi/value").text)
	pass
