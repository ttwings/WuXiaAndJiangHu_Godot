extends GameObject

class_name Weapon

## weapon.c
## Last Modified by winder on Feb. 28 2001
## "damage" = sharpness
## "rigidity" according to damage but need consider of weapon type
#
##include <weapon.h>
##include <ansi.h>
#
##ifdef AS_FEATURE
##include <dbase.h>
##else
#inherit EQUIP;
##endif

## axe.c

#func init_axe(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | EDGED | SECONDARY);
#	set("skill_type", "axe");
#	set("rigidity", (int)(damage/2));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "chop", "slash", "slice", "hack" }) );
#	}
#}
#
## blade.c
#
#func init_blade(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | EDGED | SECONDARY);
##	set("flag", 2);
#	set("skill_type", "blade");
#	set("rigidity", (int)(damage/3));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "slash", "slice", "hack" }) );
#	}
#}
#
## club.c
#
#func init_club(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | LONG | SECONDARY);
##	set("flag", 1);
#	set("skill_type", "club");
#	set("rigidity", (int)(damage/5));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "bash", "crush", "slam" }) );
#	}
#}
#
## dagger.c
#
#func init_dagger(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", flag | EDGED | SECONDARY );
##	set("flag", 0);
#	set("skill_type", "dagger");
#	set("rigidity", (int)(damage/4));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "slice", "pierce", "thrust" }) );
#	}
#}
#
## fork.c
#
#func init_fork(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | POINTED | SECONDARY);
##	set("flag", 1);
#	set("skill_type", "fork");
#	set("rigidity", (int)(damage/3));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "impale", "pierce", "thrust" }) );
#	}
#}
#
## hammer.c
#
#func init_hammer(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", flag | SECONDARY);
##	set("flag", 2);
#	set("skill_type", "hammer");
#	set("rigidity", (int)(damage/2));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "bash", "crush", "slam" }) );
#	}
#}
#
## hook.c
#
#func init_hook(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | EDGED | SECONDARY);
#	set("skill_type", "hook");
#	set("rigidity", (int)(damage/4));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "chop", "hack"}) );
#	}
#}
#
## spear.c
#
#func init_spear(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | LONG | SECONDARY);
##	set("flag", 1);
#	set("skill_type", "spear");
#	set("rigidity", (int)(damage/4));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "bash", "thrust", "pierce", "impale", "crush" }) );
#	}
#}
#
## staff.c
#
#func init_staff(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | LONG | SECONDARY);
##	set("flag", 1);
#	set("skill_type", "staff");
#	set("rigidity", (int)(damage/3));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "bash", "crush", "slam" }) );
#	}
#}
#
## stick.c
#
#func init_stick(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | LONG | SECONDARY);
##	set("flag", 1);
#	set("skill_type", "stick");
#	set("rigidity", (int)(damage/4));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "bash", "crush", "slam" }) );
#	}
#}
#
## sword.c
#
func init_sword(damage:int, flag:int):
	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | EDGED | SECONDARY);
#	set("flag", 2);
	set("skill_type", "sword");
	set("rigidity", damage/4);
	if( !query("actions") ):
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ["slash", "slice", "thrust" ] );
#
## throwing.c
#
#func init_throwing(int damage, int flag)
#{
#	set("weapon_prop/damage", damage);
#	set("flag", (int)flag | SECONDARY);
##	set("flag", 8);
#	set("skill_type", "throwing");
#	set("rigidity", (int)(damage/6));
#	if( !query("actions") ) {
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
#		set("verbs", ({ "throw" }) );
#	}
#}
#
## whip.c
#
func init_whip(damage, flag):
	set("weapon_prop/damage", damage);
	set("flag", flag );
# #	set("flag", 2);
	set("skill_type", "whip");
	set("rigidity", damage/3);
	if( !query("actions") ) :
#		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ["whip" ]);

# func this_object():
# 	return self
	
# func this_player():
# #	返回当前操作角色
# 	pass

func set_desc(w_lv:int,w_or:String,w_name:String):
	var weapon : GameObject
	var me : GameObject
	var w_liang :  String
	var player_name : String
	var make_time : String
	
	var result1
	var result2
	var result3
	var result4
	var result

	weapon = this_object();
	me = this_player();
	w_liang = weapon.query("unit");
	player_name=me.query("name");
	make_time=me.query("weapon/time");

	result1="这是一"+w_liang+"用"+w_or+"打造而成的"+w_name+"。\n";
	match w_or:
		"千年神木":
			result2=RED + "看起来黑中透红，似乎十分坚硬。\n" + NOR;
		"海底金母":
			result2=HIM + "看起来紫澄澄的，似乎十分沉重。\n" + NOR;
		"寒丝羽竹":
			result2=HIG + "看起来晶莹碧绿，透着丝丝的寒意。\n" + NOR;
		"陨星铁石":
			result2=BLK + "看起来焦黑一片，看来是坚硬之极。\n" + NOR;
#		_:
#
#			pass
	match w_lv :
		1,2,3:
			result3 = "但似乎威力还没有开发出来，是习武之人常用的练武兵器。兵刃晃动，恍若" + HIC + "清波澹澹。\n" + NOR;
		4,5,6:
			result3 = "但似乎威力并不很大，象是江湖人常用的护身兵刃。兵刃晃动，恍若" + HIC + "秋水无痕。\n" + NOR;
		7,8,9:
			result3 = "隐隐的散发着一丝令人不安的气息。兵刃晃动，恍若" + HIC + "朔风出塞。\n" + NOR;
		10,11,12:
			result3 = "散发着一丝令人不安的气息, 显然普通兵器已不能和他相比了。兵刃晃动，恍若" + HIC + "白羽飘零。\n" + NOR;
		13,14,15:
			result3 = "向外散发着一丝迷蒙的雾气，竟有一种霸气散发了出来。兵刃晃动，恍若"+ HIC +"霜冷长河。\n"+ NOR;
#			break;
		16,17,18:
			result3 = "一股霸气直冲霄汉，直叫神惊鬼泣。兵刃晃动，恍若"+ HIC +"雪落无声。\n"+ NOR;
#			break;
		19,20,21:
			result3 = "霸气似乎有所收敛，但更多的是有了一股骇人的戾气。兵刃晃动，恍若"+ HIC +"寒潭惊雁。\n"+ NOR;
#			break;
		22,23,24:
			result3 = "冲天的戾气叫人看了不由心惊胆战，不愿再看第二眼。兵刃晃动，恍若"+ HIC +"九天龙吟。\n"+ NOR;
#			break;
		25,26,27:
			result3 = "戾气似乎削减了不少，一股温和的王者之气透了出来。兵刃晃动，恍若"+ HIC +"青虹贯日。\n"+ NOR;
#			break;
		28,29,30:
			result3 = "一股温和的王者之气悠悠的散发了出来。兵刃晃动，恍若"+ HIC +"冷月断魂。\n"+ NOR;
#			break;
		_:
			result3 = "一种庄严，温和，凛然而不可侵犯的气息让人不敢有一丝亵渎之意, 它已经返朴归真，成为真正的上古神兵。兵刃晃动，直欲" + HIC +"气冲斗牛。\n"+ NOR;
	result4="上面用小篆刻着一行小字：\n\t"+player_name+"铸于"+make_time+"\n";
	result=result1+result2+result3+result4;
	weapon.set("long",result);