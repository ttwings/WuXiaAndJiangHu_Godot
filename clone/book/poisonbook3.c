// poisonbook3.c

inherit ITEM;

void create()
{
	set_name("毒经下篇", ({"jing", "book"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本薄薄的小册，上面密密麻麻的记满了各种用毒的法门，可以用(kan)看一看。\n");
		set("no_drop", "这样东西不能离开你。\n");
		set("value", 0);
		set("material", "silk");
	}
}
void init()
{
	add_action("do_read", "kan");
	add_action("do_read", "see");
	add_action("do_read", "du");

	//	this_object()->set("created", 1);
	remove_call_out("destroy_book");
	call_out("destroy_book", 28800); // 8 hours
}

void destroy_book()
{
	message_vision("一阵风吹来，" + (string)this_object()->query("name") + "片片碎落，随风而去了。\n", environment(this_object()));
	destruct(this_object());
}

int do_read(string arg)
{
	object me;
	int jing_cost, gain;
	me = this_player();
	if (!arg || !(arg == "jing" || arg == "book"))
		return notify_fail("什么？\n");
	if (!present(this_object(), this_player()))
		return 0;

	if (me->is_busy())
		return notify_fail("你现在忙着呢，哪有可能静心研读...\n");
	if (me->is_fighting())
		return notify_fail("现在才想到精研毒技，太晚了吧？\n");
	if ((string)me->query("family/family_name") != "五毒教")
	{
		remove_call_out("destroy_book");
		call_out("destroy_book", 0);
	}
	if ((int)me->query_skill("five-poison", 1) < 150 || (int)me->query("combat_exp") < 300000)
		return notify_fail("你看来看去，就是没明白这本书上写的都是啥。\n");
	if ((int)me->query_skill("five-poison", 1) > 300)
		return notify_fail("你的毒技已经很有造诣，这本书不会让你长进多少。\n");

	jing_cost = 35 + (20 - (int)me->query("int"));
	if ((int)me->query("jing") < jing_cost)
		return notify_fail("你现在头晕脑胀，该休息休息了。\n");
	me->receive_damage("jing", jing_cost);

	gain = (int)me->query_skill("five-poison", 1) / 4 + (int)me->query_skill("literate", 1) / 2;
	me->improve_skill("five-poison", gain);

	message_vision("$N拿着绢册仔细阅读,只觉上面所载的种种用毒害人的\n方法都是闻所未闻，看着看着禁不住出了一身冷汗！\n", me);

	return 1;
}
