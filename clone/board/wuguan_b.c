// /clone/board/wuguan_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("扬州武馆留言板", ({"board"}));
	set("location", "/d/wuguan/wg_dating");
	set("board_id", "wuguan_b");
	set("long", "这是一个供武馆弟子交流的留言板。\n");
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
