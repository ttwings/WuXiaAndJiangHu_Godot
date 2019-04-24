// /clone/shop/yanping_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "双溪楼");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
					 "down":"/d/yanping/majiu",
	]));
	set("objects", ([__DIR__ "waiter":1,
	]));
	set("shop_type", 0);

	setup();
}

void init()
{
	if (query("shop_type") == 0)
		set("long", @LONG
						这里是延平城里最著名的店铺，整个铺面装修得相当精美雅致，楼
							顶凭轩处，正是俯瞰双溪汇流的好去处。不过店里的货柜上却空无一物，
								看样子已经很久没人来打理了。 LONG);
	else
		set("long", @LONG
						这里是延平城里最热闹的店铺，整个铺面装修得相当精美雅致，楼
							顶凭轩处，正是俯瞰双溪汇流的好去处。店铺里的伙计正招呼着客人，
								忙得满头大汗。 LONG);
	return;
}
