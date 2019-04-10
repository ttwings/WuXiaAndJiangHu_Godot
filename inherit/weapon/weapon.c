// weapon.c
// Last Modified by winder on Feb. 28 2001
// "damage" = sharpness
// "rigidity" according to damage but need consider of weapon type

#include <weapon.h>
#include <ansi.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

// axe.c

varargs void init_axe(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | EDGED | SECONDARY);
//	set("flag", 2);
	set("skill_type", "axe");
	set("rigidity", (int)(damage/2));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "chop", "slash", "slice", "hack" }) );
	}
}

// blade.c

varargs void init_blade(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | EDGED | SECONDARY);
//	set("flag", 2);
	set("skill_type", "blade");
	set("rigidity", (int)(damage/3));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "slash", "slice", "hack" }) );
	}
}

// club.c

varargs void init_club(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | LONG | SECONDARY);
//	set("flag", 1);
	set("skill_type", "club");
	set("rigidity", (int)(damage/5));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "bash", "crush", "slam" }) );
	}
}

// dagger.c

varargs void init_dagger(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", flag | EDGED | SECONDARY );
//	set("flag", 0);
	set("skill_type", "dagger");
	set("rigidity", (int)(damage/4));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "slice", "pierce", "thrust" }) );
	}
}

// fork.c

varargs void init_fork(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | POINTED | SECONDARY);
//	set("flag", 1);
	set("skill_type", "fork");
	set("rigidity", (int)(damage/3));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "impale", "pierce", "thrust" }) );
	}
}

// hammer.c

varargs void init_hammer(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", flag | SECONDARY);
//	set("flag", 2);
	set("skill_type", "hammer");
	set("rigidity", (int)(damage/2));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "bash", "crush", "slam" }) );
	}
}

// hook.c

varargs void init_hook(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | EDGED | SECONDARY);
	set("skill_type", "hook");
	set("rigidity", (int)(damage/4));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "chop", "hack"}) );
	}
}

// spear.c

varargs void init_spear(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | LONG | SECONDARY);
//	set("flag", 1);
	set("skill_type", "spear");
	set("rigidity", (int)(damage/4));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "bash", "thrust", "pierce", "impale", "crush" }) );
	}
}

// staff.c

varargs void init_staff(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | LONG | SECONDARY);
//	set("flag", 1);
	set("skill_type", "staff");
	set("rigidity", (int)(damage/3));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "bash", "crush", "slam" }) );
	}
}

// stick.c

varargs void init_stick(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | LONG | SECONDARY);
//	set("flag", 1);
	set("skill_type", "stick");
	set("rigidity", (int)(damage/4));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "bash", "crush", "slam" }) );
	}
}

// sword.c

varargs void init_sword(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | EDGED | SECONDARY);
//	set("flag", 2);
	set("skill_type", "sword");
	set("rigidity", (int)(damage/4));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "slash", "slice", "thrust" }) );
	}
}

// throwing.c

varargs void init_throwing(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", (int)flag | SECONDARY);
//	set("flag", 8);
	set("skill_type", "throwing");
	set("rigidity", (int)(damage/6));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "throw" }) );
	}
}

// whip.c

varargs void init_whip(int damage, int flag)
{
	set("weapon_prop/damage", damage);
	set("flag", flag );
//	set("flag", 2);
	set("skill_type", "whip");
	set("rigidity", (int)(damage/3));
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "whip" }) );
	}
}

int set_desc(int w_lv,string w_or,string w_name)
{
	object weapon,me;
	string w_liang,player_name,make_time;
	string result1,result2,result3,result4,result;

	weapon = this_object();
	me = this_player();
	w_liang = weapon->query("unit");
	player_name=me->query("name");
	make_time=me->query("weapon/time");

	result1="这是一"+w_liang+"用"+w_or+"打造而成的"+w_name+"。\n";
	switch(w_or)
	{
		case "千年神木":
			result2=RED"看起来黑中透红，似乎十分坚硬。\n"NOR;
			break;
		case "海底金母":
			result2=HIM"看起来紫澄澄的，似乎十分沉重。\n"NOR;
			break;
		case "寒丝羽竹":
			result2=HIG"看起来晶莹碧绿，透着丝丝的寒意。\n"NOR;
			break;
		case "陨星铁石":
			result2=BLK"看起来焦黑一片，看来是坚硬之极。\n"NOR;
			break;
		default:
			break;
	}
	switch(w_lv)
	{
		case 1:
		case 2:
		case 3:
			result3= "但似乎威力还没有开发出来，是习武之人常用的练武兵器。兵刃晃动，恍若"HIC"清波澹澹。\n"NOR;
			break;
		case 4:
		case 5:
		case 6:
			result3= "但似乎威力并不很大，象是江湖人常用的护身兵刃。兵刃晃动，恍若"HIC"秋水无痕。\n"NOR;
			break;
		case 7:
		case 8:
		case 9:
			result3= "隐隐的散发着一丝令人不安的气息。兵刃晃动，恍若"HIC"朔风出塞。\n"NOR;
			break;
		case 10:
		case 11:
		case 12:
			result3= "散发着一丝令人不安的气息, 显然普通兵器已不能和他相比了。兵刃晃动，恍若"HIC"白羽飘零。\n"NOR;
			break;
		case 13:
		case 14:
		case 15:
			result3= "向外散发着一丝迷蒙的雾气，竟有一种霸气散发了出来。兵刃晃动，恍若"HIC"霜冷长河。\n"NOR;
			break;
		case 16:
		case 17:
		case 18:
			result3= "一股霸气直冲霄汉，直叫神惊鬼泣。兵刃晃动，恍若"HIC"雪落无声。\n"NOR;
			break;
		case 19:
		case 20:
		case 21:
			result3= "霸气似乎有所收敛，但更多的是有了一股骇人的戾气。兵刃晃动，恍若"HIC"寒潭惊雁。\n"NOR;
			break;
		case 22:
		case 23:
		case 24:
			result3= "冲天的戾气叫人看了不由心惊胆战，不愿再看第二眼。兵刃晃动，恍若"HIC"九天龙吟。\n"NOR;
			break;
		case 25:
		case 26:
		case 27:
			result3= "戾气似乎削减了不少，一股温和的王者之气透了出来。兵刃晃动，恍若"HIC"青虹贯日。\n"NOR;
			break;
		case 28:
		case 29:
		case 30:
			result3= "一股温和的王者之气悠悠的散发了出来。兵刃晃动，恍若"HIC"冷月断魂。\n"NOR;
			break;
		default:
			result3= "一种庄严，温和，凛然而不可侵犯的气息让人不敢有一丝亵渎之意, 它已经返朴归真，成为真正的上古神兵。兵刃晃动，直欲"HIC"气冲斗牛。\n"NOR;
	}

	result4="上面用小篆刻着一行小字：\n\t"+player_name+"铸于"+make_time+"\n";
	result=result1+result2+result3+result4;
	weapon->set("long",result);

}
