// /clone/shop/hangzhou_shop.c
// Last modified by winder 2003.10.20
inherit SHOP;

void create()
{
	set("short", "颐香斋");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
			 "down":"/d/hangzhou/majiu",
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
				颐香斋乃是由杭州城的老字号，所谓「上有天堂下有苏杭」，杭州
				    城建筑别具一格，这家店铺也不例外。不过货柜上却空无一物，看样子
					已很久没人来打理了。 LONG);
	else
		set("long", @LONG
				颐香斋乃是由杭州城的老字号，所谓「上有天堂下有苏杭」，杭州
				    城建筑别具一格，这家店铺也不例外。店堂装潢得典雅精致，伙计正彬
					彬有礼的招呼着客人。 LONG);
	return;
}
