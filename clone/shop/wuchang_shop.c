// /clone/shop/wuchang_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "悦新昌");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
			 "down":"/d/jiangling/majiu",
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
				悦新昌是落于长江边上，是一间装潢雅致的店铺。江城楼宇别具一
				    格，这家店铺也不例外。不过货柜上却空无一物，看样子已很久没人来
					打理了。 LONG);
	else
		set("long", @LONG
				悦新昌坐落于长江边上，是一间装潢雅致的店铺。江城楼宇别具一
				    格，这家店铺也不例外。此时店堂伙计正忙上忙下，招呼着客人。 LONG);
	return;
}
