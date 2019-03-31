extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var number_label
var timer = 2

# Called when the node enters the scene tree for the first time.
func _ready():
	number_label = $Label
	pass # Replace with function body.

func start(obj,pos:Vector2):
	# 如果是伤害
	if obj is DmgObj:
		number_label.text = String(obj.dmg)
		#暴击伤害显示为红色
		if obj.isCrit:
			scale = Vector2(2,2)
			modulate = Color.red
		position = pos
		#特殊伤害显示为黄色
		if obj.type == 1 :
			scale = Vector2(1.5,1.5)
			modulate = Color.yellow
	# 如果是治疗
	if obj is HealObj :
		number_label.text = String(obj.heal)
		position = pos
		modulate = Color.green
	
func _process(delta):
	timer = timer - delta
	if timer <-0 :
		queue_free()
	position.y = position.y - 100 * delta
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
