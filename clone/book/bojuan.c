// bojuan.c

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;
int do_study(string arg);

void init()
{
	add_action("do_study", "yanxi");	
}
void create()
{
	set_name("帛卷", ({ "bo juan", "bo", "juan" }));
	set_weight(50);
	set("no_drop", "这样东西不能离开你。\n");
        set("unit", "卷");
        set("long", "这是一卷帛卷，里面写着 ：\n庄子“逍遥游”有云：穷发之北有冥海者，天池也。有鱼焉，其广数千里。。。。\n似乎你通过(yanxi)会有所领悟.\n");
	set("value", 500);
	set("material", "silk");
	setup();
}


int do_study(string arg)
{
	object me = this_player();
	int cost=10,myskill;	

	if ( arg != "bo" && arg != "juan" && arg !="bo juan" )
		return notify_fail("你要读什么？\n");
	if( (int)me->query("jing") < 25 )
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}
	if (me->is_busy()) return notify_fail("你现在正忙着呢。\n");
	if (me->query("family")==0||me->query("family")["family_name"]!="逍遥派") 
		return notify_fail("想学更高深的北冥神功，必须加入我逍遥派。\n");
	if ( me->is_fighter()) return notify_fail("战斗中无法阅读新知！\n");

	if ( (int)me->query_skill("beiming-shengong",1) >= 20 &&
		(int)me->query_skill("beiming-shengong",1) <= 100 )
	{
	    if ((int)me->query("jing")>cost)
	       	{ myskill=(int)me->query_skill("beiming-shengong",1);
               	  if (myskill*myskill*myskill/10>(int)me->query("combat_exp") )
                   {  return notify_fail("也许是缺乏实战经验，你对帛卷上所说的东西总是无法领会!\n");
                    }
              	  else  
                      { me->receive_damage("jing", 20);
			me->improve_skill("beiming-shengong", (me->query_skill("beiming-shengong",1)+me->query("int")));
			message_vision("$N正在专心研读北冥神功心法。\n", me);
			return 1;
                       }
		}
	    else
		{
			cost=me->query("jing");
			write("你现在过于疲倦，无法专心下来研读北冥神功心法。\n");
		}
	}
	if ((int)me->query_skill("beiming-shengong",1) > 100 )
	{
		return notify_fail("你对着帛卷看来看去，无法从中领悟出更高深的道理。\n");
	}
	return notify_fail("你对着帛卷看来看去，没看出什么道理出来。\n");
}


