// menghan_yao.c

inherit COMBINED_ITEM;

void create()
{
	set_name("蒙汗药", ({"menghan yao", "yao"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这是极普通的蒙汗药. \n");
		set("unit", "包");
		set("pour_type", "slumber_drug");
		set("base_value", 700);
		set("base_unit", "些");
		set("base_weight", 30);
	}
	set_amount(1);
}
