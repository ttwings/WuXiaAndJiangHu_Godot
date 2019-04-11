// zhangpu.c 铁掌掌谱
// Last Modified by winder on Nov. 17 2000

inherit ITEM;
void setup()
{}

void init()
{
	add_action("do_du", "du");
	add_action("do_du", "study");
}

void create()
{
	set_name("铁掌掌谱", ({ "tiezhang zhangpu", "zhangpu", "pu" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit","本");
		set("long","铁掌掌谱\n这是一本落满灰尘的破书，纸质发黄，边缘处也已残缺不全了。\n");
		set("value",50000);
		set("material","paper");
		set("no_drop","这样东西不能离开你。\n");
		set("no_get", "这样东西不能离开那儿。\n");
	}
}

int do_du(string arg)
{
	object me = this_player();
	object where = environment(me);
	object ob;
	mapping skill;
	int level; 
	int neili_lost;

	if (!id(arg))
	return 0;

	if (!present(this_object(), this_player()))
		return 0;
	if (where->query("pigging"))
	{
		write("你还是专心拱猪吧！\n");
		return 1;
	}
	if( (int)me->query("jing") < 25 )
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}
	if (me->is_busy())
	{
		write("你现在正忙着呢。\n");
		return 1;
	}
	if( me->is_fighting() )
	{
		write("你无法在战斗中专心下来研读新知！\n");
		return 1;
	}
	if (!id(arg))
	{	
		write("你要读什么？\n");
		return 1;
	}
	if( !me->query_skill("literate", 1) )
	{
		write("你是个文盲，先学点文化(literate)吧。\n");
		return 1;
	}
	switch(random(3))
	{
		case 0:
			message("vision", me->name() + "翻出一本书在读。\n", environment(me), me);
			break;
		case 1:
			message("vision", me->name() + "一边读书，浑身骨骼一边发出咯咯的脆响。\n", environment(me), me);
			break;
		case 2:
			message("vision", me->name() + "的脸色时红时青，阴晴不定。\n", environment(me), me);
			break;
	}
	if( (int)me->query("jing") < 15 )
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}
	if (me->query("family/family_name") != "铁掌帮") {
		me->delete_skill("tiezhang-zhangfa");
		write("你研读了一会，发现上面所说的对你而言太深了。\n");
		return 1;
	}

	if(me->query_skill("tiezhang-zhangfa", 1) > 100) neili_lost = 15;
	else
		if(me->query_skill("tiezhang-zhangfa", 1) > 60) neili_lost = 10;
		else neili_lost = 5;
	if( (int)me->query("neili") < neili_lost)
	{
		write("你内力不够，无法钻研这么高深的武功。\n");
		return 1;
	}
	level = me->query_skill("tiezhang-zhangfa", 1);
	if( (int)me->query("combat_exp") < (int)level*level*level/10 )
	{
		write("你的实战经验不足，再怎么读也没用。\n");
		return 1;
	}
	if( me->query_skill("tiezhang-zhangfa", 1) > 120)
	{
		write( "你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
		return 1;
	}
	me->receive_damage("jing", 15);
	me->set("neili",(int)me->query("neili")-neili_lost);
	if( !me->query_skill("tiezhang-zhangfa", 1) )
	{
		me->set_skill("tiezhang-zhangfa", 0);
	}
	me->improve_skill("tiezhang-zhangfa", (int)me->query_skill("literate", 1)/3+1);
	write("你研读《铁掌掌谱》，颇有心得。\n");
	return 1;
}
