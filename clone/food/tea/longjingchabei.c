// longjingchabei.c
// Last Modified by winder on May. 29 2001

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("Áú¾®²è±­",({"longjing chabei", "cha", "chabei"}));
	set_weight(120);
	if (clonep())
		 set_default_object(__FILE__);
	else {
 		set("long", "Ò»±­ĞÂÆãµÄÁú¾®²è£¬ÓÆÓÆµØÃ°×ÅÏãÆø~~~~~~\n");
		set("unit", "±­");
		set("value", 40);
		set("remaining",10);
		set("drink_supply", 20);
	}
	set("liquid", ([
		"type": "tea",
		"name": "²è",
		"remaining": 15,
		"drunk_apply": 5,
	]));
}

