extends TextureProgressBar
var v
@onready var player_data = get_node("../../../PanelAttribute").player_data
func _ready():
	v = int(get_node("../../Label_max_neili/value").text)
	max_value = v if v >0 else 1 
	value = int(get_node("../../Label_neili/value").text)
	get_node("../value").text = str(player_data.dbase["neili"])
	pass

func _process(delta: float) -> void:
	get_node("../value").text = str(player_data.dbase["neili"])

