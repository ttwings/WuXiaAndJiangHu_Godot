// bt_book.c 欧阳锋手迹
// Last Modified by Winder on May. 15 2001

#include <ansi.h>

inherit ITEM;
void setup()
{
}

void init()
{
	add_action("do_du", "du");
	add_action("do_du", "study");
	add_action("do_du", "read");
}

void create()
{
	set_name("线装书", ({"xianzhuang shu", "shu", "book", "xianzhuang"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "一本薄薄的线装书。封面上写有“白驼欧阳锋”几个字。\n");
		set("value", 1);
		set("material", "paper");
		set("no_drop", "这样东西不能离开你。\n");
		set("no_get", "这样东西不能离开那儿。\n");
	}
}

int do_du(string arg)
{
	object ob, me = this_player();
	mapping skill;
	int level, neili_lost;

	if (me->is_busy())
	{
		write("你现在正忙着呢。\n");
		return 1;
	}
	if (me->is_fighting())
	{
		write("你无法在战斗中专心下来读书！\n");
		return 1;
	}
	if (!me->query_skill("literate", 1))
	{
		write("你是个文盲，先学点文化(literate)吧。\n");
		return 1;
	}
	if (arg == "xianzhuang shu" || arg == "shu")
	{
		write("白驼秘要，分制药(zhiyao)、练功(liangong)、图解(tujie) 和功夫(gongfu)。\n");
		me->set_temp("baituo_book", 1);
		return 1;
	}
	if (arg == "zhiyao" && me->query_temp("baituo_book"))
	{
		tell_object(me, "\n
制药：
  汝可于我药房之中找到各种制药器具及草药，
  而要制成绝世之药，非得另找原料。

  鹤红丹：以毒攻毒可克我白驼怪蛇之奇毒。虽是如此，也将消耗内力真元。
          原料：新鲜鹤顶红一个，腹蛇胆五个，断肠草三株。
          制法：。。。待定。。。
\n
    白驼山庄庄主 欧阳锋字\n\n" NOR);  
		return 1;
	}
	if (arg == "tujie" && me->query_temp("baituo_book"))
	{
		tell_object(me, "\n
汝可推开后院铁门，于院中找到蓝、红、彩三块石块。将之顺序
推下(push)之后于其中一院内等待一刻便可入白驼秘道。秘道可
直达山后乱石堆。秘道中之丹顶仙鹤乃是神物，如非性命悠关不
可取它红顶，切记！
\n
    白驼山庄庄主 欧阳锋字\n\n" NOR); 
		return 1;
	}
	if (arg == "liangong" && me->query_temp("baituo_book"))
	{
		tell_object(me, "\n
蛤蟆神功是由当日捕捉玄冰蟾蜍时由此畜生身上习得。现我将玄
冰蟾蜍封闭在后院巨石堆里，没有一定的西毒毒技修为不得冒然
进入，切记！
\n
    白驼山庄庄主 欧阳锋字\n\n" NOR);    
		me->set_temp("baituo_yun", 1);	
		return 1;
	}

	if (arg == "gongfu" && me->query_temp("baituo_book"))
	{
		tell_object(me, "\n
白驼功夫分内外两种，内功便是蛤蟆功，汝可每日去后院乱石堆
练习(strike stone)。外功则是我集多年经验观察蛇蟒搏斗而从
中变化出来的《白驼蛇杖》。蛇杖功夫要点在于灵、狠、毒三字。
汝可从此书中学得(read book)。

\n
    白驼山庄庄主 欧阳锋字\n\n" NOR);	  
		me->set_temp("baituo_book", 2);	 
		return 1;
	}
	if (arg == "xianzhuang" || arg == "book" &&
																 me->query_temp("baituo_book") == 2)
	{
		if ((int)me->query("jing") < 25)
		{
			write("你现在过于疲倦，无法专心下来研读新知。\n");
			return 1;
		}
		if ((int)me->query("neili") < 50)
		{
			write("你内力不够，无法继续钻研。\n");
			return 1;
		}
		level = me->query_skill("lingshe-zhangfa", 1);
		if ((int)me->query("combat_exp") < (int)level * level * level / 10)
		{
			write("你的实战经验不足，再怎么读也没用。\n");
			return 1;
		}
		if (me->query_skill("lingshe-zhangfa", 1) > 50)
		{
			write("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
			return 1;
		}
		me->receive_damage("jing", 15);
		me->add("neili", -1);

		me->improve_skill("lingshe-zhangfa", (int)me->query_skill("literate", 1) / 3 + 1);
		write("你开始仔细研读蛇杖杖法。\n");
		return 1;
	}
}
