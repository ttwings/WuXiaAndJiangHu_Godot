// /clone/shop/wuxi_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "聚丰园");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
			 "down":"/d/wuxi/majiu",
	]));
	set("no_steal", 1);
	set("objects", ([__DIR__ "waiter":1,
	]));
	set("no_clean_up", 0);
	set("shop_type", 0);

	setup();
}

void init()
{
	if (query("shop_type") == 0)
		set("long", @LONG
				聚丰园是无锡城里最著名的店铺，整个铺面装修得相当精美雅致，
				    显出江南大都会繁华大方的气派。不过店里的货柜上却空无一物，看样
					子已经很久没人来打理了。 LONG);
	else
		set("long", @LONG
				聚丰园是无锡城里最著名的店铺，整个铺面装修得相当精美雅致，
				    显出江南大都会繁华大方的气派。店铺里的伙计正招呼着客人，忙得满
					头大汗。 LONG);
	return;
}
