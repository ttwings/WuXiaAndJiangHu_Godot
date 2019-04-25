// cuff_book.c

inherit ITEM;

void create()
{
	set_name("拳法入门", ({"cuff book", "shu", "book"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本普普通通的拳法入门，大街上随处可见。\n");
		set("value", 100);
		set("material", "paper");
		set("skill", ([
								 "name":"cuff",
						 "exp_required":100,
							"jing_cost":20,
						   "difficulty":20,
							"max_skill":20]));
	}
}
