// /clone/shop/kaifeng_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "福兴斋");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
                "down" : "/d/kaifeng/majiu",
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
这里是开封城内有名的店铺福兴斋，开封为百年古都，民众富饶。
店铺内装饰得非常豪华，不过柜上却空无一物。伙计在一旁打着盹，看
样子已经很久没人来打理了。
LONG);
	else
		set("long", @LONG
这里是开封城内有名的店铺福兴斋，店堂里人来人往，川流不息。
开封为百年古都，出售的物品也是别具一格。铺面宽敞明亮，柜上摆满
了各式各样、琳琅满目的货物。
LONG);
        return;
}

