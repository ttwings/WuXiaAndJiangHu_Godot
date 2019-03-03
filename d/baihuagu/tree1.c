// Room: /d/baihuagu/tree1.c
// Last Modified by Winder on Mar. 5 2001
inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", "树林");
	set("long", @LONG
丛林中一片黑暗。你瞪大眼睛，勉强看清楚了一点。一条细细
的光线(light)透过层叠的树叶的缝中射下来，似乎预示着生的希望。
LONG);
	set("outdoors", "baihuagu");
	set("exits", ([ 
		"north": __DIR__"tree",  
		"west" : __DIR__"tree",
		"south": __DIR__"tree",
		"east" : __DIR__"tree",
	]));
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -400);
	set("coor/z", 0);
	setup();
}

void init()
{
	add_action("do_go","go");
	add_action("do_look","look");
}
int do_look(string arg)
{
	string *dirc = ({ "无","东","南","西","北"});
	int i;
	i=random(4)+1;
	if (!arg||!(arg=="light" || arg=="光线"))
		return notify_fail("你要看什麽？\n");
	message_vision(HIW "$N仔细观察光线,发现它是从"+dirc[i]+"边透过来的。\n" NOR,this_player());
	this_object()->set_temp("marks/百花谷",i);
	return 1;
}
int do_go(string arg)
{
	string *dira=({"+-*/","east","south","west","north"});
	string *dirb=({"+-*/","e","s","w","n"});
	int a;
	a=(int)this_object()->query_temp("marks/百花谷");
	this_object()->set_temp("marks/百花谷",0);
	if (arg==dira[a]||arg==dirb[a])
	{
		this_player()->move(__DIR__"out");
	}
	else
		if(random(4)) this_player()->move(__DIR__"tree");
		else this_player()->move(__DIR__"bhgent");
	return 1;
}
