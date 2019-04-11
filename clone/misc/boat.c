// Room: /d/nanyang/duchuan.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;

void create()
{
	set("short", "渡船");
	set("long", @LONG
一叶小舟，最多也就能载七、八个人。一名六十多岁的老艄公手持
长竹篙，正在船尾吃力地撑着船。
LONG );
	set("no_clean_up", 0);
	set("outdoors", "nanyang");
	set("coor/x", 10);
	set("coor/y", 350);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
