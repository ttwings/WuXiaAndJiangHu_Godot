// /clone/shop/suzhou_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "采芝斋");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
			 "down":"/d/suzhou/majiu",
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
				采芝斋坐落于苏州城北，是一间装潢雅致的店铺。苏州城建筑别具
				    一格，这家店铺也不例外。不过货柜上却空无一物，看样子已很久没人
					来打理了。 LONG);
	else
		set("long", @LONG
				采芝斋坐落于苏州城北，是一间装潢雅致的店铺。苏州城建筑别具
				    一格，这家店铺也不例外。此时店堂伙计正忙上忙下，招呼着客人。 LONG);
	return;
}
