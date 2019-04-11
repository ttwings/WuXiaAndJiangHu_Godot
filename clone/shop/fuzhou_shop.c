// /clone/shop/fuzhou_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "聚春园");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
                "down" : "/d/fuzhou/majiu",
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
聚春园是福州城内有名的店铺，店堂正中挂着的一块匾额，匾上大
书「三山聚春」四个大字，令人心胸大开。不过店里的货柜上却空无一
物，看样子已经很久没人来打理了。
LONG);
	else
		set("long", @LONG
聚春园是福州城内有名的店铺，店堂正中挂着的一块匾额，匾上大
书「三山聚春」四个大字，令人心胸大开。整个铺面宽敞明亮，柜上摆
满了各式各样、琳琅满目的货物。
LONG);
        return;
}

