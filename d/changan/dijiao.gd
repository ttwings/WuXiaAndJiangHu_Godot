#// // /d/changan/dijiao.c
#
#// inherit  ROOM;
extends Room

func  create():
	set_attr("short",  "地窖");
	set_attr("long",  
"""满窖里漫着酒池，二百多个酒坛子都成了破瓷块，你终于明白停业
的原因了。原来田伯光要巴结令狐冲，从这抱走了两坛酒送上华山。临
走时见地窖中尚有二百余坛，心想长安城中的达官贵人、凡夫俗子，只
须腰中有钱，便能上‘谪仙楼’去喝到这样的美酒，又如何能显得华山
派令狐大侠的矫矫不群，与众不同？因此上乒乒乓乓，希里花拉，地窖
中酒香四溢，酒涨及腰。""");
	set_attr("exits",  {
		"up"  :  __DIR__ + "jiulou",
	});
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -5030);
	set_attr("coor/y", 1020);
	set_attr("coor/z", -10);
	setup();
	# replace_program(ROOM);
