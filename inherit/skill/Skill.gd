#	skill.c
#
# 	This is the standard skill daemon object. All objects defining a skill
#	should inherit this as its skeleton.

# inherit F_CLEAN_UP;
class_name Skill

func create():
	seteuid(getuid());

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

func exert_function(me,arg:String):
	var func_
	var target
	var file
	var target_ob;

	if( sscanf(arg, "%s %s", func_, target)==2 ) :
		target_ob = present(target, environment(me));
		if( !target_ob ) return notify_fail("这里没有 " + target + "。\n");
	else :
		func_ = arg;
		target_ob = me;
	
	file = this_object().exert_function_file(func_)
	if( !stringp(file) || file_size(file + ".c") <= 0 ):
		return 0;

	return call_other( file, "exert", me, target_ob);

func perform_action(object me, string arg):
	string action, target, file;
	object target_ob;

	if( sscanf(arg, "%s %s", action, target)==2 ) :
		target_ob = present(target, environment(me));
		if( !target_ob ) return notify_fail("这里没有 " + target + "。\n");
	else :
		action = arg;

	file = this_object().perform_action_file(action)
	if( !stringp(file) || file_size(file + ".c") <= 0 ):
		return 0;

	return call_other( file, "perform", me, target_ob);


func cast_spell(object me, string spell, object target):
	string file;

	notify_fail("你所选用的咒文系中没有这种咒文。\n");
	file = this_object().cast_spell_file(spell)
	if( !stringp(file) || file_size(file + ".c") <= 0 ):
		return 0;

	return (int)call_other( file, "cast", me, target);


func conjure_magic(object me, string spell, object target):
	var file;
	notify_fail("你所选用的法术系中没有这种法术。\n");
	file = this_object().conjure_magic_file(spell)
	if( !stringp(file) || file_size(file + ".c") <= 0 ):
		return 0;
	return call_other( file, "conjure", me, target);

func scribe_spell(object me, object ob, string spell):
	var file;
	file = this_object().scribe_spell_file(spell)
	if( !stringp(file) || file_size(file + ".c") <= 0 ):
		return 0;
	return call_other( file, "scribe", me, ob );

# The following two functions are used to modify the random function
# for shaolin wugong.

func sum(n:int,base:int,d:int):
	return (n*(2*base+(n-1)*d)/2);

func NewRandom(n:int,base:int,d:int):
	var i = 1;
	var randnum = random(sum(n,base,d));

	if (sum(6,base,d) < randnum):
		i = 7;
		while (sum(i,base,d) < randnum):
			i = i + 1;
	else :
		while (sum(i,base,d) < randnum):
			i= i + 1;
	return (i-1);
