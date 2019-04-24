// yacai.c

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("鸭菜包子", ({"yacai baozi", "baozi"}));
	set_weight(50); //一两
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "个");
		set("value", 30);
		set("food_remaining", 1);
		set("food_supply", 30);
	}
	setup();
}
