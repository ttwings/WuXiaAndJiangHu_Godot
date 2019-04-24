// stick_book.c

inherit ITEM;

void create()
{
	set_name("棒法入门", ({"shu", "book"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是本有些年代的书了，封皮上写着《棒法入门》。\n");
		set("value", 100);
		set("material", "paper");
		set("skill", ([
								 "name":"stick",
						 "exp_required":10000,
							"jing_cost":40,
						   "difficulty":20,
							"max_skill":99,
							"min_skill":30,
		]));
	}
}
