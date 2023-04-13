extends Control

#var jinshen_str = String.format("%5d/%5d",[100,100])

func _ready():
	$Panel/MarginContainer/RichTextLabel.text = """
	[color=#00ff00]=============================================================[/color]
	[精神] 100/100 [100%]
	[气血] 100/100 [100%]
	[食物] 150/100
	[饮水] 150/100
	[状态] [color=#00ff00]良好[/color]
	[color=#00ff00]=============================================================[/color]
	"""
