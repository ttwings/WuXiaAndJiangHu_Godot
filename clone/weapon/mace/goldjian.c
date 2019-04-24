// goldjian.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
	set_name(HIY "金装锏" NOR, ({"gold mace", "mace", "goldmace", "jinjian"}));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("value", 20000);
		set("material", "gold");
		set("wield_msg", "$N抽出了$n，喃喃道：锏儿，锏儿，再请你一回！\n");
		set("unwield_msg", "$N收起了$n，长吁了一口气道：宝锏果然又显雄风！\n");
	}

	init_mace(95);
	setup();
}
