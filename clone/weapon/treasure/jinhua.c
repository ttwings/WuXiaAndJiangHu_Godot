// jinhua.c 夺命金花
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>
#include <ansi.h>
inherit THROWING;
inherit F_UNIQUE;

void create()
{
	set_name(HIY"夺命金花"NOR, ({ "duoming jinhua", "flower", "jinhua" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value", 0);
		set("base_unit", "朵");
		set("base_weight", 300);
		set("base_value", 0);
		set("material", "iron");
		set("long", "夺命金花是金花婆婆的独门暗器，既狠且毒。\n");
		set("wield_msg", HIC"$N迅速地从袖中摸出一把夺命金花，扣在手中！\n"NOR);
		set("unwield_msg",HIC"$N将手里剩下的夺命金花收回袖中。\n"NOR);
	}
	set_amount(20);
	init_throwing(100);
	setup();
}
