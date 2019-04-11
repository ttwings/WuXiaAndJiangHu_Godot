// lingzhou_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "同福居");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
                "down" : "/d/lingzhou/majiu",
        ]));
	set("no_steal", 1);
	set("objects", ([
                __DIR__"waiter" : 1,
        ]));
	set("no_clean_up", 0);
	set("shop_type", 0);

	setup();
}

void init()
{
	if (query("shop_type") == 0)
		set("long", @LONG
这里便是灵州城里最有名的同福居，塞上江南，真是名不虚传，店
里陈设清新可人，俨然江南名店一般。不过店里的货柜上却空无一物，
看样子已经很久没人来打理了。
LONG);
	else
		set("long", @LONG
这里便是灵州城里最有名的同福居，塞上江南，真是名不虚传，店
里陈设清新可人，俨然江南名店一般。铺面宽敞明亮，柜上摆满了各式
各样、琳琅满目的货物。
LONG);
        return;
}
