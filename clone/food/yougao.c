// yougao.c

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("千层油糕", ({"qianceng yougao", "yougao"}));
	set_weight(50); //一两
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "个");
		set("value", 40);
		set("food_remaining", 1);
		set("food_supply", 40);
	}
	setup();
}
