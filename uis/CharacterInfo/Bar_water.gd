extends TextureProgressBar
var v
var max_water
@onready var player_data = get_node("../../../PanelAttribute").player_data
var dbase
func _ready():
	# 食物的计算方法与其他的不同
#	v = int(get_node("../../Label_max_food/value").text)
	dbase = player_data.dbase
	max_water = dbase["int"]*5 + 300
	max_value = max_water
	value = int(get_node("../../Label_water/value").text)
	get_node("../value").text = str(player_data.dbase["water"])
	pass
