// pkp.c 扑克牌

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("扑克牌", ({"pkp"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "张");
		set("long", "这是一张普通的扑克牌，一般的赌徒都使用它。\n");
		set("value", 100);
		set("material", "paper");
		set("wield_msg", "$N「唰」的一声抽出一张$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n放回口袋。\n");
	}
	init_sword(25);
	setup();
}
