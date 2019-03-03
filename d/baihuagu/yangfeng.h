// yangfeng.h
#include <ansi.h>
int do_yang(string arg)
{
	object bee;
	object me,obj;
	int c,qufeng;

	me=this_player();
	seteuid(getuid());
	if(!arg)
		return notify_fail("你想养什么？\n");
	if(arg != "yu bee" || arg != "yu bee")
		return notify_fail("你只能养玉蜂。\n");
	if(me->is_busy()||me->query_temp("marks/bee1"))
		return notify_fail("你正忙着呢。\n");
	if ( present("mi", me) )
		return notify_fail("你正拿着蜂蜜呢，还是先交给老顽童吧。\n");
//	bee=new("/d/baihuagu/npc/yubee");
//	bee->move(environment(this_player()));
//	me->set_leader(bee);
//	bee->set_leader(me);
	message_vision( HIY"$N打开一个蜂箱，里面忽的飞出一群玉蜂。$N傻笑一声，开始和蜜蜂玩耍。\n"NOR, me, obj);
	qufeng = me->query_skill("qufeng",1);
	c=20;
	if (wizardp(me)) c=3;
	else if (qufeng > 50 ) c = c * 50  / qufeng; // 200级就是 1/4
	me->apply_condition("yubee", c);
	me->set_temp("marks/bee1",1);
	return 1;
}
int do_quit(string arg)
{
	write(this_player()->query("name")+"，折腾个啥劲儿呀，专心养蜂吧！\n");
	return 1;
}

