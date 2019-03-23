# // /d/changan/majiu.c 马厩

# inherit ROOM;
extends Room

func create():
	set("short","马厩");
	set("long",
"""这是客店后的马厩，常年供应新鲜草料。扬州民风淳朴，马夫们会
把马牵到马厩好生照看，将它们喂饱饮足，再洗刷得干乾净净，一直伺
候到客人上路。马厩雨檐下的烂木柱上钉着一块破木牌(paizi)。
    马厩中堆放著几堆草料，正中有一口泔槽。"""
);
	set("outdoors", "changan");
	set("no_fight", "1");
	set("no_beg", "1");
	set("no_clean_up", 0);
	set("objects", {
		"/d/city/npc/zaohongma": 1,
		"/d/city/npc/huangbiaoma": 1,
		"/d/city/npc/ziliuma": 1,
		"/clone/misc/mafu": 1,
	});
	set("item_desc", {
		"paizi":
"""客人们只要给马夫一两白银的租金就可以雇到一匹马了。

前往      扬州城:  rideyz
          伊犁镇:  rideyl"""
});
	set("exits",{
		"south" : __DIR__ + "kedian",
#		"up"    : SHOP_DIR + "changan_shop",
	});
	set("coor/x", -5060);
	set("coor/y", 1020);
	set("coor/z", 0);
	setup();
# 	replace_program(ROOM);
# }
