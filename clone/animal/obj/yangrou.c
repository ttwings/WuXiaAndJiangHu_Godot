// yangrou.c ¿¾ÑòÍÈ
// Last Modified by winder on Aug. 1 2002

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("¿¾ÑòÍÈ", ({"kao yangtui", "yangtui"}));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "Ò»Ö»¿¾µÃÏãÅçÅçµÄÑòÍÈ¡£\n");
		set("unit", "Ö»");
		set("value", 100);
		set("food_remaining", 4);
		set("food_supply", 60);
	}
}

