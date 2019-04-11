// /clone/board/news_b.c

inherit BULLETIN_BOARD;

void create()
{
	seteuid(getuid());
	set_name("更新公告版", ({ "board" }) );
	set("location", "/u/lijia/workroom");
	set("board_id", "news_b");
	set("long", "这是一个巫师提供更新消息时用的留言板。\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}

