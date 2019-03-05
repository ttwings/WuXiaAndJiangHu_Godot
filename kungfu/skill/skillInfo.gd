extends GameObject

#export(Skill) var skill


var skill_gd = load("res://kungfu/skill/taiji-quan.gd")

func _ready():
	var skill = skill_gd.new()
	creat_bbcode(skill)

func creat_bbcode(skill:Skill):
#	var bbc = ""
#	var result1 = skill.name()
#	var result2 = skill.query("name")
#	bbc = result1 + result2
#	$NinePatchRect/RichTextLabel.bbcode_text = skill.help()
	skill.help()
	pass