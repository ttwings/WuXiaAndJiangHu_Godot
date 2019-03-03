extends GameObject

#export(Skill) var skill


var skill = Skill.new()

func _ready():
	creat_bbcode(skill)

func creat_bbcode(skill:Skill):
#	var bbc = ""
#	var result1 = skill.name()
#	var result2 = skill.query("name")
#	bbc = result1 + result2
#	$NinePatchRect/RichTextLabel.bbcode_text = RED + "TEST" + NOR
	pass