// /clone/board/yideng_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("一灯大师门下弟子留言板", ({"board"}));
	set("location", "/d/heizhao/chanyuan");
	set("board_id", "yideng_b");
	set("long", "这是一个供一灯大师门下弟子交流的留言板。\n");
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
