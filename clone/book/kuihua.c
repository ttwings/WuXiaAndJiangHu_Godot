// kuihua.c 葵花宝典

inherit ITEM;
void setup()
{
}

void init()
{
	add_action("do_du", "du");
	add_action("do_du", "study");
	add_action("do_join", "join");
}

void create()
{
	set_name("葵花宝典", ({"kuihua baodian", "baodian", "book"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这就是武林第一秘籍《葵花宝典》，相传是一位宫中太监所作。\n");
		set("value", 50000);
		set("material", "paper");
		set("no_drop", "这样东西不能离开你。\n");
		set("no_get", "这样东西不能离开那儿。\n");
	}
}

int do_du(string arg)
{
	object me = this_player();
	object where = environment(me);
	object ob;
	mapping skill;
	int bxlevel;
	int neili_lost;

	if (!(arg == "kuihua baodian" || arg == "baodian" || arg == "book"))
		return 0;

	if (where->query("pigging"))
	{
		write("你还是专心拱猪吧！\n");
		return 1;
	}
	if (me->is_busy())
	{
		write("你现在正忙着呢。\n");
		return 1;
	}
	if (me->is_fighting())
	{
		write("你无法在战斗中专心下来研读新知！\n");
		return 1;
	}
	/*	if(!arg || !objectp(ob = present(arg, me)) )
	{
		write("你要读什么？\n");
		return 1;
	}
*/
	if (!id(arg))
	{
		write("你要读什么？\n");
		return 1;
	}
	if ((string)me->query("gender") == "女性")
	{
		write("自古没有女人可以读《葵花宝典》的。\n");
		return 1;
	}
	if ((string)me->query("gender") == "男性")
	{
		write("《葵花宝典》的第一页写着：欲练神功，必先自宫。\n");
		return 1;
	}
	if (!me->query_skill("literate", 1))
	{
		write("你是个文盲，先学点文化(literate)吧。\n");
		return 1;
	}

	switch (random(3))
	{
	case 0:
		message("vision", me->name() + "偷偷摸摸翻出一本书在读。\n", environment(me), me);
		break;
	case 1:
		message("vision", me->name() + "边读书边骚首弄姿，好象在模仿女人。\n", environment(me), me);
		break;
	case 2:
		message("vision", me->name() + "边读书边把腰身扭来扭去。\n", environment(me), me);
		break;
	}
	if ((int)me->query("jing") < 15)
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}

	if (me->query_skill("bixie-jian", 1) > 84)
		neili_lost = 15;
	else if (me->query_skill("bixie-jian", 1) > 74)
		neili_lost = 10;
	else
		neili_lost = 5;

	if ((int)me->query("neili") < neili_lost)
	{
		write("你内力不够，无法钻研这么高深的武功。\n");
		return 1;
	}
	bxlevel = me->query_skill("bixie-jian", 1);
	if ((int)me->query("combat_exp") < (int)bxlevel * bxlevel * bxlevel / 10)
	{
		write("你的实战经验不足，再怎么读也没用。\n");
		return 1;
	}
	if (bxlevel > 9)
		if ((!objectp(ob = present("golden ring", me))) ||
			(!ob->query("equipped")))
		{
			write("你没戴戒指，感到很难理解阴柔的指法。\n");
			return 1;
		}
	if (bxlevel > 19)
		if ((!objectp(ob = present("flower shoes", me))) ||
			(!ob->query("equipped")))
		{
			write("你没穿绣花鞋，感到很难理解阴柔的步法。\n");
			return 1;
		}
	if (bxlevel > 29)
		if ((!objectp(ob = present("xiuhua zhen", me))) ||
			(!ob->query("equipped")))
		{
			write("你没用绣花针，感到无法理解这种阴柔灵活的武功。\n");
			return 1;
		}
	if (bxlevel > 39)
		if ((!objectp(ob = present("pink cloth", me))) ||
			(!ob->query("equipped")))
		{
			write("你没穿女人的衣衫，感到很难理解阴柔的身法。\n");
			return 1;
		}
	if (bxlevel > 49)
		if ((!objectp(ob = present("golden necklace", me))) ||
			(!ob->query("equipped")))
		{
			write("你没戴项链，觉得练这种阴柔的功夫缺乏自信。\n");
			return 1;
		}
	if (bxlevel > 59)
		if (me->query("rank_info/respect") != "公公")
		{
			write("你现在需要正式加入(join)东厂才能继续深造辟邪剑法。\n");
			write("键入join你便成为东厂的一位太监。这将不影响你的师承，\n");
			write("而且大家都将尊称你为公公。\n");
			me->set_temp("pending/join", 1);
			return 1;
		}

	if (bxlevel > 199)
	{
		write("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
		return 1;
	}

	me->receive_damage("jing", 15);
	me->set("neili", (int)me->query("neili") - neili_lost);
	if (!me->query_skill("bixie-jian", 1))
	{
		me->set_skill("bixie-jian", 0);
		write("		   《葵花宝典》阅读指南\n"
			  "\n    恭喜你开始研习武林第一功夫－－－－辟邪剑法！\n"
			  "注意事项：\n"
			  "一．研习辟邪剑法必先自宫，如你不想让别人发现这个天大的秘密，你必须\n"
			  "    找一无人所在之处阅读，且当有别的玩家在场时不要使用辟邪剑法战斗，\n"
			  "    因为当你阅读或使用辟邪剑法时会出现一些阴柔的举动，使别人产生怀\n"
			  "    疑。切记不可收徒或拜别的玩家为师，以免被人检查你的技能。\n\n"
			  "二．辟邪剑法功力极强，既可作剑法，又可作腾挪之法。\n\n"
			  "三．《葵花宝典》不可送人，出售，丢弃，捡拾，唯一的获取方法是你使用\n"
			  "    你得到的密码去密室寻找。\n\n"
			  "四．辟邪剑法不可通过拜师或自己锻炼来长进，只能通过研习《葵花宝典》\n"
			  "    来提高。\n\n"
			  "	 祝你早日成为武林第一高手，称霸天下！\n");
	}
	me->improve_skill("bixie-jian", (int)me->query_skill("literate", 1) / 3 + 1);
	write("你研读《葵花宝典》，颇有心得。\n");
	return 1;
}

int do_join()
{
	if (this_player()->query("rank_info/respect") == "公公")
	{
		write("你已经加入东厂了，不需要重新加入。\n");
		return 1;
	}

	if (!this_player()->query_temp("pending/join"))
		return 0;

	this_player()->set("rank_info/respect", "公公");
	this_player()->set("rank_info/rude", "阉贼");
	write("恭喜你成为朝廷最重要的机关东厂的一员！\n");
	this_player()->delete_temp("pending/join");
	return 1;
}
int query_autoload() { return 1; }
