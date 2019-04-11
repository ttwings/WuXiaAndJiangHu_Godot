// /clone/shop/dali_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "拨云堂");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
                "down" : "/d/dali/majiu",
        ]));
	set("objects", ([
                __DIR__"waiter" : 1,
        ]));
	set("shop_type", 0);

	setup();
}

void init()
{
	if (query("shop_type") == 0)
		set("long", @LONG
这里是大理城里最著名的老字号，整个铺面装修得相当十分艳丽，
从内到外透着大西南的味儿。不过店里的货柜上却空无一物，看样子已
经很久没人来打理了。
LONG);
	else
		set("long", @LONG
这里是大理城里最著名的老字号，整个铺面装修得相当十分艳丽，
从内到外透着大西南的味儿。店铺里的伙计正招呼着客人，忙得满头大
汗。
LONG);
        return;
}

