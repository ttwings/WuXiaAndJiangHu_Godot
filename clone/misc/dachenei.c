// Last Modified by Winder on May. 21 2001
// /clone/misc/dachenei/.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "大车内");
	set("long", @LONG
					车里干干净净，放了两张舒服的大椅子。窗帘半拉了下来，阳光从
						缝隙中透进来，窗外看不尽的景致，有的壮观，有的也无趣。于是昏昏
							沉沉地睡去，也不管路上走了多久。门外挂了一串风铃，叮呤呤响着。 车夫坐在前面，一路赶着马，一路得意地哼着什么小调。 LONG);
	set("no_clean_up", 0);
	set("no_fight", 1);
	set("no_beg", 1);
	set("no_get", 1);
	setup();
	replace_program(ROOM);
}
