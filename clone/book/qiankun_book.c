// qiankun-xinfa 乾坤大挪移心法
// by King 97.05

#include <ansi.h>

inherit ITEM;
void setup()
{
}

void init()
{
	add_action("do_du", "kan");
}

void create()
{
	set_name("羊皮", ({"qiankunbook", "skin"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "张");
		set("long", 
"这是一张羊皮，一面有毛，一面光滑。第一行是“明教圣
火心法，乾坤大挪移”十一个字。原来这就是武林第一秘
籍《乾坤大挪移》心法，相传来自西域山中老人所作。
想修这门绝世武功，就好好看(kan)这本书吧。\n");
		set("value", 50000);
		set("material", "paper");
	}
}

int do_du(string arg)
{
	object me = this_player();
	object where = environment(me);
	object ob;
	mapping skill;
	int qklevel, lvl;
	int neili_lost;

	if (arg != "qiankunbook")
		return notify_fail("你要读什么？\n");
	if (!present(this_object(), this_player()))
		return 0;
	if ((int)me->query("jing") < 25)
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}
	if (where->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");
	if (me->is_busy())
		return notify_fail("你现在正忙着呢。\n");
	if (me->is_fighting())
		return notify_fail("你无法在战斗中专心下来研读新知！\n");
	if (!id(arg) || !objectp(ob = present(arg, me)))
		return notify_fail("你要读什么？\n");
	if ((string)me->query("gender") == "女性")
		//		return notify_fail("你先天不足，要修乾坤大挪移，恐怕走火入魔。\n");
		if (!me->query_skill("literate", 1))
			return notify_fail("你是个文盲，先学点文化(literate)吧。\n");
	if (!me->query_skill("jiuyang-shengong", 1))
		return notify_fail("你没有九阳神功做根坻，不能读乾坤大挪移。\n");
	if ((int)me->query("neili") < 1000)
	{
		write(CYN "忽然，你觉得内息一乱，知道不好！\n" NOR);
		me->unconcious();
		return 1;
	}

	qklevel = me->query_skill("qiankun-danuoyi", 1);
	neili_lost = qklevel / 10;
	if (neili_lost < 5)
		neili_lost = 5;
	lvl = qklevel / 20;
	if (lvl < 1)
		lvl = 1;

	message("vision", me->name() + "专心研读乾坤大挪移，脸色忽青忽红，连变" + lvl + "次。\n", environment(me), me);

	if (me->query("gender") == "无性" && qklevel > 99)
		return notify_fail("你先天不足，再学下去难免走火入魔。\n");

	if ((int)me->query_skill("force", 1) < 100)
		return notify_fail("就这么点基本内功还想学乾坤大挪移？\n");

	if ((int)me->query("max_neili", 1) < 1500)
		return notify_fail("就这么点内力还想学乾坤大挪移？\n");

	if ((int)me->query_skill("force", 1) < lvl)
		return notify_fail("你的基本内功火候还不够，小心走火入魔！\n");

	if ((int)(me->query("max_neili", 1) / 15) < lvl)
		return notify_fail("你的内力火候还不够，小心走火入魔！\n");

	if ((int)me->query("combat_exp") < (int)qklevel * qklevel * qklevel / 10)
		return notify_fail("你的实战经验不足，再怎么读也没用。\n");

	if (me->query_skill("qiankun-danuoyi", 1) > 249)
		return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");

	me->receive_damage("jing", (40 - (int)me->query("int")));
	me->set("neili", (int)me->query("neili") - neili_lost);
	if (!me->query_skill("qiankun-danuoyi", 1))
		me->set_skill("qiankun-danuoyi", 0);
	me->improve_skill("qiankun-danuoyi", (int)me->query_skill("literate", 1) / 3 + 1);
	write("你研读《乾坤大挪移》，颇有心得。\n");
	return 1;
}
