// /d/changan/puke-room.c
 

//扑克牌。

inherit  ROOM;

string  *pai_name  =  ({
"【黑Ａ】",  "【黑２】",  "【黑３】",  "【黑４】",  "【黑５】",  "【黑６】",  "【黑７】",  
"【黑８】",  "【黑９】",  "【黑十】",  "【黑Ｊ】",  "【黑Ｑ】",  "【黑Ｋ】",  
"【红Ａ】",  "【红２】"  ,"【红３】",  "【红４】",  "【红５】",  "【红６】",  "【红７】",  
"【红８】",  "【红９】",  "【红十】",  "【红Ｊ】",  "【红Ｑ】",  "【红Ｋ】",  
"【草Ａ】",  "【草２】",  "【草３】",  "【草４】",  "【草５】",  "【草６】",  "【草７】",  
"【草８】",  "【草９】",  "【草十】",  "【草Ｊ】",  "【草Ｑ】",  "【草Ｋ】",  
"【方Ａ】",  "【方２】",  "【方３】",  "【方４】",  "【方５】",  "【方６】",  "【方７】",  
"【方８】",  "【方９】",  "【方十】",  "【方Ｊ】",  "【方Ｑ】",  "【方Ｋ】",  
"【小王】",  "【大王】"
});

int  pai_size  =  sizeof(pai_name)-2;
//for  gongzhu,  it's  52.

string  *pai_state  =  ({
"i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  
"i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  
"i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i"
});
//here  state  can  be  i(initial),  t(table),  n(north),  s(south),  w(west),  e(east).

string  *pai_destination  =  ({
"i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  
"i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  
"i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i",  "i"
});
//here  destination  can  be  i(initial),  t(table),  n(north),  s(south),  w(west),  e(east).
//this  is  mainly  for  score.

string  e_id  =  "no  one";
string  w_id  =  "no  one";
string  n_id  =  "no  one";
string  s_id  =  "no  one";
string  who_to_play  =  "no  one";  

int  e_score  =  0;
int  w_score  =  0;
int  n_score  =  0;
int  s_score  =  0;
int  cao_double  =  1;  //can  be  1  or  2.
int  hong_double  =  1;  //can  be  1  or  2.
int  pig_double  =  1;  //can  be  1  or  2.
int  yang_double  =  1;  //can  be  1  or  2.

//last  pai  played.
int  e_last  =  pai_size;  
int  w_last  =  pai_size;  
int  n_last  =  pai_size;  
int  s_last  =  pai_size;  

int  game_id  =  0;  //how  many  games  processed.

int  round  =  0;  //this  indicates  how  many  rounds  processed.
string  current_round_kind  =  "none";  //kind  this  round.
int  current_round_step  =  0;  //can  be  0,  1,  2,  3,  4.
int  *current_round_ids  =  ({
53,  53,  53,  53,  53
});  //the  first  element  is  reserved.

int  game_status  =  0;
//=0,  no  game  yet.
//=1,  game  in  process.

string  check_kind(int  i);
int  check_rank(int  i);
int  check_score(int  i);
int  pai_compare(int  p1,  int  p2);
int  convert_to_id(string  kind,  int  rank);
void  game_process();
string  get_next_player();
void  game_finished();
void  calculate_score();
void  show_table(int  out);
void  show_score();
void  send_pai();
string  chinese_dir(string  dir);
void  game_reset();
void  check_finish(int  previous_game_id);

void  create  ()
{
	set  ("short",  "拱猪房");
	set  ("long",  @LONG
屋中间摆着一张看起来相当结实的大方桌 (table)，桌边围着四把
靠背木椅。东面墙上有一块大牌子 (paizi)，西面墙上有一块小牌子
(score)。
LONG);

	set("item_desc",  (["paizi"  :  "

拱猪规则：

主要指令有：
一，就坐(sit  <n,  s,  e,  w>)。
二，开拱(start)。
三，出牌(play  <花色>  <大小>)。
　　花色有(hei,  hong,  cao,  fang)或用(S/s,  H/h,  C/c,  D/d)来代表。
　　大小有(1,  ...,  13)或用(A/a,  J/j,  Q/q,  K/k)来代表(1,  11,  12,  13)。
四，好牌亮相(double  <zhu/z,  yang/y,  hong/h,  bian/b>)。
五，查自己的牌(my)。
六，看桌面情况(look  table)。
七，看积分(look  score)。
八，退出拱猪(leave)。

注意事项：
一，要端正牌风，系统不揭发舞弊。
二，每一盘必须在半小时内完成，否则取消重来。
二，有任何bug请报告巫师。目前是测试阶段，可能还有不少错。

		\n"  ]));
	//for  look  something.

	set("exits",  
	([  //sizeof()  ==  4
		//"south"  :  __DIR__"xiaomuwu",
		//"north"  :  __DIR__"chufang",
		//"west"  :  __DIR__"duchang2",
		"west"  :  __DIR__"clubpoem",
		//"up"  :  __DIR__"***",
		//"down"  :  __DIR__"***",
	]));
	
	set("objects",  
	([  //sizeof()  ==  1
		//__DIR__"npc/gongsun"  :  1,
	]));


	set("no_fight",  1);
	set("no_magic",  1);
	
	set("no_clean_up",  1);

	set("coor/x", -5020);
	set("coor/y", 1010);
	set("coor/z", 20);
	setup();
}

void  init()
{
	add_action("do_sit",  "sit");
	add_action("do_play",  "play");
	add_action("do_double",  "double");
	add_action("do_leave",  "leave");
	add_action("do_start",  "start");	
	add_action("do_look",  "look");
	add_action("do_my",  "my");
}

string  check_kind(int  i)
{
	if(  i  <  0  )  return  "none";
	else  if(  i  <  13  )    return  "hei";
	else  if(  i  <  26  )    return  "hong";
	else  if(  i  <  39  )    return  "cao";
	else  if(  i  <  52  )    return  "fang";
	else  if(  i  ==  52  )    return  "xwang";
	else  if(  i  ==  53  )    return  "dwang";
	else  return  "none";
}

int  check_rank(int  i)
{
	int  rank;

	if(  i  <  0  )  rank  =  0;
	else  if(  i  <  52  )  
	{
		rank  =  1+(i%13);
		if  (  rank  ==  1  )  rank  =  14;  //this  is  for  A.
	}
	else  rank  =  1+i;

	return  rank;
}

int  check_score(int  i)
{
	int  rank;

	if(pai_name[i]=="【黑Ｑ】")  return  100*pig_double;
	if(pai_name[i]=="【方Ｊ】")  return  -100*yang_double;
	if(pai_name[i]=="【草十】")  return  -10;

	if(check_kind(i)  !=  "hong"  )  return  0;

	rank  =  check_rank(i);
	if(  rank  <  5  )  return  0;
	else  if  (  rank  <=  10  )  return  10*hong_double;
	else  return  (rank-9)*10*hong_double;  
}

int  convert_to_id(string  kind,  int  rank)
{
	if(  kind  ==  "xwang"  )  return  52;
	if(  kind  ==  "dwang"  )  return  53;

	if(  rank  ==  14  )  rank  =  1;  
	//this  is  for  A.
	//but  can  also  be  sent  in  as  1  here.
	
	if(  kind  ==  "hei"  )  return  (rank  -1);
	else  if(  kind  ==  "hong"  )  return  (rank  +12);  
	else  if(  kind  ==  "cao"  )  return  (rank  +25);  
	else  if(  kind  ==  "fang"  )  return  (rank  +38);
	else  return  53;  	
}

string  chinese_dir(string  dir)
{
	if(dir  ==  "east"  ||  dir  ==  "e")  return  "东";
	else  if(dir  ==  "west"  ||  dir  ==  "w")  return  "西";
	else  if(dir  ==  "south"  ||  dir  ==  "s")  return  "南";
	else  if(dir  ==  "north"  ||  dir  ==  "n")  return  "北";
	else  if(dir  ==  "up"  ||  dir  ==  "u")  return  "上";
	else  if(dir  ==  "down"  ||  dir  ==  "d")  return  "下";
	else  if(dir  ==  "left"  ||  dir  ==  "l")  return  "左";
	else  if(dir  ==  "right"  ||  dir  ==  "r")  return  "右";
	else  return  "？";
}

int  do_sit(string  arg)
{
	string  dir,  my_id;
	object  players;
	object  me  =  this_player();

	my_id  =  me->query("id");

	if(  my_id  ==  e_id  ||  my_id  ==  w_id  ||  my_id  ==  n_id  ||  my_id  ==  s_id  )
		return  notify_fail("你已经坐下了？\n");

	if(!arg)  return  notify_fail("你要坐哪边？\n");

	if  (  arg  ==  "east"  ||  arg  ==  "e"  )
	{
		if(  objectp(players=present(e_id,  this_object()))  &&  living(players)  )  
		{
			return  notify_fail("东座已经有人了。\n");
		}
		else  
		{
			e_id  =  my_id;
			message_vision("$N坐上了东边的椅子。\n",  me);
			return  1;
		}
	}
	else  if  (  arg  ==  "west"  ||  arg  ==  "w"  )
	{
		if(  objectp(players=present(w_id,  this_object()))  &&  living(players)  )  
		{
			return  notify_fail("西座已经有人了。\n");
		}
		else  
		{
			w_id  =  my_id;
			message_vision("$N坐上了西边的椅子。\n",  me);
			return  1;
		}
	}
	else  if  (  arg  ==  "north"  ||  arg  ==  "n"  )
	{
		if(  objectp(players=present(n_id,  this_object()))  &&  living(players)  )  
		{
			return  notify_fail("北座已经有人了。\n");
		}
		else  
		{
			n_id  =  my_id;
			message_vision("$N坐上了北边的椅子。\n",  me);
			return  1;
		}
	}
	else  if  (  arg  ==  "south"  ||  arg  ==  "s"  )
	{
		if(  objectp(players=present(s_id,  this_object()))  &&  living(players)  )  
		{
			return  notify_fail("南座已经有人了。\n");
		}
		else  
		{
			s_id  =  my_id;
			message_vision("$N坐上了南边的椅子。\n",  me);
			return  1;
		}
	}
	else  return  notify_fail("你要坐哪边？\n");
}

int  do_play(string  arg)
{
	object  players;
	object  me;
	int  rank;
	string  kind,  rank_str,  my_id;
	int  pai_id;
	string  pai_owner;

	me=this_player();
	my_id  =  me->query("id");

	//check  if  I  am  playing...
	if(  my_id  !=  e_id  &&  my_id  !=  w_id  &&  my_id  !=  n_id  &&  my_id  !=  s_id  )
		return  notify_fail("观牌不语真君子。\n");

	//everyone  is  here?
	if(!objectp(players=present(e_id,  this_object()))  )
	{
		e_id  =  "no  one";
		return  notify_fail("东家不在了。找人来替补吧。\n");
	}
	if(!objectp(players=present(w_id,  this_object()))  )
	{
		w_id  =  "no  one";
		return  notify_fail("西家不在了。找人来替补吧。\n");
	}
	if(!objectp(players=present(n_id,  this_object()))  )
	{
		n_id  =  "no  one";
		return  notify_fail("北家不在了。找人来替补吧。\n");
	}
	if(!objectp(players=present(s_id,  this_object()))  )
	{
		s_id  =  "no  one";
		return  notify_fail("南家不在了。找人来替补吧。\n");
	}

	//who  to  play?
	if(my_id  !=  who_to_play  )
		return  notify_fail("还没到你出牌。\n");

	if(  (!  arg)  ||  (sscanf  (arg,"%s  %s",  kind,  rank_str)  !=  2))
		return  notify_fail("请使用：play  <花色>  <大小>\n");

	//convert...
	if(  kind  ==  "S"  ||  kind  ==  "s"  )  kind  =  "hei";
	else  if(  kind  ==  "H"  ||  kind  ==  "h"  )  kind  =  "hong";
	else  if(  kind  ==  "C"  ||  kind  ==  "c"  )  kind  =  "cao";
	else  if(  kind  ==  "D"  ||  kind  ==  "d"  )  kind  =  "fang";
	else  if(  kind  ==  "hei"  ||  kind  ==  "hong"  ||  kind  ==  "cao"  ||  kind  ==  "fang"  )  kind  =  kind;//do  nothing  here.
	else  return  notify_fail("花色只有(hei,  hong,  cao,  fang)或用(S/s,  H/h,  C/c,  D/d)来代表。\n");

	if(  rank_str  ==  "1"  ||  rank_str  ==  "A"  ||  rank_str  ==  "a"  )  rank  =  1;
	else  if(  rank_str  ==  "2")  rank  =  2;  
	else  if(  rank_str  ==  "3")  rank  =  3;  
	else  if(  rank_str  ==  "4")  rank  =  4;  
	else  if(  rank_str  ==  "5")  rank  =  5;  
	else  if(  rank_str  ==  "6")  rank  =  6;  
	else  if(  rank_str  ==  "7")  rank  =  7;  
	else  if(  rank_str  ==  "8")  rank  =  8;  
	else  if(  rank_str  ==  "9")  rank  =  9;  
	else  if(  rank_str  ==  "10")  rank  =  10;
  	else  if(  rank_str  ==  "11"  ||  rank_str  ==  "J"  ||  rank_str  ==  "j"  )  rank  =  11;
	else  if(  rank_str  ==  "12"  ||  rank_str  ==  "Q"  ||  rank_str  ==  "q"  )  rank  =  12;
	else  if(  rank_str  ==  "13"  ||  rank_str  ==  "K"  ||  rank_str  ==  "k"  )  rank  =  13;
	else  return  notify_fail("大小只有(1,  ...,  13)或用(A/a,  J/j,  Q/q,  K/k)来代表(1,  11,  12,  13)。\n");
	
	//if  I  have  this  pai.	
	pai_id  =  convert_to_id(kind,  rank);
	if(  pai_id  <  0  ||  pai_id  >=  pai_size)  //note,  here  no  wang.
		return  notify_fail("没有这张牌。\n");

	if(  pai_state[pai_id]  ==  "e"  )  pai_owner  =  e_id;
	else  if(  pai_state[pai_id]  ==  "w"  )  pai_owner  =  w_id;
	else  if(  pai_state[pai_id]  ==  "n"  )  pai_owner  =  n_id;
	else  if(  pai_state[pai_id]  ==  "s"  )  pai_owner  =  s_id;
	else  if(  pai_state[pai_id]  ==  "t"  )  return  notify_fail("这张牌出过了。\n");
	else  return  notify_fail("奇怪，这张牌丢了。\n");

	if(  my_id  !=  pai_owner  )
		return  notify_fail("你没有这张牌。\n");

	//I    can  play  out  this  pai.
	message_vision("$N打出一张"+pai_name[pai_id]+"。\n",  me);

	if(  pai_state[pai_id]  ==  "e"  )  e_last  =  pai_id;
	else  if(  pai_state[pai_id]  ==  "w"  )  w_last  =  pai_id;
	else  if(  pai_state[pai_id]  ==  "n"  )  n_last  =  pai_id;
	else  if(  pai_state[pai_id]  ==  "s"  )  s_last  =  pai_id;
	else  tell_room(this_object(),  "出问题了(set  last  pai)，叫巫师来吧。\n");

	pai_state[pai_id]  =  "t";//mark  it  as  on  table.	

	game_process();

	return  1;
}

void  game_process()
{
	object  next_player;

	int  i,  pai_on_table;
	int  rd;
	string  rd_msg;

	//check  score  for  this  round  if  needed.
	pai_on_table  =  0;
	for(i=0;  i<pai_size;  i++)
	{
		if(  pai_state[i]  ==  "t"  )  pai_on_table++;
	}

	current_round_step  =  pai_on_table%4;  //this  can  be  1,2,3,0.
	if(  current_round_step  ==  0  &&  pai_on_table  !=  0)  
		current_round_step  =  4;  //now  it'll  be  1,2,3,4(only  at  the  beginning,  0)

	//set  curent  round's  pai.
	if(  who_to_play  ==  e_id  )  
		current_round_ids[current_round_step]  =  e_last  ;
	else  if(  who_to_play  ==  w_id  )  
		current_round_ids[current_round_step]  =  w_last  ;
	else  if(  who_to_play  ==  n_id  )  
		current_round_ids[current_round_step]  =  n_last  ;
	else  if(  who_to_play  ==  s_id  )  
		current_round_ids[current_round_step]  =  s_last  ;
	else  
		tell_room(this_object(),  "出问题了(set  current  ids)，叫巫师来吧。\n");
	
	//set  round  rank
	if(  current_round_step  ==  1  )
	{
		if(  who_to_play  ==  e_id  )  
			current_round_kind  =  check_kind(  e_last  );
		else  if(  who_to_play  ==  w_id  )  
			current_round_kind  =  check_kind(  w_last  );
		else  if(  who_to_play  ==  n_id  )  
			current_round_kind  =  check_kind(  n_last  );
		else  if(  who_to_play  ==  s_id  )  
			current_round_kind  =  check_kind(  s_last  );
		else  
			tell_room(this_object(),  "出问题了(set  current  kind)，叫巫师来吧。\n");
	}
  

	if(  current_round_step  ==  4  )
	{//check  score...
		who_to_play  =  get_next_player();
	}
	else
	{//轮着排。
		if(  who_to_play  ==  e_id  )  who_to_play  =  n_id;
		else  if(  who_to_play  ==  n_id  )  who_to_play  =  w_id;
		else  if(  who_to_play  ==  w_id  )  who_to_play  =  s_id;
		else  if(  who_to_play  ==  s_id  )  who_to_play  =  e_id;
		else  tell_room(this_object(),  "出问题了(shift  player)，叫巫师来吧。\n");
	}

	if(  current_round_step  !=  0  )
	{
		rd_msg  =  "这一轮所出的牌：";
		for(rd=1;  rd<=current_round_step;  rd++)
		{
			if  (  current_round_ids[rd]  <  pai_size  )
				rd_msg  +=  pai_name[current_round_ids[rd]];
		}
		rd_msg  +=  "\n";
		tell_room(this_object(),  rd_msg);
	}

	if  (pai_on_table  ==  pai_size)
	{
		call_out("game_finished",  1);
		return;
	}

	if(objectp(next_player=present(who_to_play,  this_object()))  &&  living(next_player)  )
	{
		tell_room(this_object(),  "下面该"+next_player->query("name")+"出牌了。\n");
	}
	else
	{
		tell_room(this_object(),  "下一位出牌人跑了？\n");
	}			
}

string  get_next_player()
{
	int  bigger;
	string  dest;
	string  next_player;

	dest  =  "t";
	next_player  =  "no  one";

	if(  pai_compare(e_last,  w_last)  >  0  )  bigger  =  e_last;
	else  bigger  =  w_last;
	if(  pai_compare(n_last,  bigger)  >  0  )  bigger  =  n_last;
	if(  pai_compare(s_last,  bigger)  >  0  )  bigger  =  s_last;

	if(bigger  ==  e_last)
	{
		dest  =  "e";  
		next_player  =  e_id;
	}
	else  if(bigger  ==  w_last)  
	{
		dest  =  "w";  
		next_player  =  w_id;
	}
	else  if(bigger  ==  n_last)  
	{
		dest  =  "n";  
		next_player  =  n_id;
	}
	else  if(bigger  ==  s_last)
	{
		dest  =  "s";  
		next_player  =  s_id;
	}  
	else  tell_room(this_object(),  "出问题了(get  next  player)，叫巫师来吧。\n");

	if(  check_score(e_last)  !=  0  )  pai_destination[e_last]  =  dest;
	if(  check_score(w_last)  !=  0  )  pai_destination[w_last]  =  dest;
	if(  check_score(n_last)  !=  0  )  pai_destination[n_last]  =  dest;
	if(  check_score(s_last)  !=  0  )  pai_destination[s_last]  =  dest;

	tell_room(this_object(),  chinese_dir(dest)+"家的"+pai_name[bigger]+"最大。\n");
	if(pai_name[e_last]=="【黑Ｑ】"  ||  pai_name[w_last]=="【黑Ｑ】"  
	||    pai_name[n_last]=="【黑Ｑ】"  ||  pai_name[s_last]=="【黑Ｑ】"  )
		tell_room(this_object(),  "啊哈！猪上"+chinese_dir(dest)+"家去了。\n");
	if(pai_name[e_last]=="【方Ｊ】"  ||  pai_name[w_last]=="【方Ｊ】"  
	||    pai_name[n_last]=="【方Ｊ】"  ||  pai_name[s_last]=="【方Ｊ】"  )
		tell_room(this_object(),  chinese_dir(dest)+"家得到了羊。\n");
	
	return  next_player;
}

int  pai_compare(int  p1,  int  p2)
{
	//same  kind.
	if(  check_kind(p1)  ==  check_kind(p2)  )  
		return  (check_rank(p1)-check_rank(p2));

	//different  kind.
	if(  check_kind(p1)  ==  current_round_kind  )  return  1;
	if(  check_kind(p2)  ==  current_round_kind  )  return  -1;
	
	//else
	return  0;	
}

void  game_finished()
{
	tell_room(this_object(),  "这一局结束了。\n");

	//calculate  score  for  this  round.
	calculate_score();

	show_table(1);

	//reset.
	game_reset();
}

void  game_reset()
{
	int  i;

	game_status  =  0;
	e_id  =  "no  one";
	w_id  =  "no  one";
	n_id  =  "no  one";
	s_id  =  "no  one";
	who_to_play  =  "no  one";

	e_last  =  pai_size;  
	w_last  =  pai_size;  
	n_last  =  pai_size;  
	s_last  =  pai_size;  

	current_round_kind  =  "none";
	current_round_step  =  0;
	for(i=0;  i<sizeof(current_round_ids);  i++)
	{
		current_round_ids[i]  =  53;
	}

	cao_double  =  1;  //can  be  1  or  2.
	hong_double  =  1;  //can  be  1  or  2.
	pig_double  =  1;  //can  be  1  or  2.
	yang_double  =  1;  //can  be  1  or  2.

	for(i=0;  i<54;  i++)
	{
		pai_state[i]  =  "i";
		pai_destination[i]  =  "i";
	}
}

check_finish(int  previous_game_id)
{
	if(previous_game_id  !=  game_id)  return;  //it  means  already  finished.
	if(game_status  ==  0)  return;  //no  game,  no  need  to  cancel.

	tell_room(this_object(),  "这一盘一直完不成，只好取消重来了。\n");
	game_reset();
}

void  calculate_score()
{
	int  i;
	int  c10;
	string  hong_dest;

	e_score  =  0;
	w_score  =  0;
	n_score  =  0;
	s_score  =  0;

	for(i=0;  i<pai_size;  i++)
	{
		if(pai_destination[i]  ==  "e")  e_score  +=  check_score(i);
		else  if(pai_destination[i]  ==  "w")  w_score  +=  check_score(i);
		else  if(pai_destination[i]  ==  "n")  n_score  +=  check_score(i);
		else  if(pai_destination[i]  ==  "s")  s_score  +=  check_score(i);
	}

	//where  is  caohua  10?
	c10  =  convert_to_id("cao",  10);
	if(  pai_destination[c10]  =  "e"  )  e_score  *=  2*cao_double;
	else  if(  pai_destination[c10]  =  "w"  )  w_score  *=  2*cao_double;
	else  if(  pai_destination[c10]  =  "n"  )  n_score  *=  2*cao_double;
	else  if(  pai_destination[c10]  =  "s"  )  s_score  *=  2*cao_double;	

	//check  if  anyone  collected  all  hong.
	hong_dest  =  pai_destination[convert_to_id("hong",  1)];
	for  (i=2;  i<=13;  i++)
	{
		if(  pai_destination[convert_to_id("hong",  i)]  !=  hong_dest  )  
			return;
	}

	//now  all  hong  in  one  place.
	if(  hong_dest  ==  "e"  )  e_score  =  -e_score;
	else  if(  hong_dest  ==  "w"  )  w_score  =  -w_score;
	else  if(  hong_dest  ==  "n"  )  n_score  =  -n_score;
	else  if(  hong_dest  ==  "s"  )  s_score  =  -s_score;	
}

void  show_table(int  out)
{//if  out==0,  tell  player,  otherwise  tell  room.    
	object  players;
	int  i,  j,  rd;
	string  msg,  e_msg,  w_msg,  n_msg,  s_msg;

	if(  out  ==  0  )
	{
		msg  =  "东家：";
		if(  objectp(players=present(e_id,  this_object()))  &&  living(players)  )
			msg  +=  players->query("name")+"；";
		else  msg  +=  "暂缺；";  
		msg  +=  "南家：";
		if(  objectp(players=present(s_id,  this_object()))  &&  living(players)  )
			msg  +=  players->query("name")+"；";
		else  msg  +=  "暂缺；";  
		msg  +=  "西家：";
		if(  objectp(players=present(w_id,  this_object()))  &&  living(players)  )
			msg  +=  players->query("name")+"；";
		else  msg  +=  "暂缺；";  
		msg  +=  "北家：";
		if(  objectp(players=present(n_id,  this_object()))  &&  living(players)  )
			msg  +=  players->query("name")+"\n\n";
		else  msg  +=  "暂缺。\n\n";

		if(  game_status  ==  1  )
		{
			if(  current_round_step  !=  0  )
			{
				msg  +=  "这一轮所出的牌：";
				for(rd=1;  rd<=current_round_step;  rd++)
				{
					if  (  current_round_ids[rd]  <  pai_size  )
						msg  +=  pai_name[current_round_ids[rd]];
				}
				msg  +=  "\n";
			}
			if(  objectp(players=present(who_to_play,  this_object()))  &&  living(players)  )
				msg  +=  "下面该"+players->query("name")+"出牌。\n\n";
			else  msg  +=  "下面该???出牌。\n\n";
		}
  
		write(msg);
	}

	j  =  0;
	msg  =  "已出的牌有：\n";
	for(i=0;  i<pai_size;  i++)
	{
		if(  (i==13  ||    i==26  ||  i==39  ||  i==52)  )  
		{
			msg  +=  "\n";
			j  =  0;
		}

		if(  pai_state[i]  ==  "t"  )  
		{
			j++;
			msg  +=  pai_name[i];
			if(  j==7  &&  (i!=12&&i!=25&&i!=38&&i!=51)  )
			{
				j  =  0;
				msg  +=  "\n";
			}
		}
	}

	if(  out  )  tell_room(this_object(),  msg+"\n\n");
	else  write(msg+"\n\n");

	e_msg  =  "东家所得牌：\n";
	w_msg  =  "西家所得牌：\n";
	n_msg  =  "北家所得牌：\n";
	s_msg  =  "南家所得牌：\n";
	for(i=0;  i<52;  i++)
	{
		if(pai_destination[i]  ==  "e")  e_msg  +=  pai_name[i];
		else  if(pai_destination[i]  ==  "w")  w_msg  +=  pai_name[i];
		else  if(pai_destination[i]  ==  "n")  n_msg  +=  pai_name[i];
		else  if(pai_destination[i]  ==  "s")  s_msg  +=  pai_name[i];
	}

	if(  out  )
	{
		tell_room(this_object(),  e_msg+"\n");
		tell_room(this_object(),  s_msg+"\n");
		tell_room(this_object(),  w_msg+"\n");
		tell_room(this_object(),  n_msg+"\n");
	}
	else
	{
		write(e_msg+"\n");
		write(s_msg+"\n");
		write(w_msg+"\n");
		write(n_msg+"\n");
	}	
}

void  show_score()
{
	if(  game_id  ==  0  )
	{  
		write("拱猪还没开张，没有任何分数。\n");
		return;
	}
  
	if(  game_status  ==  1  )  
	{
		write("拱猪正在进行，这一局的分数还没出来。\n");
		write("上一局的结果是：\n");
	}
	else    write("最新战况：\n");

	write("东家："+sprintf("%d",  e_score)+"分。\n");
	write("南家："+sprintf("%d",  s_score)+"分。\n");
	write("西家："+sprintf("%d",  w_score)+"分。\n");
	write("北家："+sprintf("%d",  n_score)+"分。\n");
}

int  do_leave()
{
	string  my_id;
	object  me  =  this_player();

	my_id  =  me->query("id");
	if(  my_id  !=  e_id  &&  my_id  !=  w_id  &&  my_id  !=  n_id  &&  my_id  !=  s_id  )
		return  notify_fail("你并没有参加拱猪。\n");

	if(  my_id  ==  e_id  )  e_id  =  "no  one";
	else  if(  my_id  ==  w_id  )  w_id  =  "no  one";
	else  if(  my_id  ==  n_id  )  n_id  =  "no  one";
	else  if(  my_id  ==  s_id  )  s_id  =  "no  one";
	message_vision("$N说道：对不起，你们找人接替吧，我不玩了。\n",  me);
	return  1;
}

int  do_double(string  arg)
{
	int  i,  pai_on_table;
	string  my_id,  dir;
	object  me  =  this_player();

	my_id  =  me->query("id");
	if(  my_id  !=  e_id  &&  my_id  !=  w_id  &&  my_id  !=  n_id  &&  my_id  !=  s_id  )
		return  notify_fail("你并没有参加拱猪。\n");

	if(game_status  ==  0)  return  notify_fail("拱猪还没开始。\n");

	pai_on_table  =  0;
	for(i=0;  i<pai_size;  i++)
	{
		if(  pai_state[i]  ==  "t"  )  pai_on_table++;
	}
	if  (  pai_on_table  !=  0  )  return  notify_fail("太晚了。\n");	

	if(!arg||(arg!="zhu"&&arg!="z"&&
		arg!="yang"&&arg!="y"&&
		arg!="hong"&&arg!="h"&&
		arg!="bian"&&arg!="b"))  
		return  notify_fail("你要亮什么？\n");

	if(  my_id  ==  e_id  )  dir="e";
	else  if(  my_id  ==  w_id  )  dir="w";
	else  if(  my_id  ==  n_id  )  dir="n";
	else  if(  my_id  ==  s_id  )  dir="s";

	if(arg=="zhu"||arg=="z")
	{
		if(  pai_state[convert_to_id("hei",  12)]  ==  dir  )
		{
			pig_double  =  2;
			message_vision("$N奸笑了几声：嘿嘿，我有猪，你们得小心点。\n",  me);	
			return  1;
		}
		else  return  notify_fail("你手头并没有猪。\n");
	}
	else  if(arg=="yang"||arg=="y")
	{
		if(  pai_state[convert_to_id("fang",  11)]  ==  dir  )
		{
			yang_double  =  2;
			message_vision("$N兴奋地叫道：我有羊！\n",  me);	
			return  1;
		}
		else  return  notify_fail("别做梦了。\n");
	}
	else  if(arg=="hong"||arg=="h")
	{
		if(  pai_state[convert_to_id("hong",  1)]  ==  dir  )
		{
			hong_double  =  2;
			message_vision("$N大声道：现在我宣布，红心提价！\n",  me);	
			return  1;
		}
		else  return  notify_fail("你没有红心尖。\n");
	}
	else  if(arg=="bian"||arg=="b")
	{
		if(  pai_state[convert_to_id("cao",  10)]  ==  dir  )
		{
			cao_double  =  2;
			message_vision("$N躲在一边偷偷直笑：变压器的油可是加满了！\n",  me);	
			return  1;
		}
		else  return  notify_fail("你还是先弄个变压器再说吧。\n");
	}

	return  1;
}

int  do_start()
{
	int  need_players;    
	object  players,  me;
	string  my_id;
	
	need_players  =  0;

	me  =  this_player();
	my_id  =  me->query("id");

	if(game_status  ==  1)  return  notify_fail("拱猪已经开始了。\n");

	if(  my_id  !=  e_id  &&  my_id  !=  w_id  &&  my_id  !=  n_id  &&  my_id  !=  s_id  )
		return  notify_fail("你还没坐下来呢。\n");

	if(  !objectp(players=present(e_id,  this_object()))  )  
		need_players++;
	if(  !objectp(players=present(w_id,  this_object()))  )  
		need_players++;
	if(  !objectp(players=present(n_id,  this_object()))  )  
		need_players++;
	if(  !objectp(players=present(s_id,  this_object()))  )  
		need_players++;
	
	if(  need_players  >  0  )  return  notify_fail("还得找"+chinese_number(need_players)+"个人才能开拱。\n");

	//now  start  game.
	game_status  =  1;
	game_id  ++;
	call_out("check_finish",  1800,  game_id);  //30  minutes

	message_vision("$N大声宣布：拱猪正式开始！\n",  me);
	send_pai();	
	who_to_play  =  my_id;
	tell_room(this_object(),  "下面由"+me->query("name")+"开牌。\n");
	message_vision("$N问道：有亮相的没有？没有我可出牌了！\n",  me);
	current_round_step  =  1;  //set  it  to  1  as  the  beginning.
	return  1;
}

void  send_pai()
{//send  pai  out  to  players...
	int  remain,  one_set;
	string  dir;
	int  i,  j,  k,  which;

	remain  =  pai_size;

	for(k=0;  k<pai_size;  k++)
	{
		one_set  =  0;

		if(k<13)  dir="e";
		else  if(k<26)  dir="w";
		else  if(k<39)  dir="n";
		else  if(k<pai_size)  dir="s";
		else  dir="t";

		which  =  random(remain);
		
		j=  0;
		for(i=0;  i<pai_size;  i++)
		{
			if(pai_state[i]  ==  "i")  
			{
				if(j==which)  
				{
					if(one_set  ==  0)
					{
						pai_state[i]  =  dir;
						remain--;
						one_set  =  1;
					}
				}
				j++;  
			}	
		}//sent  out  1  pai.
	}//all  pai  sent  out.	
}

int  do_look(string  arg)
{
	if(arg  ==  "table")
	{
		show_table(0);
		return  1;
	}
	else  if(arg  ==  "score")
	{
		show_score();
		return  1;
	}
	else  return  0;	
}

int  do_my()
{//check  my  pai.
	int  i,  j;
	object    me;
	string  my_id;
	string  dir,  msg;

	me  =  this_player();
	my_id  =  me->query("id");

	if(game_status  ==  0)  return  notify_fail("拱猪还没开始。\n");

	dir="no  dir";

	if(  my_id  ==  e_id  )  dir="e";
  	else  if(  my_id  ==  w_id  )  dir="w";
	else  if(  my_id  ==  n_id  )  dir="n";
	else  if(  my_id  ==  s_id  )  dir="s";
	else  return  notify_fail("你并没有加入拱猪。\n");

	msg  =  "你手头的牌有：\n";

	j  =  0;
	for(i=0;  i<pai_size;  i++)
	{
		if(  (i==13  ||    i==26  ||  i==39  ||  i==52)  )  
		{
			msg  +=  "\n";
			j  =  0;  //started  another  kind  of  pai.
		}

		if(  pai_state[i]  ==  dir  )  
		{
			j++;
			msg  +=  pai_name[i];
			if(  j==7  &&  (i!=12&&i!=25&&i!=38&&i!=51)  )
			{
				j  =  0;
				msg  +=  "\n";
			}
		}
	}	

	write(msg+"\n\n");
	return  1;
}
