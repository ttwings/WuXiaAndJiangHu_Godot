// /clone/board/wudao_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("比武大会成绩版", ({ "board" }) );
	set("location", "/d/city/wudao4");
	set("board_id", "wudao_b");
	set("long", "这是一个专供公布每月比武大会成绩的布告板，其他灌水杀无赦。\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}

