// /clone/shop/yangzhou_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "月明轩");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
                "down" : "/d/city/majiu",
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
这里是扬州城里最著名的店铺，整个铺面装修得相当精美雅致，显
出十里扬州繁华大方的气派。不过店里的货柜上却空无一物，看样子已
经很久没人来打理了。
LONG);
	else
		set("long", @LONG
这里是扬州城里最热闹的店铺，铺里人来人往，川流不息。铺面装
修得精美雅致，显出十里扬州繁华大方的气派。店铺里的伙计正招呼着
客人，忙得满头大汗。
LONG);
        return;
}

