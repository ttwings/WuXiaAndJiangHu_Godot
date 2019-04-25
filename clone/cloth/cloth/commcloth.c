// commcloth.c
#include <ansi.h>
#include <armor.h>
inherit CLOTH;

string *name = ({
	"轻纱长裙",
	GRN "碧色纱衣" NOR,
	CYN "蔚蓝长裙" NOR,
	RED "撒花裙" NOR,
	"绵裙",
	"百褶裙",
	"丝裙",
	MAG "花锦袄" NOR,
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
		set("unit", "件");
		set("value", 0);
		set("armor_prop/armor", 1);
		set("material", "cloth");
		set("female_only", 1);
	}
	setup();
}
