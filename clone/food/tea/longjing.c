//longjing.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
//实际玩家买到应该是个茶壶。一开始是满的。
	set_name("龙井茶",({"longjing cha", "cha hu", "hu"}));
 	set_weight(120);
	if (clonep())
		 set_default_object(__FILE__);
	 else {
 		set("long", "一壶新沏的龙井茶，悠悠地冒着香气~~~~~~\n");
		set("unit", "壶");
 		set("value", 80);
        set("remaining",10);
		set("drink_supply", 20);
	}
	set("liquid", ([
		"type": "tea",
		"name": "龙井茶",
		"remaining": 15,
		"drunk_apply": 3,
	]));
}

