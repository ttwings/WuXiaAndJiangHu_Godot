#	skill.c
#
# 	This is the standard skill daemon object. All objects defining a skill
#	should inherit this as its skeleton.

# inherit F_CLEAN_UP;
extends Reference
class_name Skill

# const color -----------------------------------
const NOR = "[/color]"
const BLK = "[color=#000000]"
const RED = "[color=#ff0000]"
const GRN = "[color=#00ff00]"
const YEL = "[color=#ffff00]"
const BLU = "[color=#0000ff]"
const MAG = "[color=#ff0.0ff]"
const CYN = "[color=#00ffff]"
const WHT = "[color=#ffffff]"   
const HIR = "[color=#ff0000]"
const HIG = "[color=#00ff00]"
const HIY = "[color=#ffff00]"
const HIB = "[color=#44cef6]"
const HIM = "[color=#ff00ff]"
const HIC = "[color=#177cb0]"
const HIW = "[color=#e9e7ef]"
const BRED = "[color=#ff2121]"
const BGRN = "[color=#00e500]"
const BYEL = "[color=#ffb61e]"
const BBLU = "[color=#4b5cc4]"
const BMAG = "[color=#8d4bbb]"
const BCYN = "[color=#1685a9]"
const HBRED = "[color=#ff2121]"
const HBGRN = "[color=#40de5a]"
const HBYEL = "[color=#eacd76]"
const HBBLU = "[color=#3b2e7e]"
const HBMAG = "[color=#815463]"
const HBCYN = "[color=#00e09e]"
const HBWHT = "[color=#f0fcff]"



export(String) var type = "martial" 
export(String) var martialtype = "skill"
export(int,0,100) var learn_bonus = 30
export(int,0,100) var practice_bonus = 30
export(int,0,100) var success = 30
export(int,0,10) var power_point = 1

var info = []

func _init() -> void:
	help()
	
func help():
	pass
	
func notify_fail(s):
	print_debug(s)		

func create():
#	seteuid(getuid());
	pass

#
# valid_learn()
#
# This function is to check if a character should be able to 
# learn/study/practice the skill. The default function just
# returns 1 to allow any characters improve the skill. However,
# a good skill should has its own feature and restriction. Redefine
# this function in your skill object and make it reasonable 
# according to the power of the skill.

func valid_learn(me) :
	return 1

func valid_effect(me, weapon, action_name:String, skill:int) :
	return 1;

# 
# type()
#
# This function should return the type of the skill. The skill type now
# affects if the skill requires combat exp in order to be learned (see
# /cmds/std/learn.c ) and the ranking of a skill level (see 
# /cmds/usr/skills.c )。
# Currently we have only 2 types of skill: "martial" and "knowledge".

func type() :
	return "martial"

#
# skill_improved()
#
# This function is called when a character's skill has gained a new level.
# You can make some modify to a character according to the skill.

func skill_improved(me) :
	pass

#
# exert_function()
#
#     This function is used by the "exert" command as specific skill's 
# command parser. This function parses the arguments in the standard form
# (that is, exert <function> [<target>]). When <target> is not present,
# use the character himself as default.
#     In order to use this default exert command parser, you must define
# a function called exert_function_file(string func) in the skill object
# that takes the function name as argument and return the file name that
# defines the specified function. 

#func exert_function(me,arg:String):
#	var func_
#	var target
#	var file
#	var target_ob;
#
#	if( sscanf(arg, "%s %s", func_, target)==2 ) :
#		target_ob = present(target, environment(me));
#		if( !target_ob ) :
#			return notify_fail("这里没有 " + target + "。\n");
#	else :
#		func_ = arg;
#		target_ob = me;
#
#	file = this_object().exert_function_file(func_)
#	if( !stringp(file) || file_size(file + ".c") <= 0 ):
#		return 0;
#
#	return call_other( file, "exert", me, target_ob);
#
#func perform_action(me, arg):
#	var action
#	var target
#	var file;
#	var target_ob;
#
#	if( sscanf(arg, "%s %s", action, target)==2 ) :
#		target_ob = present(target, environment(me));
#		if( !target_ob ) :
#			return notify_fail("这里没有 " + target + "。\n");
#	else :
#		action = arg;
#
#	file = this_object().perform_action_file(action)
#	if( !stringp(file) || file_size(file + ".c") <= 0 ):
#		return 0;
#
#	return call_other( file, "perform", me, target_ob);


#func cast_spell(var me, string spell, object target):
#	string file;
#
#	notify_fail("你所选用的咒文系中没有这种咒文。\n");
#	file = this_object().cast_spell_file(spell)
#	if( !stringp(file) || file_size(file + ".c") <= 0 ):
#		return 0;
#
#	return (int)call_other( file, "cast", me, target);
#
#
#func conjure_magic(object me, string spell, object target):
#	var file;
#	notify_fail("你所选用的法术系中没有这种法术。\n");
#	file = this_object().conjure_magic_file(spell)
#	if( !stringp(file) || file_size(file + ".c") <= 0 ):
#		return 0;
#	return call_other( file, "conjure", me, target);
#
#func scribe_spell(object me, object ob, string spell):
#	var file;
#	file = this_object().scribe_spell_file(spell)
#	if( !stringp(file) || file_size(file + ".c") <= 0 ):
#		return 0;
#	return call_other( file, "scribe", me, ob );

# The following two functions are used to modify the random function
# for shaolin wugong.

func sum(n:int,base:int,d:int):
	return (n*(2*base+(n-1)*d)/2);

func NewRandom(n:int,base:int,d:int):
	var i = 1;
	var randnum = randi()%(sum(n,base,d));

	if (sum(6,base,d) < randnum):
		i = 7;
		while (sum(i,base,d) < randnum):
			i = i + 1;
	else :
		while (sum(i,base,d) < randnum):
			i= i + 1;
	return (i-1);
	
func write(arg):
	info.append(arg)
	
func get_info()	:
	var msg = ""
	for i in range(info.size()) :
		msg	+= info[i]
	return msg
