extends ProgressBar

func _ready():
	max_value = int(get_node("../../Label_max_jing/value").text)
	value = int(get_node("../../Label_jing/value").text)
	pass
