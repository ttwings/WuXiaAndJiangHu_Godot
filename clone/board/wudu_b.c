// /clone/board/wudu_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("五毒教弟子留言板", ({"board"}));
	set("location", "/d/wudujiao/dating");
	set("board_id", "wudu_b");
	set("long", "这是一个供五毒教弟子交流的留言板。\n");
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
