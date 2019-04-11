// hulannaao.c 湖蓝衲袄

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
	set_name(HIB"湖蓝衲袄"NOR, ({"hulan naao", "cloth"}));
	set_weight(1500);
	if ( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "一套湖蓝色的布袄，江湖人多穿此类衣服御寒。\n");
		set("unit", "套");
		set("value", 500);
		set("material", "cloth");
		set("armor_prop/armor", 3);
	}
	setup();
}
