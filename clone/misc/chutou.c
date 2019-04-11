// /clone/misc/chutou.c
// Last modified by winder 2003.9.2

inherit ITEM;
#include <ansi.h>
int do_wajue();

void create()
{
	set_name(HIG"锄头"NOR, ({ "chu tou", "bao chu", "chu" }));
	set_weight(6000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "这是一把发着黑亮荧光的特制精钢锄头，你好象可以用它挖掘(wajue)什么东西。\n");
		set("wajue", 0);
//		set("no_sell",1);
//		set("no_drop",1);
/*		set("no_put",1);
		set("no_get",1);
		set("no_beg",1);
		set("no_steal",1);	
*/		set("value", 1000000);
		set("no_value",1); // drop时丢失
		set("material", "steel");
		 
	}
	
	setup();
}

void init()
{
        add_action("do_wajue", "wajue");
}

int do_wajue()
{
	int t, time;
	string *dir, target;
	object ob, me = this_player(), where = environment(me),obj;
//	return 1;
	t = time()-where->query_temp("wajue");
	time = where->query_temp("wajue1");

	if( me->is_busy() )
		return notify_fail("你上一个动作还没有完成！\n");
	if (!present("bao chu", me))
		return notify_fail("你没有锄头，怎么挖掘呀？！\n");
	
		
	if (!wizardp(me))
	{
		obj = present("chu tou", me);
		if ((int)me->query("jing") < 50)
			return notify_fail("你挖了半天，精力不够了！\n");
		if (!environment(me)->query("outdoors"))
			return notify_fail("在房子里你也想挖宝？！\n");
		if (present("bao wu",me))
			return notify_fail("你身上已经有宝物了，别太贪心！\n");
		if (me->query_temp("baowunum") >= 1)
		        return notify_fail("韦爵爷正派人四处寻你呢，还不快去？\n");
		if( t <= time && !(me->query_temp("invite") && random(2)==1))
			return notify_fail("这里已被人挖过，一会儿再来吧！\n");
		if (me->is_fighting()) 
			return notify_fail("现在正打得起劲，哪有空挖呢？！\n");
	}
	if (random(10) <= 6 )
	{
		printf(HIC"你拿出一把锄头，在地上挖了半天，什么也没有挖到。\n"NOR);
		t = (300 + random(10) );
		where->set_temp("wajue", time());    
		where->set_temp("wajue1", t);                
    if (random(30) <= 2)
    if (me->query_temp("invite")) me->start_busy(2); 
    else  me->start_busy(1);
		return 1;
	}
	else
	{ 
		printf( HIC"你拿出一把锄头，在地上挖了半天，突然你觉得好象挖到了什么。\n"NOR);   
		switch (random(10))
		{
			case 0:
			case 1:
			case 2:
				ob = new(__DIR__"baowu");
				ob->set("owner",me->query("id"));
				ob->move(me);
				tell_object(me, HIW"由于你辛勤的挖掘，你发现了一个宝物。\n"NOR);
				tell_object(me, HIW"恭喜你啦！\n"NOR);				
				me->add_temp("baowunum",1);
				break;
			case 3:
				dir = get_dir("/clone/food/fruit/");
				ob = new("/clone/food/fruit/"+dir[random(sizeof(dir))]);
//				ob->set("owner",me->query("id"));
				ob->move(me);
				tell_object(me, HIW"由于你辛勤的挖掘，你发现了一些东东。\n"NOR);
				break;
			case 4:
			case 5:
				dir = get_dir("/clone/medicine/vegetable/");
				ob = new("/clone/medicine/vegetable/"+dir[random(sizeof(dir))]);
				if(ob->query("id")=="lingzhi"||ob->query("id")=="fuxin cao"||ob->query("id")=="xuelian")
				{
				message_vision("哇，$N挖到了一个茅坑。\n", me);
				tell_object(me,"这么快就连茅坑都能挖出来，佩服啊佩服。\n");
				break;
				}
//				ob->set("owner",me->query("id"));
				ob->move(me);
				tell_object(me, HIW"由于你辛勤的挖掘，你发现了一些药材。\n"NOR);
				break;
			case 6:
/*
				message_vision("哎呀不好，$N挖到蛇窝了！一条毒蛇从洞里钻了出来。\n", me);
				tell_object(me,"还不快跑？\n");
				ob = new("/clone/animal/snake");
				ob->move(environment(me));
				break;
*/
			case 7:
/*
				message_vision("一锄头下去，$N挖出一窝兔子。\n", me);
				ob = new("/clone/animal/yetu");
				ob->move(environment(me));
				break;
*/
			case 8:
				message_vision("哇，$N挖到了一个茅坑。\n", me);
				tell_object(me,"这么快就连茅坑都能挖出来，佩服啊佩服。\n");
				break;
			default:
				message_vision("哇，$N挖出了一口井。\n", me);
				tell_object(me,"可惜挖的地方不对，这井除了冒烟，什么也不会。\n");
		}
		
		t = ( 30 + random(10) ) * 100;
		where->set_temp("wajue", time());    
		where->set_temp("wajue1", t);	  
		me->receive_damage("jing", 20);
		return 1;
	}
}

