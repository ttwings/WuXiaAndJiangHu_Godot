// dufeng.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
	set_name("毒蜂", ({"dufeng", "feng"}));
	set("race", "昆虫");
	set("subrace", "飞虫");
	set("age", 5);
	set("long", "这是一只毒蜂，正向你袭击。\n");
	set("str", 50);
	set("dex", 60);

	set("limbs", ({"头部", "身体", "翅膀", "尾巴"}));

	set_temp("apply/attack", 50);
	set_temp("apply/armor", 30);

	setup();
}

void unconcious()
{
	object ob;

	if (base_name(environment(this_object())) == "/d/dali/chhill4" &&
		random(6) > 0)
	{
		ob = new (__FILE__);
		ob->move(environment());
		message_vision("\n嗡，嗡，嗡，又飞来一只毒蜂。\n", this_object());
	}
	else
	{
		message_vision("\n一阵风把死蜂吹走了。\n", this_object());
	}

	destruct(this_object());
}

void die()
{
	object ob;

	if (base_name(environment(this_object())) == "/d/dali/chhill4" && random(6) > 0)
	{
		ob = new (__FILE__);
		ob->move(environment());
		message_vision("\n嗡，嗡，嗡，又飞来一只毒蜂。\n", this_object());
	}
	else
	{
		message_vision("\n一阵风把死蜂吹走了。\n", this_object());
	}

	destruct(this_object());
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	victim->apply_condition("insect_poison", 3 + random(3) +
												 victim->query_condition("insect_poison"));
}
