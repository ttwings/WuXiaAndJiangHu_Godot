// dodge_book2.c

inherit ITEM;

void create()
{
	set_name("「提纵术」", ({"tizong shu", "book", "shu"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本普普通通的介绍轻功提纵之术的书。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
								 "name":"dodge",
						 "exp_required":0,
							"jing_cost":20 + random(20),
						   "difficulty":20,
							"min_skill":20,
							"max_skill":30]));
	}
}
