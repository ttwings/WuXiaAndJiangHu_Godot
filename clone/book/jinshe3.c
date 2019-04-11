// jinshe3.c 
inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h> 
void setup()
{}
void init()
{
	add_action("do_du", "du");
	add_action("do_du", "study");
}
void create()
{
	set_name(YEL"「金蛇秘芨」"NOR"下册", ({ "jinshe book3","book3", }));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("material", "paper");
		set("no_drop", "这样东西不能离开你。\n");
		set("no_get", "这样东西不能离开那儿。\n");
		set("no_put", "这样东西不能放在那儿。\n");
		set("long",
	"这是一本用薄纸写成的书。上书：「金蛇秘芨」。\n"
	"书皮泛黄，看来已经保存很久了。\n", );
	}
}

int do_du(string arg)
{
	object me = this_player();
	object where = environment(me);
	object ob;
	mapping skill;
	int pxlevel; 
	int neili_lost;

	if (!(arg=="jinshe book3" || arg == "book3"))
	return 0;
	if (!present(this_object(), this_player()))
		return 0;
	if (where->query("pigging")){
		write("你还是专心拱猪吧！\n");
		return 1;
	}
	if (me->is_busy()) {
		write("你现在正忙着呢。\n");
		return 1;
	}
	if( me->is_fighting() ) {
		write("你无法在战斗中专心下来研读新知！\n");
		return 1;
	}
	if (!id(arg)) {	
		write("你要读什么？\n");
		return 1;
	}
	if( !me->query_skill("literate", 1) ){
		write("你是个文盲，先学点文化(literate)吧。\n");
		return 1;
	}
	message("vision", me->name() + "正专心地研读金蛇密芨。\n", environment(me), me);
	if( (int)me->query("jing") < 25 ) {
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}
	neili_lost = 5;
	if( (int)me->query("neili") < neili_lost) {
		write("你内力不够，无法钻研这么高深的武功。\n");
		return 1;
	}
	pxlevel = me->query_skill("jinshe-zhang", 1);
	if( (int)me->query("combat_exp") < (int)pxlevel*pxlevel*pxlevel/10 ) {
		write("你的实战经验不足，再怎么读也没用。\n");
		return 1;
	}
	if( me->query_skill("jinshe-zhang", 1) > 199){
		write("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
		return 1;
	}
	me->receive_damage("jing", 15);
	me->set("neili",(int)me->query("neili")-neili_lost);
	me->improve_skill("jinshe-zhang", (int)me->query_skill("literate", 1)/3+1);
	write("你研读金蛇密芨，颇有心得。\n");
	return 1;
}

