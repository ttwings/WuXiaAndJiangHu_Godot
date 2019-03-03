extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var food = load("res://clone/food/apple.gd")
var apple = food.new()
# Called when the node enters the scene tree for the first time.
func _ready():
#	apple.create()
	print(apple.name())
	var test1 = """diyihang111
	"""
	var test2 = """dierhang222
	"""
	var test3 = """[br]disanhang333[br/]
	"""
	$Panel/NinePatchRect/RichTextLabel.bbcode_text = creat_food_bbc(apple)
#	$Panel/NinePatchRect/RichTextLabel.bbcode_text = test1 + test2 + test3
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func creat_food_bbc(food:Food):
	print(food.name())
	var dict = {}
	dict.name_cn = food.name()
	dict.direction = str(food.query("long"))
	dict.unit = food.query("unit")
	dict.food_remaining = food.query("food_remaining")
	dict.type = "食物"
	dict.pice = 1
	dict.pice_max = 5
	dict.food = food.query("food_supply")
	dict.water = -20
	dict.happy = 10
	dict.value = food.query("value")
	var bbc ="""[center][color=#ffff00]""" + dict.name_cn + """[/color][/center]
[color=gray]【描述】[/color]
	""" + dict.direction + """
[color=yellow]【物品信息】[/color]
	单位："""+ dict.unit +"""
	分量："""+ str(dict.food_remaining ) +"""
	类别："""+ dict.type + """
	分量：[color=red]""" + str(dict.pice) +"""[/color]/"""+ str(dict.pice_max) +"""
[color=fuchsia]【使用效果】[/color]
	果腹：[color="""+ get_number_color(dict.food) +"""]"""+ str(dict.food) +"""[/color]
	解渴：[color="""+ get_number_color(dict.water) +"""]"""+ str(dict.water) +"""[/color]
	享受：[color="""+ get_number_color(dict.happy) +"""]"""+ str(dict.happy) +"""[/color]
	[right][color=yellow]价钱："""+ get_chinese_number(dict.value) +"""钱[/color][/right]
	"""
	var result = []
	var result0 = """[center][color=#ffff00]""" + dict.name_cn + """[/color][/center]
	"""
	var result1 = """[color=gray]【描述】[/color]
	"""
	var result2 = food.query("long") + """
	"""
	var result3 = """[color=yellow]【物品信息】[/color]
	"""
	var result4 = """单位："""+ food.query("unit")
	var result5 = """
	价钱：""" + str(food.query("value"))
	var result6 = """
	分量："""+ str(dict.food_remaining )
	var result7 = """
	果腹：[color="""+ get_number_color(dict.food) +"""]"""+ str(dict.food) +"""[/color]"""
	var bbc1 = result0 + result1 + result2  + result3 + result4 + result5 + result6 + result7
	return bbc1

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