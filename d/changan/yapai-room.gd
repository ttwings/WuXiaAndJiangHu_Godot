# // /d/changan/yapai-room.c.

# inherit  ROOM;
extends Room

func create  ():
	set  ("short",  "押牌房");
	set  ("long", 
"""屋子中间放着一张白玉桌，桌后一张镶玉太师椅上坐着的就是庄家
了。你想和他玩玩么？那么，玩完你自个之前，想来还是先看看墙上钉
的牌子(paizi)吧。"""
);

	set("item_desc",  {"paizi"  :  """
押牌规则：
一，只允许一个个和庄家玩游戏。游戏名称叫二十一点。
二，先下注，至少一两银子，最多二十两黄金。下注方法就是直接把钱给庄家。
三，要下一张牌(deal)。直到爆破二十一点。
四，在没有爆破二十一点之前，可以亮牌(turn)。

注意事项：
一、相同点数时，庄家获胜。玩家以二十一点获胜时，获双倍赔偿。
二、A 可以作为一点计算，也可以做为十一点计算。J、Q、K 做十点计算。
三、本赌场对玩家的一切损失概不负责。
四、银票金票不适用此处。请勿使用，没收不赔。

		\n"""  });
	# //for  look  something.

	set("exits",  
	{
		"north"  :  __DIR__ + "clubpoem",
	});
	
	set("objects",  
	{
		"/d/city/npc/paitong"  :  1,
	});

	set("no_fight",  1);
	set("no_beg",  1);
	set("no_magic",  1);
	set("no_clean_up",  1);
	set("coor/x", -5030);
	set("coor/y", 1000);
	set("coor/z", 20);
	setup();
	# replace_program(ROOM);
