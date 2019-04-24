// waterskin.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("Å£Æ¤¾Æ´ü", ({"wineskin", "skin"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "Ò»¸öÅ£Æ¤·ìµÄ´ó¾Æ´ü£¬´ó¸Å×°µÃ°Ë¡¢¾ÅÉýµÄ¾Æ¡£\n");
		set("unit", "¸ö");
		set("value", 20);
		set("max_liquid", 15);
	}

	// The liquid contained in the container is independent, we set a copy
	// in each cloned copy.
	set("liquid", ([
							 "type":"alcohol",
							 "name":"ºì¾Æ",
						"remaining":15,
					  "drunk_apply":6,
	]));
}
