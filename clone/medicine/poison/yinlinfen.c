// yinlinfen.c
// Last Modified by winder on Feb. 28 2001
// Last Modified by qingyun 04.9.27

#include <ansi.h>
//inherit COMBINED_ITEM;
inherit ITEM;
inherit F_UNIQUE;

void create()
{
	set_name(WHT"银磷粉"NOR, ({ "yinlin fen", "fen", "yinlin" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","一包以骨灰、蛇胆等为原料制成的银光闪闪的毒粉。
可以用来生成(make)火堆(huodui)。也可以倒(pour)进酒水里，
或涂(tu)在兵器上。(涂之前必须先点燃(dian)它)\n" );
		set("unit", "包");
//		set("unit", "些");
//		set("base_value", 5000);
//		set("base_unit", "包");
//		set("base_weight", 30);
		set("drug2", __DIR__"yinlinfen1");
		set("pour_type", "cold_poison");
	}
//	set_amount(1);
}

#include "poison.h";
