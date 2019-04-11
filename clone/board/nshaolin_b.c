// Last Modified by Winder on May. 21 2001
// /clone/board/nshaolin_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("南少林弟子留言板", ({ "board" }) );
	set("location", "/d/nanshaolin/pingtai");
	set("board_id", "nshaolin_b");
	set("long", "这是一个供南少林弟子交流的留言板。\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
