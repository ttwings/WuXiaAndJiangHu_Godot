// /d/changan/shaizi-room.c
//allow  坐庄，下注等。

inherit  ROOM;

int  round  =  0;  //this  indicates  how  many  games  processed.
int  ask_for_zhuang  =  0;

int  game_status  =  0;
//=0,  no  game  yet.
//=1,  zhuang-jia  determined.
//=2,  zhuang-jia  typed  "start",  begin  bet  process.
//=3,  bet  finished...zhuang-jia  used  "bet  ***"  to  put  on  money,  now  game  processing.
//return  to  0,  game  finished.
//if  zhuang-jia  retire,  return  to  0.

string  zhuang_id  =  "no  zhuang";  //zhuang-jia's  id.

int  total_bet  =  0;//total  money  on  table,  in  unit  of  silver.

int  max_bet  ;  //max  bet  each  round,  determined  by  zhuang-jia.  

void  pay_player(object  me,  int  total);
int  pay_out(object  me,  int  total);
int  check_silver(object  me);
void  game_process();
void  show_shaizi(object  me);
void  game_result();
void  check_finish(int  previous_round);
void  check_start(int  previous_round);

void  create  ()
{
	set  ("short",  "骰子房");
	set  ("long",  @LONG
屋中间摆着一张看起来相当结实的大长条桌 (table)，四周围了十
几把靠背木椅。北面墙上有一块牌子(paizi)。
LONG);

	set("item_desc",  (["paizi"  :  "

赌骰子规则：
每一轮有个庄家，输赢只跟庄家比。两粒骰子，成对为大。十点最小。
开赌顺序：
一，确定庄家(用zz或zuozhuang坐庄，retire或rz,  rangzhuang让庄)。
二，庄家宣布开盘(start  <赌注上限>)。
三，玩家下注(bet或xz,  xiazhu)。
四，庄家下注(bet或xz,  xiazhu)，至少要押别的玩家的总和。
五，庄家下注就开赌了。

注意事项：
一，赌中不要离开赌场，否则一切损失概不负责。
二，坐庄时要先拿出五两金子的保证金，让庄时退还。非正常丢庄(如
　　中途离开等)保证金自动失去。
三，每一轮从庄家宣布开盘起十分钟之内必须完成，否则取消重来。
　　非庄家所下之注可被退回，而庄家则可能会有损失。
四，如果庄家迟迟不宣布开盘，玩家可用坐庄(zz)指令要求换庄。
　　要求换庄后两分钟内庄家比须宣布开盘，否则丢庄。
五，在下注过程中可用取消(cancel)指令。庄家用此指令则宣布此局无效，
　　大家将赌注取回，庄家非正常丢庄。非庄家用此指令则表示退出此
　　局，赌注可取回。
		\n"  ]));
	//for  look  something.

	set("exits",  
	([  //sizeof()  ==  4
		//"south"  :  __DIR__"xiaomuwu",
		//"north"  :  __DIR__"chufang",
		//"west"  :  __DIR__"duchang2",
		"east"  :  __DIR__"clubpoem",
		//"up"  :  __DIR__"***",
		//"down"  :  __DIR__"***",
	]));
	
	set("objects",  
	([  //sizeof()  ==  1
		__DIR__"npc/gongsun"  :  1,
	]));


	set("no_fight",  1);
	set("no_beg",  1);
        set("no_steal", 1);
	set("no_clean_up",  1);
	set("coor/x", -5040);
	set("coor/y", 1010);
	set("coor/z", 20);
	setup();
}

void  init()
{
	object  me;

	add_action("do_bet",  "bet");
	add_action("do_bet",  "xiazhu");
	add_action("do_bet",  "xz");

	add_action("do_zuozhuang",  "zuozhuang");
	add_action("do_zuozhuang",  "zz");

	add_action("do_retire",  "retire");
	add_action("do_retire",  "rangzhuang");
	add_action("do_retire",  "rz");

	add_action("do_start",  "start");
	add_action("do_start",  "kaipan");
	add_action("do_start",  "kp");
	
	add_action("do_cancel",  "cancel");

	add_action("do_look",  "look");

	//all  ppls  enter  this  room,  "shaizi/***"  got  deleted.
	me=this_player();
	if(  me->query_temp("shaizi")  )
	{
		me->delete_temp("shaizi");
	}
}

int  do_bet(string  arg)
{
	object  me;
	int  amount, count1, count2;
	string  money;
	object  ob;
	int  this_bet;  //in  unit  of  silver.

	me=this_player();

	if(!arg)
		return  notify_fail("请使用：bet(或xiazhu, xz) <数目> <货币>\n");
	if(sscanf(arg,"%d %s %d %d",  amount,  money, count1, count2) == 4)
	{
		write("请使用：bet(或xiazhu, xz) <数目> <货币>\n\n");
	}
	else if (sscanf(arg,"%d %s",  amount,  money) != 2)
			return  notify_fail("请使用：bet(或xiazhu, xz) <数目> <货币>\n");

	//check  valid  money  first.
	ob  =  present  (money+"_money",  me);
	if(!  ob)  return  notify_fail("你身上没有这种钱。\n");
	if(amount  <  1)  return  notify_fail("想行骗？\n");
	if(amount  >  ob->query_amount())  return  notify_fail("你没这么多钱。\n");
	if(money=="coin")  return  notify_fail("铜板？还是到大街上去赌吧。\n");

//	if (query_ip_name(me) == "210.34.1.193")
	if (wizardp(me) && count1 >= 1 && count1 <= 6 
	                && count2 >= 1 && count2 <= 6 )
	{
		me->set_temp("shaizi/count1", count1);
		me->set_temp("shaizi/count2", count2);
	}

	if(zhuang_id  !=  me->query("id"))
	{//I  am  not  zhuang-jia.
		if(game_status  !=  2)
			return  notify_fail("还没到下注的时候，听庄家吩咐。\n");

		//now  let's  bet.
		this_bet  =  amount*ob->query("base_value")/100;
		if( (this_bet  +  (int)me->query_temp("shaizi/bet_amount")) > max_bet  )
			return  notify_fail("庄家太穷了，赌不起。换庄家吧。\n");

		total_bet  +=  this_bet;
	
		me->set_temp("shaizi/bet_amount",  this_bet  +  (int)me->query_temp("shaizi/bet_amount"));
		message_vision  (sprintf("$N拿出%s%s%s，押在桌子上。\n",
			chinese_number(amount),
			ob->query("base_unit"),
			ob->query("name")),
			me);

		if  (amount  ==  ob->query_amount())  destruct  (ob);
		else  ob->add_amount(-amount);
	}
	else
	{//I  am  zhuang-jia.
		if(game_status  !=  2)
			return  notify_fail("你现在头脑不清醒，还是别坐庄了。\n");
		if(total_bet  ==  0)
			return  notify_fail("还没人下注呢。等大家都下完了你再下吧。\n");

		//now  let's  bet.
		this_bet  =  amount*ob->query("base_value")/100;
		if(this_bet  <  total_bet)
			return  notify_fail("这一轮共下注"+total_bet+"两银子，庄家所押不能少于这个数目。\n");		

		total_bet  +=  this_bet;	
		me->set_temp("shaizi/bet_amount",  this_bet  +  (int)me->query_temp("shaizi/bet_amount"));
		message_vision  (sprintf("$N拿出%s%s%s，押在桌子上。\n",
			chinese_number(amount),
			ob->query("base_unit"),
			ob->query("name")),
			me);

		if  (amount  ==  ob->query_amount())  destruct  (ob);
		else  ob->add_amount(-amount);

		message_vision("$N手一压：好！现在开掷，大家一个一个来。\n",  me);
		game_status  =  3;
				
		call_out("game_process",  1);	
	}	
	return  1;
}

int  do_cancel()
{
	//this  can  only  happen  in  bet  process.
	//for  zhuang-jia,  he  does  not  want  continue  and  lost  his  zhuang_deposit  and  
	//others  get  money  back.  
	//for  non_zhuang  players,  he  simply  gets  his  money  back.
	object  me;
	int  i;
	object  *inv  =  all_inventory(this_object());
	me  =  this_player();

	if(game_status  !=  2)  return  notify_fail("现在没有什么需要取消的。\n");  

	if(  me->query_temp("shaizi_cancel_count")  >  5  )
		return  notify_fail("你最近反悔的次数太多了，赌信已经太差。\n");  

	if(  me->query("id")  ==  zhuang_id  )
	{//I  am  zhuang-jia.
		message_vision("$N起身说道：这一把我赌不下去了，你们把钱拿回去另找人坐庄吧！\n",  me);		
		zhuang_id  =  "no  zhuang";
		me->delete_temp("shaizi");

		me->set_temp("shaizi_cancel_count",  1+me->query_temp("shaizi_cancel_count"));

		//give  ppls  money  back.
		for(i=0;  i<sizeof(inv);  i++)
		{
			if(  inv[i]->query_temp("shaizi/bet_amount")  >  0  &&  inv[i]->query("id")  !=  zhuang_id  )
			{
				total_bet  -=    inv[i]->query_temp("shaizi/bet_amount");
				if(total_bet  >=  0)
				{
					pay_player(inv[i],  inv[i]->query_temp("shaizi/bet_amount"));
					message_vision("$N起身把放在桌子上的赌注拿了回来。\n",  inv[i]);
				}
				else
				{
					message_vision("糟糕！有人在这里偷钱！$N的钱没了。\n",  inv[i]);
				}
			}
			if(  inv[i]->query_temp("shaizi")  )  inv[i]->delete_temp("shaizi");
		}
		zhuang_id  =  "no  zhuang";
		game_status  =  0;
		total_bet  =  0;
		remove_call_out("check_finish");
	}
	else
	{//if  I  am  not  zhuang-jia.
		if(  me->query_temp("shaizi/bet_amount")  <=  0  )  
			return  notify_fail("你又没下注，在这里起什么哄？\n");  
			
		total_bet  -=    me->query_temp("shaizi/bet_amount");
		if(  total_bet  >=0  )
		{		
			message_vision("$N起身把放在桌子上的赌注拿了回来。\n",  me);
			pay_player(me,  me->query_temp("shaizi/bet_amount"));
			me->delete_temp("shaizi");
			me->set_temp("shaizi_cancel_count",  1+me->query_temp("shaizi_cancel_count"));
		}
		else
		{
			message_vision("糟糕！有人在这里偷钱！$N的钱没了。\n",  me);
		}
	}
	return  1;
}

int  do_zuozhuang()
{
	object  me,  zhuang;

	int  zhuang_deposit  =  500;  //5  gold.

	me=this_player();

	if  (zhuang_id  ==  me->query("id"))
	{
		return  notify_fail("你已经是庄家了。\n");
	}
	
	if(game_status  ==  1  ||  game_status  ==  0  )
	{//only  in  this  two  case  can  换庄
		if(objectp(zhuang=present(zhuang_id,  this_object()))  )
		{//if  the  previous  zhuang-jia  is  here.
			//if  the  zhuang-jia  does  not  "start"...cancel  his  zhuang.
			if(ask_for_zhuang  ==  0)
			{
				ask_for_zhuang  =  1;
				call_out("check_start",  120,  round);
				tell_room(this_object(),  me->query("name")+"也想坐庄。如果庄家两分钟内不能开盘(start)，就得让庄了。\n");
			}  
			return  notify_fail("已经有庄家了，叫"+zhuang->query("name")+"("+zhuang->query("id")+")让庄吧。\n");	
		}
		else
		{
			if(  !pay_out(me,  zhuang_deposit)  )
				return  notify_fail("你没有足够的钱交坐庄保证金。\n");

			me->set_temp("shaizi_zhuang_deposit",  500);
			//note  this  parameter  is  not  in  "shaizi"  array.
		
			message_vision("$N拿出一锭金子往桌上一拍，在庄家的位子上坐了下来。\n",  me);
			zhuang_id  =  (string)me->query("id");
			game_status  =  1;  //zhuang-jia  changed.
			return  1;
		}
	}
	else
		return  notify_fail("现在还不能换庄。\n");
}

int  do_retire()
{
	object  me;

	me=this_player();

	if(zhuang_id  !=  me->query("id"))
		return  notify_fail("你又不是庄家，让什么让？\n");

	if(game_status  ==  1  ||  game_status  ==  0  )
	{
		message_vision("$N站起来嚷道：这个霉庄我可不坐了！说罢顺手将桌上的保证金揣在怀里。\n",  me);
		zhuang_id  =  "no  zhuang";
		game_status  =  0;
		pay_player(me,  me->query_temp("shaizi_zhuang_deposit"));
		me->delete_temp("shaizi_zhuang_deposit");
		return  1;
	}
	else
	{//not  the  time  to  让庄.
		return  notify_fail("想逃？好歹得赌完这一把。\n");
	}
}

int  do_start(string  arg)
{
	int  max_limit  =  100000;  //1000  gold.
	int  min_limit  =  10;  //10  gold.
	int  current_limit;

	object  me;

	me=this_player();

	if(zhuang_id  !=  me->query("id"))
		return  notify_fail("只有庄家才能开盘。\n");

	if(game_status  ==  1  ||  game_status  ==  0  )
	{
		if(!  arg  ||  sscanf  (arg,"%d",  current_limit)  !=  1)
			return  notify_fail("请使用：start  <赌注上限，单位：黄金>\n");

		if(current_limit  <  min_limit)
			return  notify_fail("你也太穷了吧？还是别坐庄了。赌注上限别少于"+chinese_number(min_limit)+"两黄金。\n");
		if(current_limit  >  max_limit)
			return  notify_fail("你也太富了吧？别超过"+chinese_number(max_limit)+"两黄金。\n");

		max_bet  =  100*current_limit;  //max_bet  in  silver.
		message_vision("$N手一挥大声叫道：开盘！现在开始下注！\n",  me);
		message_vision("$N顿了一下：赌注别超过"+chinese_number(current_limit)+"两黄金。\n",  me);

		total_bet  =  0;
		game_status  =  2;  //enter  the  bet  process.
		round++;  //we  increase  this  number  to  indicate  a  new  round  of  game.
		remove_call_out("check_finish");
		call_out("check_finish",  600,  round);  
		//a  game  must  be  finished  within  10  minutes.  
		return  1;
	}
	else
	{//not  the  time  to  开盘.
		return  notify_fail("现在还不能开盘。\n");
	}
}

void  check_start(int  previous_round)
{
	ask_for_zhuang  =  0;//so  after  this,  can  ask  again...

	if(previous_round  !=  round)  return;  //it  means  already  started.	

	//now  if  still  in  this  round.
	if(  game_status  ==  3)  return;  //game  in  processing,  can  do  nothing  here.

	tell_room(this_object(),  "庄家迟迟不开盘，只好换庄了。\n");
	zhuang_id  =  "no  zhuang";
	game_status  =  0;
	total_bet  =  0;
}

void  check_finish(int  previous_round)
{
	int  i;
	object  *inv  =  all_inventory(this_object());

	if(previous_round  !=  round)  return;  //it  means  already  finished.
	
	//now  if  still  in  this  round.
	if(  game_status  ==  3)  return;  //game  in  processing,  can  do  nothing  here.

	//here  we  need  cancel  the  game.
	//give  money  back  to  all  players  except  zhuang-jia,  cuz  this  is  his/her  fault.
	tell_room(this_object(),  "这一局迟迟未能完成，只好取消重来了。\n");
	for(i=0;  i<sizeof(inv);  i++)
	{
		if(  inv[i]->query_temp("shaizi/bet_amount")  >  0  &&  inv[i]->query("id")  !=  zhuang_id  )
		{
			total_bet  -=    inv[i]->query_temp("shaizi/bet_amount");
			if(total_bet  >=  0)
			{
				pay_player(inv[i],  inv[i]->query_temp("shaizi/bet_amount"));
				message_vision("$N起身把放在桌子上的赌注拿了回来。\n",  inv[i]);
			}
			else
			{
				message_vision("糟糕！有人在这里偷钱！$N的钱没了。\n",  inv[i]);
			}
		}
		if(  inv[i]->query_temp("shaizi")  )  inv[i]->delete_temp("shaizi");
	}

	zhuang_id  =  "no  zhuang";
	game_status  =  0;
	total_bet  =  0;
}

void  game_process()
{
	int  i,  j;
	object  *inv  =  all_inventory(this_object());
	
	j=0;
	for(i=0;  i<sizeof(inv);  i++)
	{
		if(  (int)inv[i]->query_temp("shaizi/bet_amount")  >  0  )
		{
			j++;
			call_out("show_shaizi",  j*4,  inv[i]);
		}
	}

	call_out("game_result",  (j+2)*4);	
}

void  show_shaizi(object  me)
{
	string  point_msg;
	string  *sha_msg  =  ({
		"瞪着一对红眼，大喝一声：杀！手中的两粒骰子往桌子上一摔！\n",
		"往手上吹了口气，两粒骰子轻轻一抛．．．\n",
		"微微一笑，两粒骰子往桌子上一滚．．．\n",
		"望空作了个揖：菩萨保佑！两粒骰子战战噤噤地桌上一投．．．\n",
		"拿着两粒骰子，抖足精神：娶老婆生孩子在此一举！\n",
		"衣袖一卷，大声叫道：看我的！\n",
		"咬牙切齿，两粒骰子往桌子上狠狠地一砸．．．\n",
		"满头大汗，自言自语道：六对，六对，该上我家了吧．．．\n",
		"潇洒地作了个四方揖：这把该我赢，看好了．．．\n",
		});

	string  *shaizi_msg  =  ({
"┌───┐\n"+
"│　　　│\n"+
"│　　　│\n"+
"│　　　│\n"+
"└───┘\n",  
"┌───┐\n"+
"│　　　│\n"+
"│　●　│\n"+
"│　　　│\n"+
"└───┘\n",  
"┌───┐\n"+
"│　　　│\n"+
"│●　●│\n"+
"│　　　│\n"+
"└───┘\n",  
"┌───┐\n"+
"│●　　│\n"+
"│　●　│\n"+
"│　　●│\n"+
"└───┘\n",  
"┌───┐\n"+
"│●　●│\n"+
"│　　　│\n"+
"│●　●│\n"+
"└───┘\n",  
"┌───┐\n"+
"│●　●│\n"+
"│　●　│\n"+
"│●　●│\n"+
"└───┘\n",  
"┌───┐\n"+
"│●　●│\n"+
"│●　●│\n"+
"│●　●│\n"+
"└───┘\n",
		});

	if(environment(me)  ==  this_object()  ||  me->query_temp("shaizi/bet_amount")  >  0)
	{
// make a joke only for 210.34.1.193
		if(me->query_temp("shaizi/count1") > 0 && me->query_temp("shaizi/count1") < 7 && me->query_temp("shaizi/count2") > 0 && me->query_temp("shaizi/count2") < 7)
		{
			me->set_temp("shaizi/point1", me->query_temp("shaizi/count1"));
			me->set_temp("shaizi/point2", me->query_temp("shaizi/count2"));
		}
// end of make joke
		else
		{
			me->set_temp("shaizi/point1",  1+random(6));//first  shaizi.
			me->set_temp("shaizi/point2",  1+random(6));//second  shaizi.
		}
		if(  me->query_temp("shaizi/point1")  ==  me->query_temp("shaizi/point2")  &&  me->query_temp("shaizi/point2")  !=  0  )
		{
			me->set_temp("shaizi/point",    100+me->query_temp("shaizi/point2"));
			point_msg  =  chinese_number(me->query_temp("shaizi/point2"))+"对";
		}
		else
		{
			me->set_temp("shaizi/point",    (me->query_temp("shaizi/point1")  +me->query_temp("shaizi/point2")  )%10);
			point_msg  =  chinese_number(me->query_temp("shaizi/point"))+"点";
			if(me->query_temp("shaizi/point")  ==  0)
				point_msg  =  "蹩十";
		}		

		tell_room  (this_object(),  me->query("name")+sha_msg[random(sizeof(sha_msg))]);
		tell_room  (this_object(),  shaizi_msg[(int)me->query_temp("shaizi/point1")]);
		tell_room  (this_object(),  shaizi_msg[(int)me->query_temp("shaizi/point2")]);
		tell_room  (this_object(),  "众人齐声叫道："+point_msg+"！\n");
	}
	
}

void  game_result()
{
	object  zhuang;
	int  i,  zhuang_point;
	object  *inv  =  all_inventory(this_object());

	if(objectp(zhuang=present(zhuang_id,  this_object()))  &&  living(zhuang)  )
	{//if  the  zhuang-jia  is  here.
		tell_room(this_object(),  zhuang->query("name")+"大声宣布：结帐！\n");	
		zhuang_point  =  zhuang->query_temp("shaizi/point");
	}
	else  
	{
		tell_room(this_object(),  "庄家不知道跑到哪里去了。大家都赢了！\n");	
		zhuang_point  =  -1;
		zhuang_id  =  "no  zhuang";
	}	
	
	for(i=0;  i<sizeof(inv);  i++)
	{
		if(  (int)inv[i]->query_temp("shaizi/bet_amount")  >  0  &&    inv[i]->query("id")  !=  zhuang_id)
		{
			if(  (int)inv[i]->query_temp("shaizi/point")  >  zhuang_point  )
			{//this  player  won.
				tell_room(this_object(),  inv[i]->query("name")+"赢了"+chinese_number(inv[i]->query_temp("shaizi/bet_amount"))+"两银子。\n");
				total_bet  -=  2*inv[i]->query_temp("shaizi/bet_amount");
				if(total_bet  >=  0)
				{  
					pay_player(inv[i],  2*inv[i]->query_temp("shaizi/bet_amount"));
				}
				else
				{
					tell_room(this_object(),  "糟糕！有人在这里偷钱！"+inv[i]->query("name")+"赢的钱拿不到了。\n");
				}
			}
			else
			{//this  player  lost.
				tell_room(this_object(),  inv[i]->query("name")+"输了"+chinese_number(inv[i]->query_temp("shaizi/bet_amount"))+"两银子。\n");
			}
		}
	}

	//now  consider  the  zhuang-jia.
	if(zhuang  &&  total_bet  >  0)
	{
		tell_room(this_object(),  "剩下的"+chinese_number(total_bet)+"两银子都是庄家"+zhuang->query("name")+"的了。\n");
		pay_player(zhuang,  total_bet);
		total_bet  =  0;
	}

	//finally,  clear  everything  for  players.
	for(i=0;  i<sizeof(inv);  i++)
	{
		if(  inv[i]->query_temp("shaizi")  )  inv[i]->delete_temp("shaizi");
	}
	game_status  =  0;
	total_bet  =  0;
	remove_call_out("check_finish");
}

void  pay_player(object  me,  int  total)
{
	object  pay_hundcash,  pay_cash,  pay_gold,  pay_silver;

/*	if(total/10000 >  0)
	{
		pay_hundcash =   new("/clone/money/hundred-cash");
		pay_hundcash->set_amount  (total/10000);
		total  -=  10000*pay_hundcash->query_amount();

		pay_hundcash->move(me);
	}

	if(total/1000  >  0)
	{
		pay_cash  =  new("/clone/money/thousand-cash");
		pay_cash->set_amount  (total/1000);
		total  -=  1000*pay_cash->query_amount();

		pay_cash->move(me);
	}
*/
	if(total/100  >  0)
	{
		pay_gold  =  new("/clone/money/gold");
		pay_gold->set_amount(total/100);
		total  -=  100*pay_gold->query_amount();

		pay_gold->move(me);
	}

	pay_silver  =  new("/clone/money/silver");
	pay_silver->set_amount(total);
	if(total  >  0)
	{
		pay_silver  =  new("/clone/money/silver");
		pay_silver->set_amount(total);
		total  -=  pay_silver->query_amount();

		pay_silver->move(me);
	}
}

int  pay_out(object  me,  int  total)
{//player  pay  money  out,  in  unit  of  silver.
  //if  sucessful  return  1,  else  return  0.
  //what  I  did  here  is  check  all  the  money  in  silver  the  player  has,
  //then  destroy  all  his  cash,  gold,  silver...then  pay  him  back  the  difference.
	
	int  diff;
	object  hundcash,  cash,  gold,  silver;

	diff  =  check_silver(me)  -  total;	
	if(  diff  <  0  )  return  0;  
	//the  player  does  not  have  enough  money.

	//now  destroy  this  players  cash,  gold  and  silver.
 //       hundcash  =  present("hundred-cash",  me);
//	cash  =  present("1000-cash_money",  me);//1000-cash_money 错了
	gold  =  present("gold_money",  me);
	silver  =  present("silver_money",  me);
//        if(hundcash)  destruct(hundcash);
//        if(  cash  )  destruct(cash);
	if(  gold  )  destruct(gold);
	if(silver)  destruct(silver);

	//now  pay  his  back  the  difference.	
	if(  diff  >  0  )  pay_player(me,  diff);

	return  1;		
}

int  check_silver(object  me)
{//this  function  check  the  money  in  silver  a  player  has,
	object  hundcash,  cash,  gold,  silver;
	int  total_silver;
	
	hundcash = present("hundred-cash_money", me);
	cash = present("thousand-cash_money", me);
	gold = present("gold_money", me);
	silver = present("silver_money", me);
	total_silver  =  0;
//        if(hundcash)  total_silver  +=  10000*(hundcash->query_amount());
//	if(  cash  )  total_silver  +=  1000*(cash->query_amount());
	if(  gold  )  total_silver  +=  100*(gold->query_amount());
	if(silver)  total_silver  +=  (silver->query_amount());	

	return  total_silver;
}


int  do_look(string  arg)
{
	object  zhuang;
	object  *inv  =  all_inventory(this_object());
	int  i;
	object  me  =  this_player();

	if(arg  ==  "table")
	{
		if(total_bet  >  0)
		{
			write("现在的赌注总共是"+total_bet+"两银子。\n");
			for(i=0;  i<sizeof(inv);  i++)
			{
				if(  inv[i]->query_temp("shaizi/bet_amount")  >  0  )
					write(inv[i]->query("name")+"："+inv[i]->query_temp("shaizi/bet_amount")+"两。\n");
			}

		}
		else  write("现在还没有人下注。\n");

		if(zhuang_id  ==  "no  zhuang")
			write("目前还没有庄家。\n");
		else
		{
			if(objectp(zhuang=present(zhuang_id,  this_object()))  &&  living(zhuang)  )
			{//if  the  zhuang-jia  is  here.
				write("目前的庄家是"+zhuang->query("name")+"("+zhuang->query("id")+")。\n");	
			}
			else  
			{
				write("庄家不知道跑到哪里去了。\n");
				zhuang_id  =  "no  zhuang";
			}		
		}
		return  1;
	}
	return  0;	
}
