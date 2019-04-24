// xisuijing.c 洗髓经

inherit ITEM;
#include <ansi.h>
int do_study(string);
string *skill = ({
	"whip",
	"finger",
	"hand",
	"cuff",
	"claw",
	"strike",
});
void create()
{
	set_name(YEL "洗髓经" NOR, ({"xisuijing"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "卷");
		set("long", "这本破纸筒就是少林最高武学典籍，是达摩老祖面壁九年与易筋经一起\n参悟出来的绝世典籍。\n");
		set("value", 5000);
		set("material", "paper");
	}
}

void init()
{
	add_action("do_study", "canwu");
}

int do_study(string arg)
{
	object where;
	object ob = this_object();
	object me = this_player();
	int myskill, cost, i, exp;

	cost = 50;
	where = environment(me);
	if (!arg || !objectp(ob = present(arg, me)))
		return notify_fail("你要参悟什么？\n");
	if ((int)me->query("jing") < 25)
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}
	if ((string)where->query("short") != "达摩院二楼")
		return notify_fail("洗髓经只能在达摩院里参悟！\n");
	if (!me->query_skill("literate", 1) || me->query_skill("literate", 1) < 100)
	{
		write("你把纸筒翻来翻去，就是什么都读不懂。\n");
		return 1;
	}
	if (!me->query_skill("yijinjing", 1) || me->query_skill("yijinjing", 1) < 100)
	{
		write("也许是没有融会贯通易筋经，你觉得这洗髓经莫名其妙。\n");
		return 1;
	}
	if ((int)me->query("kar") < 25)
	{
		write("你把纸筒翻来翻去，看来你与这绝世典籍无缘。\n");
		return 1;
	}
	if (me->is_busy())
		return notify_fail("你现在正忙着呢。\n");
	if (me->is_fighting())
		return notify_fail("你无法在战斗中专心下来研读新知！\n");
	exp = (int)me->query("combat_exp");
	if (exp < 300000)
	{
		write("你的实战经验不足，不能参悟洗髓经。\n");
		return 1;
	}
	if ((int)me->query("jing") > cost)
	{
		for (i = sizeof(skill); i > 0; i--)
		{
			myskill = me->query_skill(skill[i - 1], 1);
			if (myskill < 180 && myskill > 1 && myskill * myskill * myskill / 10 < exp)
			{
				me->improve_skill(skill[i - 1], (int)(me->query_skill("literate", 1) + me->query("int")) / 2);
			}
		}
		printf("你参悟洗髓经上的经文，似乎有点心得。\n");
		me->receive_damage("jing", cost);
	}
	else
	{
		cost = me->query("jing");
		write("你现在过于疲倦，无法专心下来参悟洗髓经。\n");
	}
	return 1;
}
