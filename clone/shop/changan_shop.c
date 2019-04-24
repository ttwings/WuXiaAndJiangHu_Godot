// /clone/shop/changan_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "同盛祥");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
			 "down":"/d/changan/majiu",
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
				这里是长安城里小有名气的店堂——同盛祥。长安城民众富裕，铺
				    里出售的货物也是别具一格。整个铺面装潢得非常雅致，不过货柜上却
					空无一物，看来已很久没人打理了。 LONG);
	else
		set("long", @LONG
				这里是长安城里小有名气的店堂——同盛祥。长安城民众富裕，铺
				    里出售的货物也是别具一格。整个铺面装潢得非常雅致。货柜上摆满了
					各式各样、琳琅满目的货物。 LONG);
	return;
}
