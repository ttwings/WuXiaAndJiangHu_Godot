// jinshe-jian.c 金蛇剑
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>
#include <ansi.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name(YEL"金蛇剑"NOR, ({ "jinshe jian", "sword", "jian" }));
	set_weight(50000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", 
"这剑金光灿烂，握在手中甚是沉重，看来竟是黄金混和了其他五
金所铸，剑身上一道血痕，发出碧油油的暗光，极是诡异。剑的
形状甚是奇特，整柄剑就如是一条蛇盘曲而成，蛇尾勾成剑柄，
蛇头则是剑尖，蛇舌伸出分叉，是以剑尖竟有两叉。\n");
		set("value", 10000);
		set("material", "gold");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中，顿时全身凉飕飕地只感寒气逼人。\n");
		set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
	}
	init_sword(130);
	setup();
}
