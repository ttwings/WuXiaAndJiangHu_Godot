// poison.h
// Last Modified by winder on Feb. 28 2001

void init()
{
	//	add_action("do_tu", "tu");
	add_action("do_make", "make");
	add_action("do_dian", "dian");
}

int do_make(string arg)
{
	object fire, me = this_player();
	object obj = this_object();

	if (!arg || (arg != "huo yan" && arg != "huoyan" && arg != "huodui"))
		return notify_fail("你要做什么？\n");

	if (!objectp(fire = present("fire", me)) && (me->query("neili") < 500))
		return notify_fail("你身上没有火种，怎么升火？\n");
	if (me->query_skill("poison", 1) < 60)
	{
		message_vision("$N打着火折将$n点燃，冒出一缕奇异的毒烟！\n", me, this_object());
		message_vision("$N吓了一大跳，连忙将$n胡乱一扔，远远躲了开去！\n", me, this_object());
		//		this_object()->add_amount(-1);
		destruct(obj);
		return 1;
	}
	if (present("huo yan", environment(me)))
		return notify_fail("这里已经有火焰了，还要升什么火？\n");
	if (!fire)
	{
		me->add("neili", -100);
		message_vision(HIR "\n$N口中吐出一口青烟，将手中$n" HIR "用内力一搓一抛，轰地一声燃起一堆熊熊火焰！\n\n" NOR, me, this_object());
	}
	else
		message_vision(HIR "\n$N将手中$n" HIR "用火种点燃，然后向地下使劲一扔，燃起了一堆熊熊火焰！\n\n" NOR, me, this_object());
	new ("/d/xingxiu/npc/obj/huoyan")->move(environment(me));
	//	this_object()->add_amount(-1);
	destruct(obj);
	return 1;
}
/*
int do_tu(string arg)
{
	string me, what;
	object ob;
	   
	if( !arg || sscanf(arg, "%s on %s", me, what)!=2 || !id(me) )
		return notify_fail("命令格式: tu <药> on <武器>。\n");

	ob = present(what, this_player());

	if( !ob ) return notify_fail("你身上没有" + what + "这样东西。\n");
	if( !ob->query("weapon_prop")) return notify_fail("只能涂在武器上。\n");

	else return notify_fail("你要先将药粉点燃才行。\n");

	return 0;	
}
*/
int do_dian(string arg)
{
	object me, ob, ob1;

	ob = this_object();
	me = this_player();
	if (!arg || arg != ob->query("id"))
		return notify_fail("你要点燃什么东西？\n");

	if (!objectp(ob1 = present("fire", me)))
		return notify_fail("你先要找个火种。\n");

	message_vision("$N打着火折将$n点燃，冒出一缕奇异的毒烟！\n", me, ob);
	if (me->query_skill("poison", 1) > 79)
	{
		new (ob->query("drug2"))->move(me);
		//		ob->add_amount(-1);
		destruct(ob);
		return 1;
	}
	else
	{
		message_vision("$N吓了一大跳，连忙将$n胡乱一扔，远远躲了开去！\n", me, ob);
		//		ob->add_amount(-1);
		destruct(ob);
		return 1;
	}
}

int drink_drug(object ob)
{
	string poison = ob->query("poison");
	this_player()->apply_condition(poison, (int)this_player()->query_condition(poison) + random(8));
	return 0;
}
