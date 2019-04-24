// yuchang-jian.c 鱼肠剑
// Last Modified by winder on Nov. 17 2000

#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;

void setup()
{
}

void init()
{
	if (!query("got"))
		add_action("do_jian", "jian");
}

void create()
{
	set_name(HIR "鱼肠剑" NOR, ({"yuchang jian", "jian", "sword"}));
	set_weight(10000);

	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这就是传说中的鱼肠剑，没想到会在这里出现！\n"
								"你忍不住想把它捡(jian)起来！！！\n");
		set("material", "steel");
		set("no_get", 1);
		set("no_drop", 1);
		set("count", 3);
		set("wield_msg", HIR "一道暗红血光划过，鱼肠剑已落入$N" HIR "手中。\n" NOR);
		set("unwield_msg", HIR "天地忽暗，$N" HIR "手中的鱼肠剑已悄然隐没 。\n" NOR);
	}
	init_sword(1);
	setup();
}

int do_jian(string arg)
{
	object me = this_player();
	if (!id(arg))
		return 0;
	if (query("count") > 0 || me->query_dex() < 40)
	{
		if (query("count") <= 0)
			set("count", 1);
		message_vision(HIR "$N轻轻地捡起鱼肠剑，突然从剑后射出" + chinese_number(query("count")) + "枚钢针，深深的刺入$N的体内。\n" NOR, me);
		if (me->query_dex() > 40)
			add("count", -1);
		me->unconcious();
		me->move("/d/tiezhang/shanlu6");
	}
	else
	{
		message_vision(HIR "$N轻轻地捡起鱼肠剑，突然从剑后射出一枚钢针。但是$N早有防备，马上躲了开去。\n" NOR, me);
		message("channel:rumor", MAG "【谣言】某人：" + this_player()->query("name") + "拿到" + this_object()->query("name") + MAG + "啦。\n" NOR, users());
		tell_object(me, "你捡起一把" + this_object()->query("name") + "。\n");
		set("long", "这是春秋名匠欧冶子所铸的五口宝剑之鱼肠剑。\n剑身长仅寸余，细看之下隐隐有血光浮现。\n");
		//		remove_action(me,"jian");
		set("got", 1);
		set("weapon_prop/damage", 300);
		set("rigidity", 300 / 4);
		move(me);
	}
	return 1;
}
