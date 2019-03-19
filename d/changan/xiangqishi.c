// /d/changan/xiangqishi.c
#include <ansi.h>
inherit  ROOM;
string lookjian();
void create ()
{
	set ("short", "适情雅趣屋");
	set ("long", @LONG
房间里很是雅致。当中一座大棋盘，棋盘上楚河汉界，将士跃马横
炮，《战国策·秦》云：“缀甲历兵，效胜于战场。”诚如是也。棋盘
边的小几上搁着一叠薛涛笺(jian)，密密麻麻写满不少东西，还有一些
好象是棋经(jing)歌诀(poem)之类的，抄录得很是整齐，想来颇值一读
(read)。宋·刘克庄《象弈一首呈叶潜仲》诗云：“小艺无难精，上智
有未解。君看橘中戏，妙不出局外。”何不领略一番？ 
    墙上贴了一张小帖子(tie)。
LONG);

	set("no_fight",  1);
	set("objects", ([ /* sizeof() == 4 */
		__DIR__"obj/chess" : 1,
	]));
	set("item_desc", ([ 
		"poem": HIY"\n	象棋歌诀\n\n"NOR,
		"jing": HIR"\n	棋经论\n\n"NOR,
		"tie":
"

下子        ：move <横座标> <纵座标> to <横座标> <纵座标>
重下        ：reset
读出残局    ：deploy
记录残局    ：csave
掷骰确定先行：toss
回顾        ：review
认输        ：lose
观看棋局    ：look或l board或ccb

",
		"jian": (: lookjian :)
	]));
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"club3",
	]));
	set("no_clean_up", 0);
	set("coor/x", -5020);
	set("coor/y", 1010);
	set("coor/z", 30);
	setup();
}
void init()
{
	add_action("do_read", "read");
}
int do_read(string arg)
{
	if (arg == "poem")
		this_player()->start_more(read_file(__DIR__"obj/chess_book"));
	else
	if (arg == "jing")
		this_player()->start_more(read_file(__DIR__"obj/chess_jing"));
	else
                return notify_fail("你要读什么？\n");
	return 1;
}
string lookjian()
{
        return
" 
                     以战争之象为棋戏

    回溯历史，春秋时的战争主要是车战，是四马拉的各种战车。
    战车纵聘于平原之上，却会受到不平坦地形的阻滞，而步兵则无论密草丛
林、丘陵险隘，……这些地带对战车是畏途，对步兵则无往而不利。所以到了
战国时期，步兵部队就庞大了起来，形成了以步兵部队为主体，配置以战车的
军队。骑兵的发展，自赵武王“胡服骑射”运动之后，从而使战术是形成步、
骑、车（即车马兵）的协同作战的战术联合体，使得战术组织复杂了许多。
    早期的象棋，在定型前除去无炮外，车、马、兵齐备，这与古代战争中的
兵种是一致的，尤其是五个兵卒，正好符合“五兵为伍”的战争中的战术组合
体。\n"+"
    象棋中的不同兵种协同联攻的战术组合体很多，举不胜举。诸如：五兵联
攻，可以形成“五卒擒王”之势；车马联攻，俗称“车马冷着”令受攻者防不
胜防；车炮联攻，能形成“夹车炮”、“滚地雷”以及抽将得子等有迅猛威肋
的杀势，等等。
    出棋制胜犹如将帅之立奇功，李白计曰：“剪虏若草收奇功！”（《送族
弟馆从军安西》）的机巧战术，精妙的胜局，使棋迷荡气回肠，如饮甘醴，回
味无穷，妙不可言，是一种超脱世俗的艺术享受！
";
}
