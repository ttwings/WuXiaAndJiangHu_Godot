// Room: /d/baihuagu/tree.c 树林
// Last Modified by Winder on Mar. 5 2001
inherit ROOM;
void create()
{
	set("short", "树林");
	set("long", @LONG
丛林中一片黑暗，你瞪大眼睛，觉得到处都是路，又好象到处
都不是路。若是在丛林中迷失了方向，这辈子就别想活着走出去了。
LONG);
	set("outdoors", "baihuagu");
	set("exits", ([ 
		"north": __DIR__"treen",  
		"west" : __DIR__"treew",
		"south": __DIR__"trees",
		"out"  : __DIR__"ent",
		"east" : __DIR__"treee",
	]));
	set("coor/x", -450);
	set("coor/y", -400);
	set("coor/z", 0);
	setup();
}

void init()
{
	add_action("do_go","go");
}
int do_go()
{
	if(random(40)<(this_player()->query("kar")))
	{
		this_player()->move(__DIR__"tree1");
		return 1;
	}
	else
		if(random(5))
		{
			this_player()->move(this_object());
			return 1;
		}
}
