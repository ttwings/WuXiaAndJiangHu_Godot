// feicui.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(GRN"翡翠"NOR, ({ "fei cui", "feicui" }) );
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "一块暗绿如深潭古水般的翡翠。\n");
		set("unit", "块");
		set("value", 60000 );
	}

}
