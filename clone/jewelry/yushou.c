// yushou.c

#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
	set_name(CYN"玉手镯"NOR, ({"yu shouzhuo", "shuozhuo" }));
	set_weight(500);
	if ( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "白玉雕成的手镯，纹理清晰，圆滑光泽。\n");
		set("unit", "枚");
		set("value", 100000);
		set("material", "gold");
                set("armor_prop/armor", 10);
	}
	setup();
}

