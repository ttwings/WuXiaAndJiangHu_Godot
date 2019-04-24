// /clone/board/wiz2_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("巫师专用公告版(玩家留言将不保留)", ({"board"}));
	set("location", "/d/city/wumiao");
	set("board_id", "wiz2_b");
	set("long", "这是一个专供巫师做通告的留言板，通告一些侠客行公共信息。\n");
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
