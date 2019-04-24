// commcloth.c
#include <ansi.h>
#include <armor.h>
inherit CLOTH;

string *name = ({
	"ÇáÉ´³¤È¹",
	GRN "±ÌÉ«É´ÒÂ" NOR,
	CYN "ÎµÀ¶³¤È¹" NOR,
	RED "Èö»¨È¹" NOR,
	"ÃàÈ¹",
	"°ÙñÞÈ¹",
	"Ë¿È¹",
	MAG "»¨½õ°À" NOR,
});
string *id = ({
	"chang qun",
	"bisha yi",
	"weilan changqun",
	"sahua qun",
	"mian qun",
	"baizhe qun",
	"si qun",
	"huajin ao",
});

void create()
{
	int i = random(sizeof(name));
	set_name(name[i], ({id[i], "cloth"}));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "¼þ");
		set("value", 0);
		set("armor_prop/armor", 1);
		set("material", "cloth");
		set("female_only", 1);
	}
	setup();
}
