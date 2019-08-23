extends ProgressBar

func _ready():
	max_value = int(get_node("../../Label_max_tili/value").text)
	value = int(get_node("../../Label_tili/value").text)
	pass
