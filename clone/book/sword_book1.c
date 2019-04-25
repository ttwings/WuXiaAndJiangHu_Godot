// sword_book1.c

inherit ITEM;

void create()
{
	set_name("说剑", ({"sword book", "shu", "book"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是庄子中的说剑篇，似乎对基本剑术有所裨益。\n");
		set("value", 100);
		set("material", "paper");
		set("skill", ([
								 "name":"sword",
						 "exp_required":100,
							"jing_cost":20,
						   "difficulty":20,
							"max_skill":20]));
	}
}
