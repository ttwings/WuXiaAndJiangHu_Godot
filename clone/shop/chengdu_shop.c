// /clone/shop/chengdu_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "清香园");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
                "down" : "/d/chengdu/majiu",
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
成都号称天府之国，物产丰盛，富甲一时。整个店铺装潢雅致，看
得出店主是费了一番心思的，不过店里的货柜上却空无一物，看样子已
经很久没人来打理了。
LONG);
	else
		set("long", @LONG
成都号称天府之国，物产丰盛，富甲一时。这家残月楼出售各式各
样的稀有物品，都是在别地难于购买的。整个店铺装潢雅致，看得出店
主是费了一番心思的。
LONG);
        return;
}

