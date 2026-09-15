#// //  Room:  /d/changan/club3
#// inherit  ROOM;
extends Room

func  create():
	set_attr("short",  "聚义厅");
	set_attr("long", 
"""这是一间宽敞明亮的大厅，厅的正中间是一根圆形的柱子。柱子上
贴满了各种广告：有换房的，有卖家具的，但其中最多的还是找打牌搭
档的广告。厅的东南西北各有个门，里面传出“拱啊！”“毙了！”等
的叫声。"""
);

	set_attr("light_up",  1);
	set_attr("no_magic",  1);
	set_attr("no_fight",  1);
	set_attr("exits",  {
        "down":  __DIR__ + "clubpoem",
        "west":  __DIR__ + "majiang",
        "east":  __DIR__ + "xiangqishi",
        "south": __DIR__ + "qishi",
        "north": __DIR__ + "piggy",
    });
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -5030);
	set_attr("coor/y", 1010);
	set_attr("coor/z", 30);
	setup();
    # replace_program(ROOM);
