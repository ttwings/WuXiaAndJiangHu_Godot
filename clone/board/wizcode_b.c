// /clone/board/wizcode_b.c
inherit BULLETIN_BOARD;
void create()
{
	set_name("程序更新留言簿", ({"board"}));
	set("location", "/d/wizard/meeting_room");
	set("board_id", "wizcode_b");
	set("long", "这是一个专供巫师记录程序更新情况的留言板。\n");
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}