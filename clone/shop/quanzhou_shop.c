// /clone/shop/quanzhou_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "福人颐");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
			 "down":"/d/quanzhou/majiu",
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
				这里是泉州城里的一家店铺。泉州城虽小，清源山却甚为著名。从
				    店铺红木雕窗放眼望去，整个泉州古城熙熙攘攘的街道尽收眼底。不过
					店里的货柜上却空无一物，看样子已经很久没人来打理了。 LONG);
	else
		set("long", @LONG
				这里是泉州城里的一家店铺。泉州城虽小，清源山却甚为著名。从
				    店铺红木雕窗放眼望去，整个泉州古城熙熙攘攘的街道尽收眼底。店铺
					里的伙计正招呼着客人，忙得满头大汗。 LONG);
	return;
}
