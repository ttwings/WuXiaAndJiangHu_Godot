// /clone/board/meizhuang_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("日月神教梅庄记事板", ({"board"}));
	set("location", "/d/meizhuang/dating");
	set("board_id", "meizhuang_b");
	set("long", "这是一个专供日月神教教众在梅庄使用的留言板。\n");
	setup();
	set("capacity", 300);
	replace_program(BULLETIN_BOARD);
}
