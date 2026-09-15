# // /d/changan/gulou.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "鼓楼");
	set_attr("long",  
"""鼓楼建于明洪武一十三年。青条石为基，青砖为楼，稳重厚实。门
楼内安放大鼓一张，相传当年天子在此击鼓点将，连洛阳都能听到。楼
前檐下悬挂蓝底金字木匾(bian)，和城中心的钟楼遥相呼应。"""
);
	set_attr("item_desc",  {
		"bian"  : """ 
        ********************************************
        *            文武盛地    声闻于天          *
        ********************************************
\n"""
	});
	set_attr("exits",  {
		"south"  :  __DIR__ + "westroad2",
	});
	set_attr("outdoors",  "changan");
	setup();
# 	replace_program(ROOM);
# }

