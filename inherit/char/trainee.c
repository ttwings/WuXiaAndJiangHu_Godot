// /d/yixing/clbajiaoting.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

int do_yao(string);
int train_it(object, object, int);
varargs void revive();

void init()
{
	add_action("do_gen", "gen");
	add_action("do_gen", "come");
	add_action("do_yao", "yao");
	add_action("do_yao", "attack");
	add_action("do_ting", "ting");
	add_action("do_ting", "stay");
	add_action("do_fang", "fang");
	add_action("do_fang", "release");
	add_action("do_stop","zhi");
	add_action("do_stop","stop");
}

void create()
{
	set_name("野兽", ({"ye shou", "shou"}));
	set("race", "野兽");
	set("age", 100);
	set_weight(150000);
	set("long", "一只面目不清的野兽。\n");
	set("combat_exp", 1000);
	set("wildness", 5);
	set("loyalty", 5);
	set("auto_follow",1);
	
	setup();
}

int is_trainee()
{
	return 1;
}

int train_it(object ob, object me, int pts)
{
	string msg_trained;

	if(!living(me)) return 1;
	if(me->query_lord()) pts = 10 * pts / (me->query("loyalty") + 10);

	if(query_temp("trainer") != ob->name())
	{
		set_temp("trainer", ob->name());
		set_temp("training_pts",pts);
	}
	else add_temp("training_pts",pts);

	if(query_temp("training_pts") > 100)
	{
		delete_temp("trainer");
		delete_temp("training_pts");
		if(me->is_fighting()) me->remove_all_enemy();
		me->set_lord(ob);
		if(!(msg_trained = me->query("msg_trained")))
			msg_trained = "$N驯服了$n";
 		
		message_vision(msg_trained + "。\n", ob, me);

		if(me->query("auto_follow"))
		{
			me->set_leader(ob);
			message_vision("$n朝$N走了过来。\n", ob, me);
		}
	}
	return 1;
}

int do_gen(string arg)
{
	object vc, me, ob = this_player();

	if (!arg ) return notify_fail("你想让谁跟着你走？\n");
	if(!objectp(me = present(arg, environment(ob))))
		return notify_fail("这里没有这个生物。\n");
	if( !me->is_character() || me->is_corpse() )
		return notify_fail("看清楚一点，那并不是活物。\n");
	if(ob==me) return notify_fail("这个好办。\n");
	message_vision("$N向$n招了招手。\n", ob, me);
	if(me->query_lord() == ob)
	{
		me->set_leader(ob);
		message_vision("$n朝$N走了过来。\n", ob, me);
	}
	else
	{
		message_vision("$n对$N睬也不睬。\n", ob, me);
	}
	return 1;
}

int do_stop(string arg)
{
	object vc, me, ob = this_player();

	if (!arg ) return notify_fail("你想让谁停下来？\n");
	if(!objectp(me = present(arg, environment(ob))))
		return notify_fail("这里没有这个生物。\n");
	if( !me->is_character() || me->is_corpse() )
		return notify_fail("看清楚一点，那并不是活物。\n");
	if(ob==me) return notify_fail("用halt命令。\n");

	message_vision("$N拍一拍$n的头。\n", ob, me);
	if(me->query_lord() == ob)
	{
		if (me->is_fighting())
		{
			me->remove_all_enemy();
			message_vision("$N缩在$n的脚边不咬人了。\n",me,ob);
			return 1;
		}
		else
		{
			message_vision("$n疑惑地看着$N。\n", ob, me);
			return 1;
		}
	}
	else
	{
		 message_vision("$n对$N睬也不睬。\n", ob, me);
	}
	return 1;
}

int do_yao(string victim)
{
	object vc, me = this_object(), ob = this_player();
	int atk;

	if(! victim)
	{
		message_vision("咬谁？\n", ob, me);
		return 1;
	}
	if(!(vc = present(victim,environment(me))))
	{
		message_vision("$N拍拍$n的头。\n", ob, me);
		write(me->name()+"找不到这个人。\n");
		return 1;
	}
	if (vc == ob)
	{
		message_vision("$N拍拍$n的头，又指了指自己。\n", ob, me);
		if(me->query_lord()==ob)
		{
			message_vision("$n疑惑地看着$N。\n", ob, me);
			return 1;
		}
		remove_call_out("biting");
		call_out("biting",1,me,vc);
		return 1;
	}
	if (vc == me)
	{
		message_vision("$N拍拍$n的头，指了指它的尾巴。\n", ob, me);
		message_vision("$n咬着自己的尾巴转了一个圈。\n", ob, me);
		return 1;
	}

	message_vision("$N拍拍$n的头，又指了指" + vc->query("name") +
		"。\n", ob, me);
	if(me->query_lord() != ob)
	{
//		atk = 9;
//	else {
//		atk = random(10);
//		message_vision("$n疑惑地看了看$N，", vc, me);
//		message_vision("又看了看$N。\n", ob, me);
		message_vision("$n对$N睬也不睬。\n", ob, me);
		return 1;
//		if(atk > 6)  vc = ob;
	}
//	if( atk > 5 ) {
	else
	{
//		if(me->query_lord() == vc) vc = ob;
		remove_call_out("biting");
		call_out("biting",1,me,vc);
		message_vision("$n向$N扑了过去。\n", vc, me);
	}
	return 1;
}

int do_ting()
{
	object me = this_object(), ob = this_player();

	if(me->query_lord()==ob && !me->query("rider"))
	{
		me->set_leader(0);
		message_vision("$N对$n挥了挥手，$n垂首走开了。\n", ob, me);
		return 1;
	}
	return 0;
}

int do_fang()
{
	object me, ob;
	me = this_object();
	ob = this_player();
	if(me->query_lord()==ob && !me->query("rider"))
	{
		me->set_lord(0);
		me->set_leader(0);
		if (me->query("rider") == ob) me->delete("rider");
		if (ob->query("rided") == me) ob->delete("rided");
		message_vision("$N在$n耳边轻声说了几句，$n垂首走开了。\n", ob, me);
		me->set_temp("prelord",ob->query("id"));
		return 1;
	}
	return 0;
}

void biting(object me, object ob)
{
	if( !ob || environment(ob) != environment() ) return;

	me->kill_ob(ob);
}
