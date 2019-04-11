// /clone/shop/foshan_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "天海楼");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
		"down" : "/d/foshan/majiu",
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
天海楼是佛山城内有名的店铺，岭南向来多豪侠之士，此楼内外装
饰豪放，颇有豪杰之气。不过店里的货柜上却空无一物，看样子已经很
久没人来打理了。
LONG);
	else
		set("long", @LONG
天海楼是佛山城内有名的店铺，岭南向来多豪侠之士，此楼内外装
饰豪放，颇有豪杰之气。整个铺面宽敞明亮，柜上摆满了各式各样、琳
琅满目的货物。
LONG);
        return;
}

