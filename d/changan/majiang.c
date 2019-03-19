// /d/changan/majiang.c

#include <ansi.h>
inherit ROOM;

void create ()
{
	set("short", "方城沙场");
	set("long", @LONG
这是一间麻将室，吵吵囔囔聚了一大堆人。房间中央是一张雕边釉
面方桌(table) ，每边都有一张红木锦垫雕背椅，坐(sit) 上去玩起麻
将来挺舒坦的。椅子边上都有一个小茶几，摆着吃的喝用的，大概几个
通宵不挪窝是没啥问题了。
    墙上贴了一张小帖子(tie)。
LONG);
	set("item_desc",  ([
		"tie" :
HIY"  指  令        例          子              说    明"HIC"
┌──────────────────────────┐
│sit          ----------                    坐下入局 │
│look  l mj或.看自己牌,l 1p或.1看玩家1的牌           │
│      l all或..看全部,l end看流局l dump。    看牌   │
│mo           ----------                      摸牌   │
│da             da <代码>。                   打牌   │
│chi           chi <代码1> <代码2>。          吃牌   │
│peng          ----------                     碰牌   │
│gang          gang 或 gang <代码>(暗杠用)。  杠牌   │
│hu                                           胡牌   │
│setmj          请看桌面。                  设定参数 │
│start        ----------                    牌局开始 │
│restart   restart 或 restart mj。          重新开始 │
│top   top aip,top -p,top -w,top -h,top -d           │
│      top -l看全部,-lw,-lh,-ld。            查资料  │
└──────────────────────────┘
"NOR,
		"table" : "
                       基  本  设  定
            setmj 可用的有自动胡、杠 、碰、听、显式方法。
--------------------------------------------------------------------
例子1: setmj peng 1w    设定会自动碰1w 当别人打出一万时会自动碰一万。
       setmj gang 1w    设定会自动杠1w 当别人打出一万时会自动杠一万。
       setmj tin 1w     设定会自动听1w 当别人打出一万时会自动胡一万。
例子2: setmj show 代码  设定为只显示代码。
       setmj show color 设定为彩色显示。
例子3: setmj tin none   取消会自动胡牌设定。
       setmj gang none  取消会自动杠牌设定。
       setmj peng none  取消会自动碰牌设定。
例子4: setmj auto tin   设定自动听牌。
--------------------------------------------------------------------
"
	]));
	set("exits", ([
		"east"  :  __DIR__"club3",
	]));

	set("objects", ([
		__DIR__"npc/matong"  :  1,
	]));

	set("no_fight",  1);
	set("no_beg",  1);
	set("no_steal", 1);
	set("no_clean_up",  1);
	set("coor/x", -5040);
	set("coor/y", 1010);
	set("coor/z", 30);
	setup();
}
