// beijing_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "瑞蚨祥");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
                "down" : "/d/beijing/majiu",
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
这里便是北京城里最有名的瑞蚨祥，铺里人来人往，川流不息，显
出天子之都繁华大方的气派。不过店里的货柜上却空无一物，看样子已
经很久没人来打理了。
LONG);
	else
		set("long", @LONG
这里便是北京城里最有名的瑞蚨祥，铺里人来人往，川流不息，显
出天子之都繁华大方的气派。铺面宽敞明亮，柜上摆满了各式各样、琳
琅满目的货物。
LONG);
        return;
}
