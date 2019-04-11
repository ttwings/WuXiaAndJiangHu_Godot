// /clone/board/murong_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("慕容世家弟子留言板", ({ "board" }) );
	set("location", "/d/yanziwu/lanyue");
	set("board_id", "murong_b");
	set("long", "这是一个供慕容世家门下交流的留言板。\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}

