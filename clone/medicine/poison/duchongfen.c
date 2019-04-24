// duchongfen.c
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>
//inherit COMBINED_ITEM;
inherit ITEM;
inherit F_UNIQUE;

void create()
{
	set_name("毒虫粉", ({"duchong fen", "duchong", "fen"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一包以蜈蚣、蜘蛛等为原料制成的毒粉。
可以用来生成(make)火堆(huodui)。也可以倒(pour)进酒水里，
或涂(tu)在兵器上。(涂之前必须先点燃(dian)它)\n" );
//		set("unit", "些");
		set("unit", "包");
//		set("base_value", 3000);
//		set("base_unit", "包");
//		set("base_weight", 30);
		set("drug2", __DIR__"duchongfen1");
		set("pour_type", "xx_poison");
	}
	//	set_amount(1);
}
#include "poison.h";
