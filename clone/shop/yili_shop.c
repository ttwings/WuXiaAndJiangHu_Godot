// /clone/shop/yili_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
	set("short", "牛大碗");
	set("no_fight", 1);
	set("no_beg", 1);
	set("owner", "VOID_SHOP");
	set("exits", ([
			 "down":"/d/xingxiu/majiu",
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
				来往于牛大碗的多是商富大贾。楼内装潢得非常典雅精致，堪称兰
				    州城内一绝。红木铺地，漆门雕窗，大堂正中挂着一幅百鹤图。不过货
					柜上却空无一物，看样子已很久没人来打理了。 LONG);
	else
		set("long", @LONG
				来往于牛大碗的多是商富大贾。楼内装潢得非常典雅精致，堪称兰
				    州城内一绝。红木铺地，漆门雕窗，大堂正中挂着一幅百鹤图。此时店
					堂伙计正忙上忙下，招呼着客人。 LONG);
	return;
}
