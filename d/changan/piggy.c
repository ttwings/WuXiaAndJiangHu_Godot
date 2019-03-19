// /d/changan/piggy.c
/******************************************************************************/
//  inherit  and  include

#include  <ansi.h>
inherit  ROOM;

/******************************************************************************/
//  declare  global  variables.

//  cards  are  each  a  mapping  variable,  with  name,  status  (played?
//  in  hand?  on  table?  collected?),  worth,  misc  (pig?  sheep?  
//  blood?  doubler?).

mapping  *CARDS=({
([]),
([  "name":  HIB  "黑桃Ａ"  NOR,
	"suit":  "spade",
	"rank":  14,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃Ｋ"  NOR,
	"suit":  "spade",
	"rank":  13,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃Ｑ"  NOR,
	"suit":  "spade",
	"rank":  12,
	"status":  "undealt",
	"worth":  -10000,
	"misc":  "pig",
	]),
([  "name":  HIB  "黑桃Ｊ"  NOR,
	"suit":  "spade",
	"rank":  11,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃Ｔ"  NOR,
	"suit":  "spade",
	"rank":  10,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃９"  NOR,
	"suit":  "spade",
	"rank":  9,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃８"  NOR,
	"suit":  "spade",
	"rank":  8,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃７"  NOR,
	"suit":  "spade",
	"rank":  7,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃６"  NOR,
	"suit":  "spade",
	"rank":  6,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃５"  NOR,
	"suit":  "spade",
	"rank":  5,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃４"  NOR,
	"suit":  "spade",
	"rank":  4,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃３"  NOR,
	"suit":  "spade",
	"rank":  3,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "黑桃２"  NOR,
	"suit":  "spade",
	"rank":  2,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "红桃Ａ"  NOR,
	"suit":  "heart",
	"rank":  14,
	"status":  "undealt",
	"worth":  -5000,
	"misc":  "blood",
	]),
([  "name":  HIR  "红桃Ｋ"  NOR,
	"suit":  "heart",
	"rank":  13,
	"status":  "undealt",
	"worth":  -4000,
	"misc":  "",
	]),
([  "name":  HIR  "红桃Ｑ"  NOR,
	"suit":  "heart",
	"rank":  12,
	"status":  "undealt",
	"worth":  -3000,
	"misc":  "",
	]),
([  "name":  HIR  "红桃Ｊ"  NOR,
	"suit":  "heart",
	"rank":  11,
	"status":  "undealt",
	"worth":  -2000,
	"misc":  "",
	]),
([  "name":  HIR  "红桃Ｔ"  NOR,
	"suit":  "heart",
	"rank":  10,
	"status":  "undealt",
	"worth":  -1000,
	"misc":  "",
	]),
([  "name":  HIR  "红桃９"  NOR,
	"suit":  "heart",
	"rank":  9,
	"status":  "undealt",
	"worth":  -1000,
	"misc":  "",
	]),
([  "name":  HIR  "红桃８"  NOR,
	"suit":  "heart",
	"rank":  8,
	"status":  "undealt",
	"worth":  -1000,
	"misc":  "",
	]),
([  "name":  HIR  "红桃７"  NOR,
	"suit":  "heart",
	"rank":  7,
	"status":  "undealt",
	"worth":  -1000,
	"misc":  "",
	]),
([  "name":  HIR  "红桃６"  NOR,
	"suit":  "heart",
	"rank":  6,
	"status":  "undealt",
	"worth":  -1000,
	"misc":  "",
	]),
([  "name":  HIR  "红桃５"  NOR,
	"suit":  "heart",
	"rank":  5,
	"status":  "undealt",
	"worth":  -1000,
	"misc":  "",
	]),
([  "name":  HIR  "红桃４"  NOR,
	"suit":  "heart",
	"rank":  4,
	"status":  "undealt",
	"worth":  -1,
	"misc":  "",
	]),
([  "name":  HIR  "红桃３"  NOR,
	"suit":  "heart",
	"rank":  3,
	"status":  "undealt",
	"worth":  -1,
	"misc":  "",
	]),
([  "name":  HIR  "红桃２"  NOR,
	"suit":  "heart",
	"rank":  2,
	"status":  "undealt",
	"worth":  -1,
	"misc":  "",
	]),
([  "name":  HIR  "方片Ａ"  NOR,
	"suit":  "diamond",
	"rank":  14,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片Ｋ"  NOR,
	"suit":  "diamond",
	"rank":  13,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片Ｑ"  NOR,
	"suit":  "diamond",
	"rank":  12,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片Ｊ"  NOR,
	"suit":  "diamond",
	"rank":  11,
	"status":  "undealt",
	"worth":  10000,
	"misc":  "sheep",
	]),
([  "name":  HIR  "方片Ｔ"  NOR,
	"suit":  "diamond",
	"rank":  10,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片９"  NOR,
	"suit":  "diamond",
	"rank":  9,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片８"  NOR,
	"suit":  "diamond",
	"rank":  8,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片７"  NOR,
	"suit":  "diamond",
	"rank":  7,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片６"  NOR,
	"suit":  "diamond",
	"rank":  6,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片５"  NOR,
	"suit":  "diamond",
	"rank":  5,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片４"  NOR,
	"suit":  "diamond",
	"rank":  4,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片３"  NOR,
	"suit":  "diamond",
	"rank":  3,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIR  "方片２"  NOR,
	"suit":  "diamond",
	"rank":  2,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花Ａ"  NOR,
	"suit":  "club",
	"rank":  14,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花Ｋ"  NOR,
	"suit":  "club",
	"rank":  13,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花Ｑ"  NOR,
	"suit":  "club",
	"rank":  12,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花Ｊ"  NOR,
	"suit":  "club",
	"rank":  11,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花Ｔ"  NOR,
	"suit":  "club",
	"rank":  10,
	"status":  "undealt",
	"worth":  5000,
	"misc":  "doubler",
	]),
([  "name":  HIB  "草花９"  NOR,
	"suit":  "club",
	"rank":  9,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花８"  NOR,
	"suit":  "club",
	"rank":  8,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花７"  NOR,
	"suit":  "club",
	"rank":  7,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花６"  NOR,
	"suit":  "club",
	"rank":  6,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花５"  NOR,
	"suit":  "club",
	"rank":  5,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花４"  NOR,
	"suit":  "club",
	"rank":  4,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花３"  NOR,
	"suit":  "club",
	"rank":  3,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
([  "name":  HIB  "草花２"  NOR,
	"suit":  "club",
	"rank":  2,
	"status":  "undealt",
	"worth":  0,
	"misc":  "",
	]),
});

int  CARDNO=sizeof(CARDS)-1;

//  these  two  are  for  updating  the  table  when  players  play  cards.
//  if  they  want  to  see  the  whole  thing,  show  FULL,  otherwise  show
//  SHORT,  difference  being  short  is  only  cards  on  table,  and  full
//  is  those  sold  and  those  played.

string  COLLECT_STATE  =  "
%s

　　　　　　　　　"+HIC+"%|12s"+NOR+"
　　　　　　　┌────────┐
　　　　　　　│　　　　　│
　　　　　　　│　　　　　　　　│
　　　　　　　│　　　　　　　　│
　"+HIC+"%+12s"+NOR+"│　　│"+HIC+"%-12s"+NOR+"
　　　　　　　│　　　　　　　　│
　　　　　　　│　　　　　　　　│
　　　　　　　│　　　　　│
　　　　　　　└────────┘
　　　　　　　　　"+HIC+"%|12s"+NOR+"

";

string  PIGSTATE_FULL  =  "
%s

　　　　　　　　　　"+HIC+"%|12s"+NOR+"
　　　　　　　　┌────────┐
　　　　　　　　│%s│
　　　　　　┌─┼────────┼─┐
　　　　　　│%2s│　　  %6s  　　│%2s│
　　　　　　│　│　　　　　　　　│　│
　　　　　　│%2s│　　　　　　　　│%2s│
"+HIC+"%+12s"+NOR+"│　│%6s　　%6s│　│"+HIC+"%-12s"+NOR+"
　　　　　　│%2s│　　　　　　　　│%2s│
　　　　　　│　│　　　　　　　　│　│
　　　　　　│%2s│　　  %6s  　　│%2s│
　　　　　　└─┼────────┼─┘
　　　　　　　　│%s│
　　　　　　　　└────────┘
　　　　　　　　　　"+HIC+"%|12s"+NOR+"

";

string  PIGSTATE_SHORT  =  "
%s

　　　　　　　　　"+HIC+"%|12s"+NOR+"
　　　　　　　┌────────┐
　　　　　　　│　　  %6s  　　│
　　　　　　　│　　　　　　　　│
　　　　　　　│　　　　　　　　│
　"+HIC+"%+12s"+NOR+"│%6s　　%6s│"+HIC+"%-12s"+NOR+"
　　　　　　　│　　　　　　　　│
　　　　　　　│　　　　　　　　│
　　　　　　　│　　  %6s  　　│
　　　　　　　└────────┘
　　　　　　　　　"+HIC+"%|12s"+NOR+"

";

string*  DIR=({  "east",  "north",  "west",  "south",});
string*  SUIT=({"spade",  "heart",  "diamond",  "club",});
int  LIMIT  =  -5000;
mapping  CSUIT=([
"spade":  HIB"黑桃"NOR,
"heart":  HIR"红桃"NOR,
"diamond":  HIR"方片"NOR,
"club":  HIB"草花"NOR,
]);

mapping  CDIR  =  ([
"east"  :  "东",
"north":  "北",
"west"  :  "西",
"south":  "南",
]);

mapping  SCARD=([
"pig":  HIB,
"blood":  HIR,
"sheep":  HIR,
"doubler":  HIB,
]);
mapping  NCARD=([
"pig":  3,
"blood":  14,
"sheep":  30,
"doubler":  44,
]);
mapping  CCARD=([
"pig":  "猪（"+HIB+"黑桃Ｑ"+NOR+"）",
"sheep":  "羊（"+HIR+"方片Ｊ"+NOR+"）",
"doubler":  "变压器（"+HIB+"草花Ｔ"+NOR+"）",  
"blood":  "血（"+HIR+"红桃Ａ"+NOR+"）",
]);

string  *CNUM  =  ({"？",  "１",  "２",  "３",  "４",  "５",  "６",
"７",  "８",  "９",  "Ｔ",  "Ｊ",  "Ｑ",  "Ｋ",  "Ａ",  });

int  NUM  =  4;
/******************************************************************************/
//  following  will  change.

//  game  info...

mapping  GAMEINFO=([
"round":  0,
"rlead":"",
"next":"",
"suit":"",
"spade":  0,
"heart":  0,
"diamond":  0,
"club":  0,
]);

string  PIG_OWNER="";

mapping  SCORING=([
"sitting":  ([      "east":  0,
		"west":  0,
		"south":  0,
		"north":  0,  ]),
"hand"      :  ([      "east":  0,
		"west":  0,
		"south":  0,
		"north":  0,  ]),
]);

//  indicate  who  collect  all.
string  FULL="";
string  *PIGHEAD=({});

mapping  CLAIM=([
"claimer":  "",
"east":  "no",
"west":  "no",
"north":  "no",
"south":  "no",
]);

//  possible  states:  "等人",  "等发牌",  "等卖牌",  "出牌",  "算分",  

mapping  TABLE=([
"cond":  "等人",
"east":([  "player_name":  "「空」",
	    "player_id":  "no  one",
	    "status":  "empty",
	    "collected":  ({}),
	    "sold":  ({}),
	    "card":  0,  ]),
"north":([  "player_name":  "「空」",
	    "player_id":  "no  one",
	    "status":  "empty",
	    "collected":  ({}),
	    "sold":  ({}),
	    "card":  0,  ]),
"west":([  "player_name":  "「空」",
	    "player_id":  "no  one",
	    "status":  "empty",
	    "collected":  ({}),
	    "sold":  ({}),
	    "card":  0,  ]),
"south":([  "player_name":  "「空」",
	    "player_id":  "no  one",
	    "status":  "empty",
	    "collected":  ({}),
	    "sold":  ({}),
	    "card":  0,  ]),
]);

mapping  SOLD=([
"pig":  ({"not"}),
"blood":  ({"not"}),
"sheep":  ({"not"}),
"doubler":  ({"not"}),
]);


object  HERE=this_object();

/******************************************************************************/
//  declare  functions.

object  find_me(string  dir);

string  treat_sold(string  sold,  int  cnt);
string  sold_display(string  dir,  int  index,  int  flag);
string  display_table(string  cond);
string  look_table();
string  read_rules();
string  look_hand();
string  look_collected();
string  check_collected(string  dir,  string  suit);
string  table_cond();
string  card_suit(string  arg);
string  search_my_dir(object  me);
string  display_suit(string  dir,  string  suit);
string  next_player(string  dir);
string  find_large();
string  display_score();
string  look_note();
string  display_sell();

void  finish_round();
void  renew(string  type);

int  score_player(string  dir);
int  card_numb(string  card);
int  card_rank(string  arg);
int  is_empty(string  dir);
int  is_my_card(object  me,  int  cardno);
int  is_sellable(int  cardno);
int  is_dir(string  dir);
int  is_suit(string  suit);
int  in_table(object  me);
int  is_playable(object  me,  int  cardno);
int  search_suit(object  me,  string  suit);
int  all_have(string  arg);
int  deal_cards(string  dir);
int  display_cards(object  player);

/******************************************************************************/
void  create  ()
{
    set  ("short",  "拱猪房");
    set  ("long",  @LONG
这间房子是专门为了拱猪用而设的，整间屋子都是用不去皮的松树
搭成。一张石桌 (table)周围摆着四个石礅，桌面镶了一块大理石，摸
上去极为光滑。四壁挂着长明灯，把屋子照得有如白昼。墙角里烧了一
炉不知名的香，似乎颇有提神之效。香炉旁边挂着张告示(gaoshi)，上
面写着这里的规矩；桌上有张小纸条(note)，上面草草的记着拱猪成绩。
LONG);

    set("exits",  ([
	"south":  __DIR__"club3",
    ])  );
    set("item_desc",  ([
	"table":	(:  look_table  :),
	"gaoshi":	(:  read_rules  :),
	"hand":		(:  look_hand  :),
	"collected":	(:  look_collected  :),
	"note":		(:  look_note  :),
    ])  );
    set("no_clean_up",  1);
    set("no_fight",  1);
    set("no_magic",  1);

	set("coor/x", -5030);
	set("coor/y", 1020);
	set("coor/z", 30);
	setup();
}
/******************************************************************************/
//  init,  add  action.

void  init()
{
        add_action("do_leave",  "leave");
        add_action("do_leave",  "likai");
        add_action("do_leave",  "离开");
        add_action("do_sit",  "sit");
        add_action("do_sit",  "zuo");
        add_action("do_sit",  "坐");
        add_action("do_deal",  "deal");
        add_action("do_deal",  "fapai");
        add_action("do_deal",  "发牌");
        add_action("do_sell",  "sell");
        add_action("do_sell",  "liang");
        add_action("do_sell",  "亮");
        add_action("do_pass",  "pass");
        add_action("do_pass",  "tingmai");
        add_action("do_pass",  "停卖");
        add_action("do_play",  "play");
        add_action("do_play",  "da");
        add_action("do_play",  "打");
        add_action("do_claim",  "claim");
        add_action("do_cast",  "cast");
        add_action("do_exert",  "exert");
        add_action("do_perform",  "perform");
        add_action("do_xiudao",  "xiudao");
        add_action("do_check",  "check");
        add_action("do_find",  "find");
        add_action("do_bian",  "bian");
        add_action("do_get",  "get");
        add_action("do_practice",  "practice");
        add_action("do_read",  "read");
        add_action("do_study",  "study");
        add_action("do_learn",  "learn");
        add_action("do_steal",  "steal");
        add_action("do_fight",  "fight");
        add_action("do_kill",  "kill");
        add_action("do_quit",  "quit");
        add_action("do_exercise",  "exercise");
        add_action("do_meditate",  "meditate");

        return;
}
/******************************************************************************/
int  valid_leave(object  me,  string  dir)
{
        if  (in_table(me))
	return  notify_fail("对不起，你现在在拱猪，就这么走掉不太好吧？\n");
        return  ::valid_leave(me,  dir);
}
int  do_quit(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里离开游戏，谢谢。\n");
        return  1;
}
int  do_steal(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里偷东西，谢谢。\n");
        return  1;
}
int  do_fight(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里打架，谢谢。\n");
        return  1;
}
int  do_kill(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里杀戮，谢谢。\n");
        return  1;
}
int  do_exercise(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里练功，谢谢。\n");
        return  1;
}
int  do_meditate(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里修炼，谢谢。\n");
        return  1;
}
int  do_get(string  arg)
{
        object  ob;
        string  thing,  person;

        sscanf(arg,  "%s  from  %s",  thing,  person);
        if  (!person)  person=arg;
        if  (ob=present(person,  this_object()))
	if(userp(ob))
	{
	        tell_object(this_player(),  "请不要占别人的便宜，谢谢。\n");
	        return  1;
	}
        return  0;
}
int  do_cast(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里施用法术，谢谢。\n");
        return  1;
}
int  do_exert(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里施用内功，谢谢。\n");
        return  1;
}
int  do_perform(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里施用外功，谢谢。\n");
        return  1;
}
int  do_xiudao(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里修道，谢谢。\n");
        return  1;
}
int  do_check(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里查别人的功夫，谢谢。\n");
        return  1;
}
int  do_find(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里查别人的踪迹，谢谢。\n");
        return  1;
}
int  do_bian(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里变来变去，谢谢。\n");
        return  1;
}
int  do_practice(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里练功，谢谢。\n");
        return  1;
}
int  do_read(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里读书，谢谢。\n");
        return  1;
}
int  do_study(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里读书，谢谢。\n");
        return  1;
}
int  do_learn(string  arg)
{
        tell_object(this_player(),  "请不要在拱猪房里学习，谢谢。\n");
        return  1;
}
/******************************************************************************/
int  is_suit(string  suit)
{

        if  (member_array(suit,  SUIT)  ==  -1)
	return  0;
        return  1;
}
int  is_dir(string  dir)
{

        if  (member_array(dir,  DIR)  ==  -1)
	return  0;
        return  1;
}
int  is_empty(string  dir)
{
        if(TABLE[dir]["player_id"]  ==  "no  one")
	return  1;
        if(!present(TABLE[dir]["player_id"],  HERE))
        {
	TABLE[dir]["player_id"]="no  one";
	return  1;
        }
        return  0;
}
int  is_my_card(object  me,  int  cardno)
{
        if(CARDS[cardno]["status"]  !=  search_my_dir(me))
	return  0;
        return  1;
}
object  search_dir(string  dir)
{
        return  present(TABLE[dir]["player_id"],  HERE);
}
string  card_suit(string  arg)
{
        string  card=capitalize(arg);

        switch  ((string)card[0..0])
        {
	case  "S":
	        return  "spade";
	case  "H":
	        return  "heart";
	case  "D":
	        return  "diamond";
	case  "C":
	        return  "club";
	default:
	        return  "花色错误：card_suit。\n";
        }
}
int  card_rank(string  card)
{
        int  i=strlen(card)-1;

        switch  ((string)card[i..i])
        {
	case  "2":
	        return  2;
	case  "3":
	        return  3;
	case  "4":
	        return  4;
	case  "5":
	        return  5;
	case  "6":
	        return  6;
	case  "7":
	        return  7;
	case  "8":
	        return  8;
	case  "9":
	        return  9;
	case  "T":
	case  "t":
	        return  10;
	case  "J":
	case  "j":
	        return  11;
	case  "Q":
	case  "q":
	        return  12;
	case  "K":
	case  "k":
	        return  13;
	case  "A":
	case  "a":
	        return  14;
	default:
	        return  notify_fail("无法理解输入的牌，"+card+"。请重新输入。\n");
        }
}
int  card_numb(string  card)
{
        int  base,  rank;
        string  suit;
        if  (!(suit=card_suit(card))  ||  !(rank=card_rank(card)))
	return  notify_fail("函数错误：card_numb。\n");
        switch  (suit)
        {
	case  "spade":
	        base=1;
	        break;
	case  "heart":
	        base=14;
	        break;
	case  "diamond":
	        base=27;
	        break;
	case  "club":
	        base=40;
	        break;
	default:
	        return  notify_fail("函数错误：card_numb。\n");
        }
        return  (base+15-rank);
}
int  is_sellable(int  cardno)
{
        switch(cardno)
        {
	case  3:
	case  14:
	case  30:
	case  44:
	        return  1;
	default:
	        return  0;
        }
}
/******************************************************************************/

int  is_playable(object  me,  int  cardno)
{
        string  dir=search_my_dir(me),  suit;

        if  (!is_my_card(me,  cardno))
        {
	tell_object(me,  "对不起，"+CARDS[cardno]["name"]+"不在你手里。\n");
	return  0;
        }
        if  (dir==GAMEINFO["rlead"])
	if  (!is_sellable(cardno))
	        return  1;
        suit=CARDS[cardno]["suit"];
        if  (suit  !=  GAMEINFO["suit"]
          &&  search_suit(me,  GAMEINFO["suit"]))
        {
	tell_object(me,  "对不起，你手中还有"+CSUIT[GAMEINFO["suit"]]+"，不能出"+CARDS[cardno]["name"]+"。\n");
	return  0;
        }
        if  (!GAMEINFO[CARDS[cardno]["suit"]]
          &&  is_sellable(cardno))
        {
	if  (SOLD[CARDS[cardno]["misc"]][0]  ==  "m"
                  &&  search_suit(me,  (GAMEINFO["suit"]  ==  ""?CARDS[cardno]["suit"]:GAMEINFO["suit"]))  >  1)
	{
	        tell_object(me,"对不起，明卖了的牌不能在本花色第一轮出。\n");
	        return  0;
	}
        }
        return  1;
}
int  in_table(object  me)
{
        int  i=NUM;
        string  id=me->query("id");

        while(i--)
        {
	if  (id  ==  TABLE[DIR[i]]["player_id"])
	{
	        me->set_temp("piggy/seating",  DIR[i]);
	        return  1;
	}
	continue;
        }
        return  0;
}

string  search_my_dir(object  me)
{
        int  i=NUM;
        string  id=me->query("id");

        while(i--)
        {
	if  (id  ==  TABLE[DIR[i]]["player_id"])
	        return  DIR[i];
	continue;
        }
        return  "none";
}
/******************************************************************************/
//  do_sit,  to  enter  the  table.

int  do_sit(string  dir)
{
        object  me=this_player(),  pl;

        if(!is_dir(dir))
	return  notify_fail("请选择「east、north、south  或  west」。\n");
        if(in_table(me))
	return  notify_fail("你已经在座了。请用「leave」站起来。\n");
        if  (!is_empty(dir))
	return  notify_fail(search_dir(dir)->query("name")+"正在"+CDIR[dir]+"边坐着呢，你还是等空位吧。\n");
        me->set_temp("piggy/seating",  dir);
        TABLE[dir]["player_id"]=me->query("id");
        TABLE[dir]["player_name"]=me->query("name");
        TABLE[dir]["status"]="filled";
        if  (all_have("players"))
	TABLE["cond"]="等发牌";
        message_vision("$N坐入了"+CDIR[dir]+"边的空位。\n",  me);
        return  1;
}
/******************************************************************************/
//  do_leave,  to  leave  the  table.

int  do_leave(string  arg)
{
        string  dir;
        object  me=this_player();

        if  (!in_table(me))
	return  notify_fail("对不起，你并没在拱猪桌边坐着。\n");
        dir  =  search_my_dir(me);
        if  (is_empty(dir)  ||  search_dir(dir)  !=  me)
	return  notify_fail("函数错误：do_leave。请告诉酸黄瓜。\n");
        me->delete_temp("piggy/seating",  dir);
        TABLE[dir]["status"]="empty";
        TABLE[dir]["player_name"]="「空」";
        TABLE[dir]["player_id"]="no  one";
        TABLE["cond"]="等人";
        renew("all");
        message_vision("$N让出了"+CDIR[dir]+"边的位置，不打算拱下去了。\n",  me);
        return  1;
}
/******************************************************************************/
//  players  declare  dealing.

int  do_deal(string  arg)
{
        int  i  =  NUM,  cnt,  j;
        object  me=this_player();
        string  dir  =  search_my_dir(me);
        string  *name  =  ({}),  dir2,  str;

        if  (dir  ==  "none")
        {
	me->delete_temp("piggy/seating");
	return  notify_fail("对不起，你没有入座，无法要求发牌。\n");
        }
        if  (!all_have("players"))
	return  notify_fail("还没凑齐四个人，没法开牌局。\n");
        if  (TABLE[dir]["status"]  ==  "asked_for_deal"  &&  TABLE["cond"]  ==  "等人")
        {
	while(i--)
	{
	        dir2  =  DIR[i];
	        if  (TABLE[dir2]["status"]  !=  "asked_for_deal")
		name  +=  ({TABLE[dir2]["player_name"]});
	        continue;
	}
	j  =  sizeof(name);
	switch  (j)
	{
	        case  1:  str  =  name[0];  break;
	        case  2:  str  =  name[0]+"和"+name[1];break;
	        case  3:  str  =  name[0]+"、"+name[1]+"和"+name[2];  break;
	        default:  tell_room(HERE,  "函数错误：发牌。请告诉酸黄瓜。\n");  break;
	}
	return  notify_fail("对不起，"+str+"还没准备好呢。\n");
        }
        if  (TABLE[dir]["status"]  !=  "filled"  ||  TABLE["cond"]  !=  "等发牌")
	return  notify_fail("对不起，现在不是发牌的时候。\n");
        TABLE[dir]["status"]="asked_for_deal";
        message_vision("$N说道：我准备好了，发牌吧。\n",  me);
        if  (all_have("req_deal"))
        {
	message_vision("\n大家都准备好了，由$N负责发牌。\n\n",  me);
	TABLE["cond"]="等卖牌";
	deal_cards("east");
	deal_cards("north");
	deal_cards("west");
	deal_cards("south");
	if  (!is_dir(GAMEINFO["rlead"]))
	        GAMEINFO["rlead"]=search_my_dir(me);
	tell_room(HERE,  "请用「sell」卖牌，「pass」停卖。\n");
        }
        return  1;
}
/******************************************************************************/
//  do_sell,  for  selling  cards  of  course.

int  do_sell(string  arg)
{
        object  me=this_player();
        string  dir;
        string  card,  flag="a",  suit;
        int  rank,  index;

        if(!in_table(me))
	return  notify_fail("对不起，你并不在拱猪。\n");
        if(TABLE["cond"]  !=  "等卖牌")
	return  notify_fail("对不起，现在不能卖牌。\n");
        dir=search_my_dir(me);
        if(TABLE[dir]["status"]  ==  "passed")
	return  notify_fail("对不起，你已经决定停卖了。\n");
        if(!arg)
	return  notify_fail("请用  sell  [-m]  <card>  来卖牌。\n");
        if  (sscanf(arg,  "-%s  %s",  flag,  card)  !=  2)
	card=arg;
        else  if  (flag  !=  "m")
	return  notify_fail("对不起，只能选择  [-m]。\n");
        if  (!(index=card_numb(card)))
	return  notify_fail("对不起，「"+card+"」并不是一张牌。\n");
        index--;
        if  (!is_my_card(me,  index))
	return  notify_fail("对不起，"+CARDS[index]["name"]+"不在你手里。\n");
        if(!is_sellable(index))
	return  notify_fail("对不起，只能卖猪（黑桃Ｑ）、羊（方片Ｊ）、变压器（草花Ｔ）或血（红桃Ａ）。\n");
        card=CARDS[index]["misc"];
        SOLD[card]=({flag,  (dir=search_my_dir(me))});
        if  (member_array(card,  TABLE[dir]["sold"])  ==  -1)
	TABLE[dir]["sold"]+=({card});
        tell_object(me,  "你决定"+(flag=="a"?"暗":"明")+"卖"+CCARD[card]+"。\n");
        return  1;
}

int  do_claim(string  arg)
{
        object  me=this_player();
        string  dir=search_my_dir(me),  str,  claimer;
        int  i=NUM,j=CARDNO+1;

        if  (TABLE["cond"]  !=  "出牌")
	return  notify_fail("对不起，现在并不在出牌。\n");
        switch(arg)
        {
	case  "all":
	        if  (dir  ==  CLAIM["claimer"])
		return  notify_fail("你已经发出要求，请等别人的回音。\n");
	        if  (CLAIM["claimer"]  !=  "")
		return  notify_fail("已经有人发出要求了，请先否决。\n");
	        CLAIM[dir]="yes";
	        CLAIM["claimer"]  =  dir;
	        str  =  "$N认为自己手中的牌都大了：\n";
	        str  +=  display_suit(dir,  "spade");
	        str  +=  display_suit(dir,  "heart");
	        str  +=  display_suit(dir,  "diamond");
	        str  +=  display_suit(dir,  "club");
	        str  +=  "\n请用「yes」表示同意，「no」表示反对。\n";
	        message_vision(str,  me);
	        break;
	case  "yes":
	        if  (CLAIM["dir"]  ==  "yes")
		return  notify_fail("你已经同意了。\n");
	        if  (!is_dir(CLAIM["claimer"]))
		return  notify_fail("对不起，没人要求摊牌。\n");
	        CLAIM[dir]="yes";
	        message_vision("$N摊牌道：我同意。\n",  me);
	        if  (all_have("agreed_claim"))
	        {
		while  (i--)
		{
		        if  (TABLE[DIR[i]]["card"]!=0)
		        {
			TABLE[CLAIM["claimer"]]["collected"]  +=
			        ({TABLE[DIR[i]]["card"]});
		                TABLE[CLAIM["claimer"]]["card"]  =  0;
		        }
		}
		while(j--)
		{
		        if  (is_dir(CARDS[j]["status"]))
		        {
			TABLE[CLAIM["claimer"]]["collected"]  +=  ({j});
			CARDS[j]["status"]  =  "played";
			if  (j==3)
			{
			        tell_room(HERE,HIB+TABLE[CLAIM["claimer"]]["player_name"]+"吃了猪头！\n"+NOR);
			        PIG_OWNER=CLAIM["claimer"];
			}
		        }
		        continue;
		}
	  	GAMEINFO["round"]=13;
		finish_round();
	        }
	        break;
	case  "no":
	        if  (!is_dir(CLAIM["claimer"]))
		return  notify_fail("对不起，没有人要求摊牌。\n");
	        message_vision("$N不同意，请继续打下去。\n",  me);
	        while  (i--)
		CLAIM[DIR[i]]  =  "no";
	        CLAIM["claimer"]  =  "";
	        break;
	default:
	        return  notify_fail("请用「all」表示你想全收，「yes」表示同意，「no」表示反对。\n");
	        break;
        }
        return  1;
}

int  do_pass(string  arg)
{
        object  me=this_player();
        string  dir=search_my_dir(me),  str;

        if  (!in_table(me))
	return  notify_fail("对不起，你并不在拱猪。\n");
        if  (TABLE["cond"]  !=  "等卖牌")
	return  notify_fail("对不起，现在不能卖牌或停卖。\n");
        if  (TABLE[dir]["status"]=="passed")
	return  notify_fail("你已经决定停卖了。\n");
        TABLE[dir]["status"]="passed";
        message_vision("$N说道：我停卖。\n",  me);
        if  (all_have("pass"))
        {
	TABLE["cond"]="出牌";
	GAMEINFO["round"]=1;
	str  =  "\n大家都停卖了，";
	str  +=  display_sell();
	str  +=  "\n一切就绪，开拱！\n";
	str  +=  "这把由"+TABLE[GAMEINFO["rlead"]]["player_name"]+"先出！\n\n";
	GAMEINFO["next"]=GAMEINFO["rlead"];
	tell_room(HERE,  str);
        }
        return  1;
}
int  do_play(string  card)
{
        object  me=this_player();
        int  numb;

        if  (!in_table(me))
	return  notify_fail("对不起，你并不在拱猪。\n");
        if  (!card)
	return  notify_fail("请用  play  <card>  出牌。\n");
        if  (TABLE["cond"]  !=  "出牌")
	return  notify_fail("对不起，现在不能出牌。\n");
        if  (GAMEINFO["next"]  !=  search_my_dir(me))
	return  notify_fail("对不起，现在不该你出牌。\n");
        if  (is_dir(CLAIM["claimer"]))
	return  notify_fail("对不起，请等到"+TABLE[CLAIM["claimer"]]["player_name"]+"的全收要求有结果后再出牌。\n");
        if  (!(numb=card_numb(card)))
	return  notify_fail("对不起，无法分辨  "+card+"。\n");
        numb--;
        if  (!is_playable(me,  numb))
	return  1;

        CARDS[numb]["status"]="played";
        TABLE[GAMEINFO["next"]]["card"]=numb;
        if  (GAMEINFO["next"]  ==  GAMEINFO["rlead"])
	GAMEINFO["suit"]=CARDS[numb]["suit"];
        if  (!is_sellable(numb))
	message_vision("$N"+(CARDS[numb]["suit"]  ==  GAMEINFO["suit"]?"出":"垫")
		+"了一张"+CARDS[numb]["name"]+"。\n",  me);
        else  if(SOLD[CARDS[numb]["misc"]][0]  !=  "not")
	message_vision(  "$N出"  +  (SOLD[CARDS[numb]["misc"]][0]=="m"  ?
		"明"  :  "暗")  +  "卖的"+CARDS[numb]["name"]+"！\n",  me);
	else  message_vision("$N"+(CARDS[numb]["suit"]  ==  GAMEINFO["suit"]?
		"出":"垫")  +"了一张"+CARDS[numb]["name"]+"。\n",  me);
        if(all_have("cards"))
	finish_round();
        else  GAMEINFO["next"]=next_player(GAMEINFO["next"]);
        if  (is_dir(GAMEINFO["next"]))
	tell_room(HERE,  "下面该由"+TABLE[GAMEINFO["next"]]["player_name"]+"出牌。\n");
        return  1;
}
/******************************************************************************/
object  find_me(string  dir)
{
        object  player;
        string  id=TABLE[dir]["player_id"];

        if  (!(player=present(id,  HERE)))
        {
	tell_room(HERE,  TABLE[dir]["player_name"]+"不在房间里！\n");
	tell_room(HERE,  "清理房间中……\n");
	renew("all");
	tell_room(HERE,  "请重新凑人！\n");
        }

        return  player;
}
int  score_player(string  dir)
{
        int  score,  tscore=0,  *collected=TABLE[dir]["collected"],  i=13,  j,  full=0;
        object  player;

//  do  hearts  first;

        while(i--)
        {
	j  =  i+14;
	if(member_array(j,  collected)  ==  -1)
	        continue;
	score+=CARDS[j]["worth"];
	collected-=({j});
	continue;
        }
        if  (score==-20003)
        {
	score  =  20000;
	full  =  1;
        }
//        else  score  =  (score  /  10)  *  10;
//        tell_room(HERE,  "so  far  after  hearts  score  is  "+score+"\n");
        if  (SOLD["blood"][0]  ==  "m")  score  =  score  *  4;		//  明卖
        else  if  (SOLD["blood"][0]  ==  "a")  score  =  score  *  2;	//  暗卖

//  then  pig.  the  rules  i  go  by  are  that  if  收全红，猪变正。

        if  (member_array(3,  collected)  !=  -1)
        {
	if  (SOLD["pig"][0]=="m")  tscore  =  4*CARDS[3]["worth"];
	else  if  (SOLD["pig"][0]=="a")  tscore  =  2*CARDS[3]["worth"];
	else  tscore  =  CARDS[3]["worth"];
	collected  -=  ({3});
	if  (full)  score=score-tscore;
	else  score  +=  tscore;
        }
        else  full  =  0;
//        tell_room(HERE,  "so  far  after  pig  score  is  "+score+"\n");
        

//  then  sheep.
        if  (member_array(30,  collected)  !=  -1)
        {
	score  =  score  /  100  *  100;
                if  (SOLD["sheep"][0]=="m")  tscore  =  4*CARDS[30]["worth"];
                else  if  (SOLD["sheep"][0]=="a")  tscore  =  2*CARDS[30]["worth"];
	else  tscore  =  CARDS[30]["worth"];
                collected  -=  ({30});
	score  +=  tscore;
        }
        else  full  =  0;
//        tell_room(HERE,  "so  far  after  sheep  score  is  "+score+"\n");

//  then  doubler.
        if  (member_array(44,  collected)  !=  -1)
        {
                if  (SOLD["doubler"][0]=="m")  tscore  =  8;
                else  if  (SOLD["doubler"][0]=="a")  tscore  =  4;
	else  tscore  =  2;
                collected  -=  ({44});
	if  (score  ==  0)  score  =  tscore  *  CARDS[44]["worth"]/2;
	else
	{
	        score  =  (score/1000)*1000;
	        score  =  score  *  tscore;
	}
        }
        else  full=0;
        if  (full)  FULL=dir;
        else  FULL="";

        return  score/100;
}
string  find_large()
{
        mapping  card,  lcard;
        string  dir;
        int  i=NUM,  mark=0;

        if  (is_dir(CLAIM["claimer"]))
	return  CLAIM["claimer"];
        dir=GAMEINFO["rlead"];
        while(i--)
        {
	lcard=CARDS[TABLE[dir]["card"]];
	card=CARDS[TABLE[DIR[i]]["card"]];
	if  (card["misc"]  ==  "pig")
	        mark  =  1;
	if  (card["suit"]==GAMEINFO["suit"]  &&  card["rank"]>lcard["rank"])
	        dir=DIR[i];
	continue;
        }
        i=NUM;
        while(i--)
        {
	TABLE[dir]["collected"]+=({TABLE[DIR[i]]["card"]});
	continue;
        }
        if  (mark)
        {
	PIG_OWNER=dir;
	tell_room(HERE,  HIB+TABLE[dir]["player_name"]+"吃了猪头！\n"NOR);
        }
        return  dir;
}
void  finish_round()
{
        int  i=NUM,  j=CARDNO,  score,  k;
        string  dir=find_large();
        object  me;

        if  (GAMEINFO["round"]  ==  13)
        {
	TABLE["cond"]  =  "算分";
	while(j--)
	{
	        if  (CARDS[j+1]["status"]  !=  "played")
		tell_room(HERE,"函数错误：finish_round。"+CARDS[j+1]["name"]+"还没打过。\n");
	        continue;
	}
	score_player(PIG_OWNER);
	if  (!is_dir(FULL))
  	    while(i--)
	    {
	        score=score_player(DIR[i]);
	        me=find_me(DIR[i]);
	        me->add("piggy/score",  score);
	        me->add("piggy/hand_played",  1);
	        SCORING["hand"][DIR[i]]+=score;
	        if  ((SCORING["sitting"][DIR[i]]+=score)  <  LIMIT)
		PIGHEAD+=({DIR[i]});
	        continue;
	    }
	else
	        while(i--)
	        {
		(me=find_me(DIR[i]))->add("piggy/hand_played",  1);
		if(FULL  !=  DIR[i])
		{
		        PIGHEAD+=({DIR[i]});
		        continue;
		}
		me->add("piggy/score",  score=score_player(FULL));
		SCORING["hand"][FULL]+=score;
		SCORING["sitting"][FULL]+=score;
		continue;
	        }
	if  (k=sizeof(PIGHEAD))
	        while(k--)
		find_me(PIGHEAD[k])->add("piggy/head_received",  1);
	tell_room(HERE,  display_score());
	if  (sizeof(PIGHEAD))
	{
	        all_have("given_head");
	        renew("sitting");
	}
	else  renew("hand");
	return;
        }
        GAMEINFO[GAMEINFO["suit"]]++;
        GAMEINFO["rlead"]=dir;
        GAMEINFO["next"]=dir;
        find_me(dir);
        tell_room(HERE,  display_table(dir));
        renew("round");
        return;
}
string  next_player(string  dir)
{
        switch  (dir)
        {
	case  "east":
	        return  "north";
	case  "north":
	        return  "west";
	case  "west":
	        return  "south";
	case  "south":
	        return  "east";
	default:
	        return  "函数错误：next_player。\n";
        }
}
int  deal_cards(string  dir)
{
        int  j  =  CARDNO  /  4;
        mapping  card=([]);

        while  (j--)
        {
	card  =  CARDS[random(CARDNO)+1];
	if  (card["status"]!="undealt")
	{
	        j++;
	        continue;
	}
	card["status"]=dir;
	continue;
        }
        display_cards(search_dir(dir));
        return  1;
}

int  display_cards(object  player)
{
        string  str,  dir=search_my_dir(player);

        str  =  "你手中的牌如下：\n";
        str  +=  display_suit(dir,  "spade");
        str  +=  display_suit(dir,  "heart");
        str  +=  display_suit(dir,  "diamond");
        str  +=  display_suit(dir,  "club");
        tell_object(player,  str+"\n\n");
        return  1;
}
string  check_collected(string  dir,  string  suit)
{
        string  str="",  toreturn;
        int  size  =  sizeof(TABLE[dir]["collected"]),  i  =  13,  count,  base;

        if  (!size)
	return  "";
        switch  (suit)
        {
	case  "spade":
	        str  +=  "\n　　"+HIB"黑桃："NOR;
	        base=1;
	        break;
	case  "heart":
	        str  +=  "\n　　"+HIR"红桃："NOR;
	        base=14;
	        break;
	case  "diamond":
	        str  +=  "\n　　"+HIR"方片："NOR;
	        base=27;
	        break;
	case  "club":
	        str  +=  "\n　　"+HIB"草花："NOR;
	        base=40;
	        break;
	default:
	        return  "函数错误：display_suit。\n";
        }
        while  (i--)
        {
	if  (member_array((i+base),  TABLE[dir]["collected"])  !=  -1
	  &&  CARDS[i+base]["worth"]  !=  0)
	{
	        count++;
	        str  +=  CNUM[CARDS[i+base]["rank"]]+"，";
	}
	continue;
        }
        if  (!count  ||  !str)
	return  "";
        toreturn=str[0..(strlen(str)-3)];
        return  toreturn;
}
string  display_suit(string  dir,  string  suit)
{
        string  str="",  toreturn;
        int  i=13,  base,  count=0;
        mapping  card;

        switch  (suit)
        {
	case  "spade":
	        str  +=  "\n　　"+HIB"黑桃："NOR;
	        base=1;
	        break;
	case  "heart":
	        str  +=  "\n　　"+HIR"红桃："NOR;
	        base=14;
	        break;
	case  "diamond":
	        str  +=  "\n　　"+HIR"方片："NOR;
	        base=27;
	        break;
	case  "club":
	        str  +=  "\n　　"+HIB"草花："NOR;
	        base=40;
	        break;
	default:
	        return  "函数错误：display_suit。\n";
        }
        while  (i--)
        {
	card=CARDS[i+base];
	if  (dir  ==  card["status"])
	{
	        count++;
	        str  +=  CNUM[card["rank"]]+"，";
	}
	continue;
        }
        if  (!count  ||  !str)
	return  "";
        toreturn=str[0..(strlen(str)-3)];
        return  toreturn;
}
int  search_suit(object  me,  string  suit)
{
        int  count=0,  i=13,  base;
        string  dir=search_my_dir(me);

        switch  (suit)
        {
	case  "spade":
	        base=1;
	        break;
	case  "heart":
	        base=14;
	        break;
	case  "diamond":
	        base=27;
	        break;
	case  "club":
	        base=40;
	        break;
	default:
	        return  notify_fail("函数错误：search_suit。\n");
        }
        while(i--)
        {
	if(CARDS[i+base]["status"]==dir)
	{
//	        tell_room(HERE,  "you  have  "+CARDS[i+base]["name"]+"\n");
	        count++;
	}
	continue;
        }
        return  count;
}

/******************************************************************************/
//  some  functions  for  others  to  use.

void  renew(string  type)
{
        int  i  =  NUM,  j=CARDNO;
        switch  (type)
        {
	case  "round":
	        GAMEINFO["round"]++;
	        all_have("played_card");
	        GAMEINFO["suit"]="";
	        break;
	case  "hand":
	        TABLE["cond"]="等发牌";
	        GAMEINFO["round"]=0;
	        GAMEINFO["suit"]  =  "";
	        GAMEINFO["rlead"]  =  PIG_OWNER;
	        GAMEINFO["next"]  =  "";
	        CLAIM["claimer"]  =  "";
	        SOLD=([  "pig":  ({"not"}),  "blood":  ({"not"}),
			"sheep":  ({"not"}),  "doubler":  ({"not"}),  ]);
	        FULL="";
	        PIG_OWNER="";
	        while(j--)
		CARDS[j+1]["status"]  =  "undealt";
	        while  (i--)
	        {
		GAMEINFO[SUIT[i]]  =  0;
		CLAIM[DIR[i]]  =  "no";
		TABLE[DIR[i]]["card"]=0;
		TABLE[DIR[i]]["collected"]=({});
		TABLE[DIR[i]]["sold"]=({});
		TABLE[DIR[i]]["status"]="filled";
		SCORING["hand"][DIR[i]]=0;
	        }
	        break;
	case  "sitting":
	        renew("hand");
	        PIGHEAD=({});
	        while(i--)
	        {
		SCORING["sitting"][DIR[i]]  =  0;
		SCORING["hand"][DIR[i]]  =  0;
	        }
	        break;
	case  "all":
	        renew("sitting");
	        while(i--)
		if  (TABLE[DIR[i]]["player_id"]  ==  "no  one")
		        TABLE[DIR[i]]["status"]  =  "empty";
	        TABLE["cond"]  =  "等人";
	        GAMEINFO["rlead"]  =  "";
	        break;
	default:
	        tell_room(HERE,"函数用法错误：renew。\n");
	        break;
        }
        return;
}

int  all_have(string  arg)
{
        int  value=1,  i=NUM;
        object  me;

        switch  (arg)
        {
	case  "players":
	        while(i--)
	        {
		if  (TABLE[DIR[i]]["player_name"]  ==  "「空」"
		  ||  !present(TABLE[DIR[i]]["player_id"],  HERE))
		        value  =  0;
	  	continue;
	        }
	        break;
	case  "played_card":
	        while(i--)
	        {
		CARDS[TABLE[DIR[i]]["card"]]["status"]="played";
		TABLE[DIR[i]]["card"]=0;
		continue;
	        }
	        break;
	case  "agreed_claim":
	        while(i--)
	        {
		if  (CLAIM[DIR[i]]  !=  "yes")
		        value  =  0;
		continue;
	        }
	        break;
	case  "cards":
	        while(i--)
	        {
		if  (!TABLE[DIR[i]]["card"])
		        value  =  0;
		continue;
	        }
	        break;
	case  "given_head":
	        while(i--)
	        {
		me=find_me(DIR[i]);
		me->add("piggy/head_given",  sizeof(PIGHEAD));
		continue;
	        }
	        break;
	case  "req_deal":
	        while(i--)
	        {
		if  (TABLE[DIR[i]]["status"]  !=  "asked_for_deal")
		        value  =  0;
		continue;
	        }
	        break;
	case  "pass":
	        while(i--)
	        {
		if  (TABLE[DIR[i]]["status"]  !=  "passed")
		        value  =  0;
		continue;
	        }
	        break;
	        
	default:
	        tell_room(HERE,"函数用法错误：all_have。\n");
	        value  =  0;
	        break;
        }
        return  value;
}

/******************************************************************************/
//  functions  to  look.  look  table,  of  course,  checks  the  table.
//  look  gaoshi  reviews  the  rules  of  this  game......

string  look_table()
{
        string  cond=this_player()->query("env/brief_message");
        if(is_dir(cond))
	cond="YES";

        return  display_table(cond);
}
string  look_collected()
{
        string  str;
        int  i=NUM;

        if  (TABLE["cond"]  !=  "出牌"  &&  TABLE["cond"]  !=  "算分")
	return  "现在没在打牌，桌子上空着。\n";
        str  =  display_sell();
        while  (i--)
        {
	str  +=  "\n"+CDIR[DIR[i]]+"家"+TABLE[DIR[i]]["player_name"]+"收了如下的牌：";
	str  +=  check_collected(DIR[i],  "spade");
	str  +=  check_collected(DIR[i],  "heart");
	str  +=  check_collected(DIR[i],  "diamond");
	str  +=  check_collected(DIR[i],  "club");
        }
        return  str+"\n";
}
string  look_hand()
{
        object  me=this_player();
        string  str="",  dir;

        if  (!in_table(me))
	return  "对不起，你并不在拱猪。\n";
        if  (TABLE["cond"]  ==  "算分")
	return  "这把已经打完了。\n";
        if  (TABLE["cond"]  ==  "等人"  ||  TABLE["cond"]  ==  "等发牌")
	return  "你手中还没有牌。\n";
        dir=search_my_dir(me);
        str  +=  "\n你手中的牌如下：\n";
        str  +=  display_suit(dir,  "spade");
        str  +=  display_suit(dir,  "heart");
        str  +=  display_suit(dir,  "diamond");
        str  +=  display_suit(dir,  "club");

        return  str+"\n\n";
}
string  look_note()
{
        string  str;
        object  me=this_player();

        if  (TABLE["cond"]  ==  "等人")
	return  "纸上画着一个猪头，旁边的名字被人擦去了。下面是个表格，画得歪七扭八的。\n";
        return  display_score();
}
string  display_score()
{
        int  i  =  NUM;
        string  format  =  "│%2s家：%-12s　　　%6d　　%6d　　　%2s│\n";
        string  str  =  "\n┌────────────────────────┐\n"
		+    "│方向　玩家　　　　　　　　盘分　　　总分　　　猪│\n"
		+    "├────────────────────────┤\n";


        while  (i--)
        {
	str  +=  sprintf(format,  CDIR[DIR[i]],  TABLE[DIR[i]]["player_name"],
			SCORING["hand"][DIR[i]],  SCORING["sitting"][DIR[i]],
			(member_array(DIR[i],  PIGHEAD)  ==  -1  ?  "　":  "√"));
	continue;
        }
        str  +=  "└────────────────────────┘\n";
        return  str;
}

string  display_sell()
{
        int  counta=0,  count=0,  countm=0,  i=NUM,  j;
        string  card,  *asell=({}),  str="",  dir;

        if  (SOLD["pig"][0]  ==  "a")
                counta++;
        else  if  (SOLD["pig"][0]  ==  "m")
                countm++;
        if  (SOLD["blood"][0]  ==  "a")
                counta++;
        else  if  (SOLD["blood"][0]  ==  "m")
                countm++;
        if  (SOLD["sheep"][0]  ==  "a")
                counta++;
        else  if  (SOLD["sheep"][0]  ==  "m")
                countm++;
        if  (SOLD["doubler"][0]  ==  "a")
                counta++;
        else  if  (SOLD["doubler"][0]  ==  "m")
                countm++;
        if  (!(countm+counta))  str  +=  "这把没人卖牌。\n";
        else
        {
                str  +=  "卖牌情况如下：\n";
                while(i--)
                {
        	        dir=DIR[i];
        	        if  (!(j=sizeof(TABLE[dir]["sold"])))
        		continue;
        	        str  +=  "　　"+CDIR[dir]+"家"+HIC+TABLE[dir]["player_name"]+NOR;
        	        count=0;
        	        while  (j--)
        	        {
        		card=TABLE[dir]["sold"][j];
        		if  (SOLD[card][0]=="a")  count++;
        		else  str  +=  "明卖"+CCARD[card]+"，";
        	        }
        	        if  (!count)  str  =  str[0..(strlen(str)-3)]+"。";
        	        else  str  +=  "暗卖"+chinese_number(count)+"张。";
        	        str  +=  "\n";
                }
        }
        return  str;
}
string  display_table(string  cond)
{
        int  i,  index,  j,  size,  cnt;
        string  str,  dir,  state;
        mapping  status=allocate_mapping(4),  tmp  =  allocate_mapping(3);
        mapping  sell=allocate_mapping(4);

        sell=([
	"east":  ({"　","　",  "　",  "　",}),
	"north":  "",
	"west":  ({"　","　",  "　",  "　",}),
	"south":  "",
]);
        status=([
	"east":  ([  "card":  "　　　",
		      "player":  "「空」",  ]),
	"north":  ([  "card":  "　　　",
		      "player":  "「空」",  ]),
	"west":  ([  "card":  "　　　",
		      "player":  "「空」",  ]),
	"south":  ([  "card":  "　　　",
		      "player":  "「空」",  ]),
]);

        i  =  NUM;
        while(i--)
        {
	dir  =  DIR[i];
	if  (!is_empty(dir))
	        status[dir]["player"]=TABLE[dir]["player_name"];
	if  (index=TABLE[dir]["card"])
	        status[dir]["card"]  =  CARDS[index]["name"];
	continue;
        }
        if(is_dir(cond))
	state="第"+chinese_number(GAMEINFO["round"])+"轮结束，"+TABLE[cond]["player_name"]+"的牌最大。";
        else
	state  =  (TABLE["cond"]  ==  "出牌"  ?
	        "现在是第"+chinese_number(GAMEINFO["round"])+"轮，该"
		+TABLE[GAMEINFO["next"]]["player_name"]+"出牌："  :  "");
        if  ((cond  ||  TABLE["cond"]  !=  "出牌")  &&  !is_dir(cond))
	str  =  sprintf(PIGSTATE_SHORT,  state,
	        status["north"]["player"],  status["north"]["card"],
	        status["west"]["player"],  status["west"]["card"],
	        status["east"]["card"],  status["east"]["player"],
	        status["south"]["card"],  status["south"]["player"]);
        else
        {
	if  (j=sizeof(TABLE["north"]["sold"]))
	{
	        cnt=j;
	        size=j;
	        while(j--)
		sell["north"]  +=  sold_display("north",  j,  1);
	        sell["north"]  =  treat_sold(sell["north"],  size);
//	        sell["north"]  =  sell["north"][0..(strlen(sell["north"])-3)];
	}
	else  sell["north"]="　　　　　　　　";
	if  (cnt  <  4  &&  j=sizeof(TABLE["south"]["sold"]))
	{
	        cnt+=j;
	        size=j;
	        while(j--)
		sell["south"]  +=  sold_display("south",  j,  1);
	        sell["south"]  =  treat_sold(sell["south"],  size);
//	        sell["south"]  =  sell["south"][0..(strlen(sell["south"])-3)];
	}
	else  sell["south"]="　　　　　　　　";
	if  (cnt  <  4  &&  j=sizeof(TABLE["east"]["sold"]))
	{
	        cnt  +=  j;
	        switch(j)
	        {
	            case  1:
		sell["east"][1]=sold_display("east",  0,  0);
		break;
	            case  2:
		sell["east"][1]=sold_display("east",  0,  0);
		sell["east"][2]=sold_display("east",  1,  0);
		break;
	            case  3:
		sell["east"][0]=sold_display("east",  0,  0);
		sell["east"][1]=sold_display("east",  1,  0);
		sell["east"][2]=sold_display("east",  2,  0);
		break;
	            case  4:
		sell["east"][0]=sold_display("east",  0,  0);
		sell["east"][1]=sold_display("east",  1,  0);
		sell["east"][2]=sold_display("east",  1,  0);
		sell["east"][3]=sold_display("east",  3,  0);
		break;
	        }
	}
	if  (cnt  <  4  &&  j=sizeof(TABLE["west"]["sold"]))
	{
	        cnt  +=  j;
	        switch(j)
	        {
	            case  1:
		sell["west"][1]=sold_display("west",  0,  0);
		break;
	            case  2:
		sell["west"][1]=sold_display("west",  0,  0);
		sell["west"][2]=sold_display("west",  1,  0);
		break;
	            case  3:
		sell["west"][0]=sold_display("west",  0,  0);
		sell["west"][1]=sold_display("west",  1,  0);
		sell["west"][2]=sold_display("west",  2,  0);
		break;
	            case  4:
		sell["west"][0]=sold_display("west",  0,  0);
		sell["west"][1]=sold_display("west",  1,  0);
		sell["west"][2]=sold_display("west",  1,  0);
		sell["west"][3]=sold_display("west",  3,  0);
		break;
	        }
	}
	str  =  sprintf(PIGSTATE_FULL,  state,
	        status["north"]["player"],
	        sell["north"],
	        sell["west"][0],
	        status["north"]["card"],
	        sell["east"][0],
	        sell["west"][1],
	        sell["east"][1],
	        status["west"]["player"],
	        status["west"]["card"],
	        status["east"]["card"],
	        status["east"]["player"],
	        sell["west"][2],
	        sell["east"][2],
	        sell["west"][3],
	        status["south"]["card"],
	        sell["east"][3],
	        sell["south"],
	        status["south"]["player"]);
        }
        return  str;
}
string  treat_sold(string  sold,  int  cnt)
{
        string  str="";

        switch  (cnt)
        {
	case  4:  str  =  sold;break;
	case  3:  str  =  "　"+sold+"　";break;
	case  2:  str  =  "　　"+sold+"　　";break;
	case  1:  str  =  "　　　"+sold+"　　　";break;
        }

        return  str;
}
string  sold_display(string  dir,  int  index,  int  flag)
{
        string  str="";

        str  +=  (SOLD[TABLE[dir]["sold"][index]][0]  ==  "m"  ?
	(CARDS[NCARD[TABLE[dir]["sold"][index]]]["status"]  !=  "played"?
	SCARD[TABLE[dir]["sold"][index]]
	        +(CCARD[TABLE[dir]["sold"][index]][0..1])  :  "○")+NOR  :
	(CARDS[NCARD[TABLE[dir]["sold"][index]]]["status"]  ==  "played"?
		GRN"□"NOR:GRN"■"NOR));
        if  (flag)  str  +=  "　";
        return  str;
}
string  read_rules()
{

        string  str="";

        str  +=  "如果您不会打拱猪，请用  help  pigrules  来查看。\n\n";
        str  +=  "具体打牌方法请用  help  pigcmds  来查看。\n\n";

        return  str;
}
/******************************************************************************/
