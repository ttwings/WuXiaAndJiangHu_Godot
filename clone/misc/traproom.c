// Room: /clone/room/traproom.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit ROOM;

void falldown(object);
void flydown(object);
int do_jump(string);
int do_climb(string);
int do_push(string);
int do_fill();
void maintaining(object, int);
int trap_power(object);

void create()
{
	set("short",HIR "陷阱" NOR);
	set("long", HIR @LONG
这是一口不知是谁挖掘的陷阱。陷阱深达数丈，由下往上望去，只
能见到桌面般大的一片天空。陷阱周围是松软的土层，不停地往外渗水。
似乎刚刚挖好没多久。
LONG NOR
);      
	set("invalid_startroom",1);
	set("trap_room",1);
	setup();
	call_out("maintaining", 30, this_object(), 0);
}

void init()
{
	int depth, power, reward;
	object me = this_player();
	object roomtrap = this_object();
	object owner = roomtrap->query("owner");

	depth = roomtrap->query("depth");
	power = trap_power(me);

	if( me->query_temp("is_riding") ) me->delete_temp("is_riding");
	remove_call_out("maintaining");
	call_out("maintaining", 30, roomtrap, 0);

	if( depth > power && owner != me && roomtrap->query("limit") &&
		!me->query_temp("trap/" + file_name(roomtrap)) )
	{
		me->set_temp("trap/" + file_name(roomtrap));
		call_out("falldown", 1, me);

		if( objectp(owner) && userp(me) &&
			environment(owner) == roomtrap &&
			roomtrap->query("limit") >= 1)
		{
			reward = me->query("combat_exp")/300;
			if( reward >= 40 ) reward = 40;
			owner->add("combat_exp", reward);

			reward = me->query("shen")/300;
			if( reward >= 10 ) reward = 10;
			owner->add("shen", - reward);
		}
		if( roomtrap->query("limit") >= 1) roomtrap->add("limit", -1);
		if( depth / 5 > power ) me->unconcious();
	}
	else call_out("flydown", 1, me);
// tell_object(me, HIY "power = " + power + "\n" NOR);

	add_action("do_jump", "tiao");
	add_action("do_climb", "pa");
	add_action("do_push", "tui");
	add_action("do_fill", "tian");

	add_action("do_jump", "jump");
	add_action("do_climb", "climb");
	add_action("do_push", "push");
	add_action("do_fill", "fill");
}

void falldown(object me)
{
	object rum_ob;
	object owner = this_object()->query("owner");

// To noisy. 
	if( !objectp(rum_ob = find_object("/d/city/npc/aqingsao")) )
		rum_ob = load_object("/d/city/npc/aqingsao");
	CHANNEL_D->do_channel(rum_ob, "rumor",
		sprintf("%s掉进陷阱里了。", me->name(1)));
//
	message("vision", HIY "只听哇地一声喊，从上边掉下一团黑影来！\n" NOR, environment(me), me);
	tell_object(me, HIR "你只觉得脚下一虚，大叫一声，摔了下去！\n" NOR);
	me->start_busy(3+random(5));
	if( present(owner, environment(me)))
	{
		owner->start_busy(3+random(5));
	}
}

void flydown(object me)
{       
	if( random(5) == 0 )
	message("vision", "只见人影一闪，" + me->name() + "已经站在你的面前！\n", environment(me), me);
}

int valid_leave(object me, string dir)
{
	int power, depth;
	mapping exit;
	object roomtrap = this_object();

	if( roomtrap->query("owner") == me ) return ::valid_leave(me, dir);
	if( me->query("race") == "飞禽" ) return ::valid_leave(me, dir);
//      if( !roomtrap->query("limit") )	 return ::valid_leave(me, dir);

	depth = roomtrap->query("depth");
	power = trap_power(me);
	if(me->is_busy())
		return notify_fail("你现在正忙着呢。\n");

	if( depth / 3 > power )
	{
		return notify_fail("陷阱太深了，你怎么闯也闯不出去，看来得请人来把你推（ＴＵＩ）出去了。\n");
	}
	else
		if( depth / 2 > power)
		{
			return notify_fail("陷阱很深，你得试试能不能爬（ＰＡ）出去。\n");
		}
		else
			if( depth > power )
			{
				return notify_fail("陷阱看来挺深的，你得试试能不能使劲跳（ＴＩＡＯ）出去。\n");
			}
			
			else if( !mapp(exit = roomtrap->query("exits")) || !stringp(exit[dir]) )
       {
         return notify_fail("这个方向没有路。\n");
       }
			else
			{
				me->receive_damage("qi", depth/20, "在陷阱里累死了");
				message_vision("$N长袖飘飘，姿态美妙地从陷阱上方飞跃而过。\n", me);
				return ::valid_leave(me, dir);
			}
}

int do_jump(string arg)
{
	int depth, power;
	object me, roomtrap, roomto;

	me = this_player();
	roomtrap = this_object();

	depth = roomtrap->query("depth");
	power = trap_power(me);

	if( !arg || !environment(me)->query("exits/" + arg) )
		return notify_fail("你要往哪个方向跳越？\n");
	if(!( roomto = find_object(roomtrap->query("exits/" + arg)) ) )
		roomto = load_object(roomtrap->query("exits/" + arg));
	if( depth < power )
		return notify_fail("以你的本领，用得着这么费事吗？\n");
	if(me->is_busy())
		return notify_fail("你现在正忙着呢。\n");
	if(depth > power && depth/2 < power && me->query("qi") >= depth/10 )
	{
		me->receive_damage("qi", depth/10, "在陷阱里累死了");
		if( random(me->query_kar() + me->query_dex()) >= 15 )
		{
			me->move(roomto);
			message_vision("$N展开轻功，猛一纵身，嗖地从陷阱里跃了出去。\n", me);
			return 1;
		}
		else
		{
			message_vision("$N使劲猛地一跳，半空中一口气接不上来，又重重地摔了下来。\n", me);
			return 1;
		}
	}
	else return notify_fail("你有这个力气吗？\n");

	if( depth / 2 > power && depth / 3 < power )
	return notify_fail("看来跳是不成的了，试试能不能爬上去？\n");
	return notify_fail("陷阱太深了，看来一定得喊人来救你出去了。\n");
}

int do_climb(string arg)
{
	int depth, power;
	object me, roomtrap, roomto;

	me = this_player();
	roomtrap = this_object();

	depth = roomtrap->query("depth");
	power = trap_power(me);

	if( !arg || !environment(me)->query("exits/" + arg) )
		return notify_fail("你要沿哪个方向爬上去？\n");
	if(!( roomto = find_object(roomtrap->query("exits/" + arg)) ) )
		roomto = load_object(roomtrap->query("exits/" + arg));
	if( depth < power )
		return notify_fail("以你的本领，用得着这么费事吗？\n");
	if( depth > power && depth / 2 < power )
		return notify_fail("陷阱并不深，不妨施展轻功，试试能不能跳上去？\n");
	if(me->is_busy()) return notify_fail("你现在正忙着呢。\n");
	if( depth /2 > power && depth/3 < power && me->query("qi") >= depth/5 )
	{
		me->receive_damage("qi", depth/5, "爬陷阱累死了");
		if( random(me->query_kar() + me->query_str()) >= 15 )
		{
			me->move(roomto);
			message_vision("$N抓住陷阱边上的草根和树枝，手脚并用地慢慢爬了出去。\n", me);
			return 1;
		}
		else
		{
			message_vision("$N慢慢地往上爬着爬着，忽然坪的一声，狼狈不堪地摔了下来。\n", me);
			return 1;
		}
	}
	else return notify_fail("你有这个力气吗？\n");
	return notify_fail("陷阱太深了，看来一定得喊人来救你出去了。\n");
}

int do_push(string arg)
{
	object me, ob, roomtrap, roomto;
	int depth, power_me, power_ob;
	string who, where;

	me = this_player();
	roomtrap = this_object();

	if( !arg || sscanf(arg, "%s %s", who, where)!=2 ) 
		return notify_fail("指令格式：tui <人物> <方向>\n");
	if( !objectp(ob = present(who, environment(me))) || !living(ob))
		return notify_fail("你要推谁上去？\n");
	if(me->query("id")==who)
		return notify_fail("自己推自己上去？好象不行吧。\n");

	depth = roomtrap->query("depth");
	power_me = trap_power(me);
	power_ob = trap_power(ob);

	if( !environment(me)->query("exits/" + where) )
		return notify_fail("你要沿哪个方向推"+ob->name()+"上去？\n");
	if(!( roomto = find_object(roomtrap->query("exits/" + where)) ) )
		roomto = load_object(roomtrap->query("exits/" + where));
	if( depth > power_me || me->query("qi") < depth/5 )
		return notify_fail("你没这个本事推"+ob->name()+"上去吧？\n");
	if(me->is_busy())
		return notify_fail("你现在正忙着呢。\n");
	me->receive_damage("qi", depth/5, "救人出陷阱时累死了");
	if( random(me->query_str() + ob->query_kar()) >= 15 )
	{
		ob->move(roomto);
		me->move(roomto);
		message_vision("$N轻轻托起$n，鼓足内力，一下就把$n送出了陷阱。接着一纵身，自己也跃了出去。\n", me, ob);
		return 1;
	}
	else
	{
		message_vision("$N托住$n想把$n送出陷阱，结果$N手一软，两人都摔倒在地。\n", me, ob);
		return 1;
	}
	return notify_fail("陷阱太深了，看来得另想办法。\n");
}

int do_fill()
{
	object me, roomtrap, roomto, roomfrom, *inv;
	int depth, power_me, i;

	me = this_player();
	roomtrap = this_object();
	roomfrom = roomtrap->query("roomfrom");
	roomto = roomtrap->query("roomto");

	depth = roomtrap->query("depth");
	power_me = trap_power(me);

	if( (depth*2 > power_me || me->query("qi") < depth/3) &&
		me != roomtrap->query("owner") )
		return notify_fail("这个陷阱太深了，想填住它，非累死不可。\n");
	me->receive_damage("qi", depth/3, "填陷阱时累死了");
	message_vision("$N满头大汗地挑泥担水，把陷阱严严实实地填了起来。\n\n", me);
	roomfrom->set("exits/" + roomtrap->query("from"), file_name(roomto));
	roomto->set("exits/" + roomtrap->query("to"), file_name(roomfrom));     
	roomfrom->delete("exits/jump" + roomtrap->query("from"));
	roomto->delete("exits/jump"  + roomtrap->query("to"));
	
	inv = all_inventory(environment(me));

	if( sizeof(inv) >= 1 )
	{
		for(i=0; i<sizeof(inv); i++)
		{
			if( !living(inv[i]) || inv[i] == me ) continue;
			else inv[i]->move(roomto);
		}
	}

	me->move(roomto);
	destruct(roomtrap);

	return 1;
}

int trap_power(object me)
{
	return  me->query_skill("dodge")*5
		+ me->query_dex()*4
		+ me->query_int()*3
		+ me->query_kar()*2
		+ me->query("qi");
}

void maintaining(object roomtrap, int count)
{
	object owner, roomfrom, roomto;
  int i;
  object *inv;
	roomfrom = roomtrap->query("roomfrom");
	roomto = roomtrap->query("roomto");

	if( objectp(owner = roomtrap->query("owner")) && count < 10 )
	{ 
/*		if( environment(owner) == roomtrap ||
			environment(owner) == roomfrom ||
			environment(owner) == roomto )
			count = 0;
		else */count++;
		call_out("maintaining", 120, roomtrap, count);
	}
	else
	{
		roomfrom->set("exits/"+roomtrap->query("from"),file_name(roomto));
		roomto->set("exits/"+roomtrap->query("to"),file_name(roomfrom));
		roomfrom->delete("exits/jump" + roomtrap->query("from"));
		roomto->delete("exits/jump"  + roomtrap->query("to"));
		inv=all_inventory(roomtrap);
    tell_room(roomtrap,"这时候走过来一个中年汉子，见你掉在陷阱里面，就找了条绳子把你拉了上来。\n随后你们一起把这个害人的陷阱严严实实地填了起来。\n");
		for (i=0;i<sizeof(inv);i++)
			if (!living(inv[i])) continue;
			else inv[i]->move(roomfrom);
		destruct(roomtrap);
	}
}
