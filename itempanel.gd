extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	$Panel/NinePatchRect/RichTextLabel.bbcode_text = creat_food_bbc()
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func creat_food_bbc():
	var dict = {}
	dict.name_cn = "大米饭"
	dict.direction = "一碗刚从锅里盛出来的大米饭，还冒着热气～～～"
	dict.unit = "碗"
	dict.number = "1"
	dict.type = "食物"
	dict.pice = 1
	dict.pice_max = 5
	dict.food = 50
	dict.water = -20
	dict.happy = 10
	dict.value = 2548
	var bbc ="""[center][color=#ffff00]""" + dict.name_cn + """[/color][/center]
[color=gray]【描述】[/color]
	""" + dict.direction + """
[color=yellow]【物品信息】[/color]
	单位："""+ dict.unit +"""
	数量："""+ str(dict.number) +"""
	类别："""+ dict.type + """
	分量：[color=red]""" + str(dict.pice) +"""[/color]/"""+ str(dict.pice_max) +"""
[color=fuchsia]【使用效果】[/color]
	果腹：[color="""+ get_number_color(dict.food) +"""]"""+ str(dict.food) +"""[/color]
	解渴：[color="""+ get_number_color(dict.water) +"""]"""+ str(dict.water) +"""[/color]
	享受：[color="""+ get_number_color(dict.happy) +"""]"""+ str(dict.happy) +"""[/color]
	[right][color=yellow]价钱："""+ get_chinese_number(dict.value) +"""文[/color][/right]
	"""
	return bbc

func get_number_color(number):
 	if number < 0: return "red" 
 	else:return "green"
	
func get_chinese_number(n:int):
	var number_str = str(n)
	var l = number_str.length()
	var output = []
	for i in range(l):
		number_str[i] = swap_to_font(number_str[i])
	return number_str
		
func swap_to_font(number):
	match number:
		"1":return "一"
		"2":return "二"
		"3":return "三"
		"4":return "四"
		"5":return "五"
		"6":return "六"
		"7":return "七"
		"8":return "八"
		"9":return "九"
		"0":return "〇"
		_:return "X"