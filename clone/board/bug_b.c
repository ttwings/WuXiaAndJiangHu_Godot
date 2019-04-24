// /clone/board/bug_b.c
inherit BULLETIN_BOARD;
void create()
{
	set_name("bug处理版", ({"board"}));
	set("location", "/d/wizard/bug_room");
	set("board_id", "bug_b");
	set("long", "这是一个专供巫师处理玩家举报bug的留言板。\n");
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}