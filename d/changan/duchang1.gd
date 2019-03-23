# // /d/changan/duchang1.c
 
# inherit  ROOM;
extends Room

var room_status  =  0;
#var res  =  allocate(5);

#var random2  (var i)
#{
#    return  (random(i)+uptime())  %  i;
#}

var qians  =  {
	"dqq"  :  "大乾签",
	"dkq"  :  "大坤签",
	"xqq"  :  "小乾签",
	"xkq"  :  "小坤签",
	"qq"   :  "乾签",
	"kq"   :  "坤签",
};

func create():
	set("short",  "押签房");
	set("long",
"""一群人围着紫檀木大桌而坐，首席座着一位精瘦的签客，正在一本
正经地从镶金黑盒里慢悠悠一根一根往外抽出乾坤签，码在桌面上。

	墙上有一匾写着：
		大乾签（全部五根皆为乾签）：一赢三十二
		大坤签（全部五根皆为坤签）：一赢三十二
		小乾签（连续四根皆为乾签）：一赢十六
		小坤签（连续四根皆为坤签）：一赢十六
			乾签（任意三根皆为乾签）：一赢二
			坤签（任意三根皆为坤签）：一赢二

	匾角有一个牌子(paizi)。"""
);

	set("item_desc",{
#		押大乾签：  qian dqq <amount> <money>,
#		押大坤签：  qian dkq <amount> <money>,,
#		押小乾签：  qian xqq <amount> <money>\n
#		押小坤签：  qian xkq <amount> <money>\n
#		押乾签：    qian qq <amount> <money>\n
#		押坤签：    qian kq <amount> <money>\n\n
#		为免破产跳楼  限押一两黄金\n""",
		});
	set("exits",  {
		"east"  :  __DIR__ + "clubup",
		});
	set("objects",  {
		__DIR__ + "npc/qianke"  :  1,
		});
	set("light_up",  1);
	set("no_fight",  1);
	set("no_beg",  1);
	set("coor/x", -5040);
	set("coor/y", 1010);
	set("coor/z", 10);
	setup();

# void  init  ()
# {
#     add_action  ("do_qian","qian");

#     if  (room_status  >  0)
#         return;

#     remove_call_out  ("gamble_prepare");
#     remove_call_out  ("gamble_start");
#     remove_call_out  ("gamble_perform");
#     remove_call_out  ("gamble_finish");
#     call_out  ("gamble_prepare",2);
#     room_status  =  1;
# }

# var do_qian  (string  arg)
# {
#     object  me  =  this_player();
#     string  what;
#     var amount;
#     string  money;
#     object  ob;

#     if  (!arg  ||
#             sscanf(arg,"%s %d %s",what,amount,money)  !=  3)
#         return notify_fail("请使用：  qian <押签种类> <数目> <货币>\n");

#     if  (what  !=  "dqq"  &&
#             what  !=  "dkq"  &&
#             what  !=  "xqq"  &&
#             what  !=  "xkq"  &&
#             what  !=  "qq"  &&
#             what  !=  "kq")
#         return  notify_fail("你要押什么签？\n");

#     ob  =  present  (money+"_money",  me);
#     if  (!  ob)
#         return  notify_fail("你身上没有这种货币。\n");
#     if  (amount  <  1)
#         return  notify_fail("请多押一些钱。\n");
#     if  (amount  >  ob->query_amount())
#         return  notify_fail("你身上的钱不够押。\n");
#     if  (amount * (ob->query("base_value")) > 10000 )
#         return  notify_fail("你想豪赌啊，拜托！官兵就上来了。\n");

#     if  (me->query_temp  ("gamble_qian/amount")  >  0)
#         return  notify_fail("你已经押过了。\n");

#     if  (room_status  >  1)
#         return  notify_fail("现在正在赌呢，稍等片刻。\n");

#     me->set_temp("gamble_qian/kind",what);
#     me->set_temp("gamble_qian/amount",amount);
#     me->set_temp("gamble_qian/money",money);
#     message_vision  (sprintf("$N拿出%s%s%s，押在%s上。\n",
#                                                     chinese_number(amount),
#                                                     ob->query("base_unit"),
#                                                     ob->query("name"),
#                                                     qians[what},
#                                     me);
#     if  (amount  ==  ob->query_amount())
#         destruct  (ob);
#     else
#         ob->add_amount(-amount);

#     return  1;
# }

# var valid_leave(object  me,  string  dir)
# {
#     if  (dir  ==  "east")
#     {
#         if  (me->query_temp  ("gamble_qian/amount")  >  0)  
#             message_vision  ("$N扔下押签的钱。\n",me);
#         me->delete_temp("gamble_qian");
#     }
#     return  ::valid_leave(me,dir);
# }

# void  gamble_prepare  ()
# {
#     object  room  =  this_object();
#     object  *inv;
#     var i;

#     tell_room  (room,"签客将一大束签在桌上哗啦啦地迅速洗了一遍。\n");
#     tell_room  (room,"洗签之后，签客啪地一声将签装入镶金黑盒，叫道：开押！\n");
    
#     inv=all_inventory();
#     i=sizeof(inv);
#     while(i--)  {
#             if(userp(inv[i})  {
#                   room_status  =  1;
#                   call_out  ("gamble_start",25);
# 	  return;
#             }
#     }
#     room_status=0;
#     return;
# }
  
# void  gamble_start  ()
# {
#     object  room  =  this_object();
#     tell_room  (room,"签客喊声：停押！\n");
#     tell_room  (room,"然后闭上眼睛，将镶金黑盒打开从里开始往外抽签。\n");
#     room_status  =  2;
#     call_out  ("gamble_perform",3,0);
#     call_out  ("gamble_perform",6,1);
#     call_out  ("gamble_perform",9,2);
#     call_out  ("gamble_perform",12,3);
#     call_out  ("gamble_perform",15,4);
#     call_out  ("gamble_finish",18);
# }

# void  gamble_perform  (var i)
# {
#     object  room  =  this_object();

#     switch  (random2(2))
#     {
#         case  0:
#         {
#             tell_room  (room,"\n□□    坤    签    □□\n");
#             res[i]  =  0;
#             break;
#         }
#         case  1:
#         {
#             tell_room  (room,"\n□□    乾    签    □□\n");
#             res[i]  =  1;
#             break;
#         }
#     }
# }

# void  player_wins  (object  who,  var total)
# {
#     object  money  =  new  ("/clone/money/"+who->query_temp("gamble_qian/money"));
#     var amount  =  who->query_temp("gamble_qian/amount");
#     total  =  total  *  amount;
#     money->set_amount(total);
#     message_vision  (sprintf("$N赢了%s%s%s！\n",
#                                                     chinese_number(total),
#                                                     money->query("base_unit"),
#                                                     money->query("name")),
#                                     who);
#     money->move(who);
# }

# void  player_loses  (object  who,  var total)
# {
#     object  money  =  new  ("/clone/money/"+who->query_temp("gamble_qian/money"));
#     total  =  who->query_temp("gamble_qian/amount");
#     message_vision  (sprintf("签客将$N押在盘中的%s%s%s收走。\n",
#                                                     chinese_number(total),
#                                                     money->query("base_unit"),
#                                                     money->query("name")),
#                                     who);
#     destruct  (money);
# }

# void  gamble_finish  ()
# {
#     string  win;
#     var total,  i;
#     object  room  =  this_object();
#     object  *list  =  all_inventory(room);
#     if  (res[0]==1  &&  res[1]==1  &&  res[2]==1  &&  res[3]==1  &&  res[4]==1)
#     {
#         total  =  32;
#         win  =  "dqq";
#     }
#     else  if  (res[0]==0  &&  res[1]==0  &&  res[2]==0  &&  res[3]==0  &&  res[4]==0)
#     {
#         total  =  32;
#         win  =  "dkq";
#     }
#     else  if  ((res[0]==1  &&  res[1]==1  &&  res[2]==1  &&  res[3]==1)  ||
#                       (res[1]==1  &&  res[2]==1  &&  res[3]==1  &&  res[4]==1))
#     {
#         total  =  16;
#         win  =  "xqq";
#     }
#     else  if  ((res[0]==0  &&  res[1]==0  &&  res[2]==0  &&  res[3]==0)  ||
#                       (res[1]==0  &&  res[2]==0  &&  res[3]==0  &&  res[4]==0))
#     {
#         total  =  16;
#         win  =  "xkq";
#     }
#     else  
#     {
#         var r  =  0;
#         total  =  2;
#         for  (i  =  0;  i  <  5;  i++)
#             r  +=  res[i];
#         if  (r  >=  3)
#             win  =  "qq";
#         else
#             win  =  "kq";
#     }
#     tell_room  (room,"\n签客睁开眼睛，迅速看一眼桌面，叫道："+qians[win]+"！\n");
#     i  =  sizeof(list);
#     while  (i--)
#     {
#         if  (!userp(list[i})
#             continue;
#         if  (list[i]->query_temp("gamble_qian/kind")  ==  win)
#             player_wins(list[i],total);
#         else  if  (list[i]->query_temp("gamble_qian/kind"))
#             player_loses(list[i],total);
#         list[i]->delete_temp("gamble_qian");
#     }
#     tell_room  (room,"\n");
#     call_out  ("gamble_prepare",5);
# }
