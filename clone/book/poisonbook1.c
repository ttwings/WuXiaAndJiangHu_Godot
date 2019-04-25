// poisonbook1.c

inherit ITEM;

void create()
{
	set_name("毒经上篇", ({"jing", "book"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本薄薄的小册，上面密密麻麻的写满了各种用毒的基本方法和毒药的配方。\n你可以用(see)看一看。\n");
		set("value", 0);
		set("material", "silk");
		set("skill", ([
								 "name":"five-poison", // name of the skill
						 "exp_required":0,			   // minimum combat experience required
							"jing_cost":20,			   // jing cost every time study this
						   "difficulty":20,			   // the base int to learn this skill
							"max_skill":50			   // the maximum level you can learn
		]));
	}
}
void init()
{
	add_action("do_read", "see");
}
int do_read(string arg)
{
	if (!present(this_object(), this_player()))
		return 0;

	if (arg == "jing" || arg == "book")
		return notify_fail("\n  五毒教灵药配方及功效：\n
       蛇信子+蛇毒囊------>红色药粉----->蛇毒\n
       穿心莲+蜈蚣毒囊---->黄色药粉----->蜈蚣毒\n
       腐骨草+蜘蛛毒囊---->绿色药粉----->蜘蛛毒\n
       鹤顶红+蝎子毒囊---->白色药粉----->蝎子毒\n
       断肠草+蟾蜍毒囊---->黑色药粉----->蟾蜍毒\n
       千日醉+金蛇毒液---->神仙倒------->迷魂药\n
");
}
