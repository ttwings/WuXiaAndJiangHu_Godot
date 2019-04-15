// Last Modified by Winder on May. 15 2001
// fruit.c

#include <ansi.h>
#include <dbase.h>

int is_food()
{
	return 1;
}
void init()
{
	if (!query("decay") && userp(environment()))
	{
		set("decay", 1);
		remove_call_out("stats");
		call_out("stats", 280,0);
	}
  add_action("do_eat", "eat");
}
int do_eat(string arg)
{
	mapping gifts;
	object me = this_player();
	object ob = this_object();
	object core;
	string msg, *list;
	int i, temp, sign;

	if( !living(this_player()) || this_player()->query_temp("noliving") )
		return 1;
	if( me->query("jing") < 0 || me->query("qi") < 0 )
		return notify_fail("你太累了，实在没力气吃什么了。\n");
	if( !this_object()->id( arg ) ) return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");
	if( me->is_fighting() )
		me->start_busy(2);
	if( !query( "fruit_remaining" )  )
		return notify_fail("你拿着这个" + ob->name() + "，看了半天觉得无处下嘴。\n");
	if( (int)me->query("water") >= (int)me->max_food_capacity() ||
		(int)me->query("food") >= (int)me->max_water_capacity() )
	{
		if ( msg = query( "over_msg" ) ) notify_fail( msg );
		else notify_fail("吃那么多？？真贪心，小心撑死了……\n");
		return 0;
	}
	add( "fruit_remaining", -1);
	set( "value", 0);
	if ( query( "fruit_remaining" ) )
	{
		me->add("food" ,  query( "food_supply" ) );
		me->add( "water" , query( "water_supply" ) );

// hamlet的想法：食物对天赋有影响 (trill)
// 可以在food,fruit等加个mapping gifts
// 这样对gifts有影响

		if ( gifts = query("gifts") )
		{
			list = keys( gifts );
			for( i = 0; i < sizeof( list ); i ++ )
			{
				me->add( "hamlet_food/" + list[ i ],
					query("gifts/" + list[ i ] ) );
				temp = me->query( "hamlet_food/" + list[ i ] );
				sign = ( temp > 0 ) ? 1 : -1 ;
				temp *= sign;
				if (temp >= 500  && random( 2000 - temp ) == 0 && me->query("age")<22)
				{
//如果这个player年纪小<22，就改善先天的天赋
//否则 只影响后天的天赋就 query_per()这类了..
//现在这个东西太麻烦，而且我们对先天后天的天赋使用没有明确的概念
//所以我就把它都改成先天的了。——lala，１９９８－０１－０７

//原来的奖励可以吃到30 30 35 35 的天赋 进行了限制
//-- qingyun 2004.10.13
//这个东西是别的mud的吧
//原本是建立在不能迅速降食物基础上，因为侠客行有沙漠
//这个东西等同于送天赋给知道的人 
					if (me->query(list[i])>=30 )
						sign = 0;
					if (me->query("gift/hamlet/"+list[i])>0)
						sign=0;
					if (me->query(list[i])<10 )
						sign = 0;
					if (sign>0)
					{
						me->add("gift/hamlet/"+list[i],1);
						me->add( list[ i ] , sign );
						me->set( "hamlet_food/" + list[ i ], 0);
						tell_object( me, YEL"由于你日常的饮食习惯而造成了你天赋的改变！\n"NOR );
					}
				}
			}
		}
		if ( msg = query( "eat_msg" ) ) message_vision( msg, me, ob );
		else message_vision( RED"$N拿起$n，狠狠地咬了几口，大赞道：味道好极了！\n" NOR, me, ob);
	}
	else
	{
//吃到最后一口就变成个水果核
		if ( msg = query ("end_msg" ) ) message_vision( msg , me, ob );
		else message_vision(RED"$N吃完最后一口$n，心满意足的说：真不错。\n", me,ob);
		if ( query("core") )
		{
			core = new( "/clone/misc/core.c" );
			core->set_name(query("core"), query("core_id") );
			if ( query("core_unit") )
				core->set("unit", query("core_unit"));
			else core->set("unit", query("unit") );
			if ( query("core_long") )
				core->set("long", query("core_long") );
			core->move( environment( this_object() ) );
		}
		remove_call_out( "stats" );
		destruct( this_object() );
	}
	return 1;
}

int stats( int i )
{
	string base_long, base_name;
	object core, env;
	int life;

//	if( !life = query( "life" )*240  ) return -1;
		if( !life = query( "life" )*20  ) return -1;

	switch ( i )
	{
		case 0:
			set("base_long", query("long") );
			set("base_name", query("name") );
			call_out("stats", life/4, 1);
			break;
		case 1:
			base_long = query("base_long");
			set("long",base_long+"，上面好象有些斑点，不过还不算显眼。\n");
			call_out("stats", life/4, 2);
			break;
		case 2:
			base_name = query("base_name");
			base_long = query("base_long");
			set("name","有点烂了的"+base_name );
			set("long",base_long+"，可惜已经开始烂了。\n");
			call_out("stats", life/4, 3);
			break;
		case 3:
			base_name = query("base_name");
			base_long = query("base_long");
			set("name", "烂" + base_name );
			set("long",base_long+"，可惜已经烂了，散发出一股异味。\n");
			call_out("stats", life/4, 4);
			break;
		default :
			if ( query("core") )
			{
				core = new( "/clone/misc/core.c" );
				core->set_name(query("core"), query("core_id"));
				if ( query("core_unit") )
					core->set("unit", query("core_unit"));
				else
					core->set("unit", query("unit") );
				if ( query("core_long") )
					core->set("long", query("core_long") );
				if ( env = environment( this_object() ) )
					core->move( env );
			}
			tell_room( environment(this_object()), this_object()->query("name")+"终于完全烂掉了。\n" );
			destruct( this_object() );
			break;
	}
	return i;
}
