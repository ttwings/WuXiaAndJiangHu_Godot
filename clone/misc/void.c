// void.c (re-created after Elon screwed it up on 07-24-95)

inherit ROOM;
int is_chat_room() {return 1;}
void create()
{
	set("short","最後乐园");
	set("long",@LONG	
这里就是传说中的 VOID -- 大神和巫师的最後乐园. 你看到四周一片
白茫茫的, 不一会从虚无中冒出一只企鹅, 递给你一罐「可口可乐」(tm), 
然後站在一旁很邪恶地笑著. 又过了一会, 一只北极熊走了过来, 一掌拍扁
了那只企鹅并从你手上抢走那瓶可乐, 大笑三声後就从你眼前消失了.
你摇摇头, 这种地方还是不要待太久的好.
LONG
	);

	set("exits", ([
		"down" : "/d/city/zuixianlou",
	]));

	setup();
}

/*
void init()
{
	object me = this_player();
	if (!wizardp(me)) me->move("/d/city/zuixianlou");
	return;
}
*/

void init()
{
	object me;
	me=this_player();
	if (!wizardp(me)) me->save();
	return;
}
