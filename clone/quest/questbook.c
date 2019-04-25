// quest_book.c 任务书籍

inherit ITEM;

void dest_me()
{
	object env;
	env = environment(this_object());
	if (objectp(env) && !env->is_character())
		destruct(this_object());
}
void dest_me1()
{
	destruct(this_object());
}

void create()
{
	set_name("本门秘籍", ({"family book", "book"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本线装书，颜色有点老旧。\n");
		set("value", 0);
		set("material", "paper");
	}
	//	call_out("dest_me",500);//500是任务时间
	call_out("dest_me1", 1500); //1500是允许accept时间
}
