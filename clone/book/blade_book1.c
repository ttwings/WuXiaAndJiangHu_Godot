// blade_book1.c

inherit ITEM;

void create()
{
	set_name("「刀术」", ({"blade book", "book", "shu"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本普普通通的介绍刀法的书，字迹很是潦草。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
								 "name":"blade",
						 "exp_required":100,
							"jing_cost":20 + random(20),
						   "difficulty":20,
							"min_skill":20,
							"max_skill":30]));
	}
}
