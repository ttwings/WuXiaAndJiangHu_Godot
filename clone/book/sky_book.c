// skybook.c

#include <ansi.h>

inherit ITEM;
inherit F_AUTOLOAD;

void create()
{
	set_name(HIY "ÎŞ×ÖÌìÊé" NOR, ({"skybook", "book"}));
	set_weight(10);
	set("no_steal", 1);
	set("no_beg", 1);
	set("no_get", 1);
	set("no_drop", "ÍÛ£¿ÌìÊé¶¼Ïë¶ªµô,Ğ¡ĞÄÔâÌìÇ´¡£\n\n");
	set("long", @LONG ´ËÄËµ±ÄêÏÉÈËÔùÓÚ "µ°Éú"µÄ±¦Îï, ÒòÎªµ°Éú²»Ê¶×Ö, ÏÉÈËÊ©ÁË·¨,
°ÑÌìÊé±ä³ÉÁËÎŞ×ÖÌìÊé, ºÇºÇ !¾ÍÊÇÎÄÃ¤Ò²ÄÜ¶Á¶®, ¿ì¿´¿´(kan)°É£¡ LONG);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "±¾");
		set("material", "unknow");
	}
}

void init()
{
	add_action("kan_book", "kanbook");
	add_action("bigu_eat", "bigu");
	add_action("cloud_goto", "cloud");
}

int query_autoload()
{
	return 1;
}

//½éÉÜ
int kan_book()
{
	object me;
	me = this_player();
	if (!present(this_object(), this_player()))
		return 0;

	tell_object(me,
    "·¨¾÷ö		    ¹¦ÄÜ

±Ù¹È(bigu)        ÈıÌìÈıÒ¹²»³Ô²»ºÈ\n

¿µ¸´(body)        Á¢Âí»Ö¸´¾«ÉñÌåÁ¦\n

½î¶·ÔÆ(cloud)     µ½ÏëÈ¥µÄµØ·½\n");
	return 1;
}

// ±Ù¹È

int bigu_eat()
{
	object ob, me;
	int fw;

	ob = this_object();
	me = this_player();

	if (!present(this_object(), this_player()))
		return 0;

	if (!me->query_condition("f_condi"))
	{
		write(HIY "Äã¿ÚÖĞÄîÄîÓĞ´Ê,ÄÇß×ßäßèÎû...\n" NOR);
		tell_object(me, "ÄãÖ»¾õÉñÇåÆøË¬,¿ÉÒÔ²»³Ô·¹ÁË...\n");

		fw = (int)me->max_food_capacity();
		me->set("food", fw);
		fw = (int)me->max_water_capacity();
		me->set("water", fw);

		write("ÈıÌìÈıÒ¹Ò²²»»á¶öÁË£¡\n\n");
		me->apply_condition("f_condi", 5);
		ob->set("eated", "xixi");
	}
	else
	{

		tell_object(me, "Ou¡£¡£Äã´òÁË¸ö±¥àÃ¡£¡£¡£Ou...Ou...\n");

		fw = (int)me->max_food_capacity();
		me->set("food", fw);
		fw = (int)me->max_water_capacity();
		me->set("water", fw);
	}

	return 1;
}
// ½î¶·ÔÆ

int cloud_goto(string arg)
{
	string home;
	object mme;
	int goto_inventory = 0;
	object obj;
	string msg;
	mme = this_player();
	if (!present(this_object(), this_player()))
		return 0;

	if (!arg)
		return notify_fail("ÄãÒªÈ¥ÄÄÀï£¿\n");

	if (sscanf(arg, "-i %s", arg))
		goto_inventory = 1;

	if (!arg)
		return notify_fail("ÄãÒªÈ¥ÄÄÀï£¿\n");

	obj = find_player(arg);
	if (!obj)
		obj = find_living(arg);
	if (!obj || !mme->visible(obj))
	{
		arg = resolve_path(mme->query("cwd"), arg);
		if (!sscanf(arg, "%*s.c"))
			arg += ".c";
		if (!(obj = find_object(arg)))
		{
			if (file_size(arg) >= 0)
				return mme->move(arg);
			return notify_fail("Ã»ÓĞÕâ¸öÍæ¼Ò¡¢ÉúÎï¡¢»òµØ·½¡£\n");
		}
	}

	if (!goto_inventory && environment(obj))
		obj = environment(obj);

	if (!obj)
		return notify_fail("Õâ¸öÎï¼şÃ»ÓĞ»·¾³¿ÉÒÔ goto¡£\n");
	tell_object(mme,HIM"ÄãÒ»¸ö½î¶·´ÜÏò¿ÕÖĞ,Ö»¼ûÑÛÇ°ºìÔÆ·É¹ı,¶ú±ß·çºôºô×÷Ïì .
.\n\n"NOR);
	tell_object(mme,"ÍÛà¸,ºÃÍ´¿ì,ºÃË¬,Ë¬ÍáÍá!\n\n");
	mme->move(obj);

	tell_object(mme,"Äã¼İ×ÅÔÆ»º»ºÏÂ½µ,°Èß´Ò»Éù,ºÙ!°²È«×ÅÂ½...\n");
	return 1;
}
// »Ö¸´
int body_recover()
{
	object mme;
	mme = this_player();
	mme->set("jing", mme->query("max_jing"));
	mme->set("eff_jing", mme->query("max_jing"));
	mme->set("qi", mme->query("max_qi"));
	mme->set("eff_qi", mme->query("max_qi"));
	mme->set("neili", mme->query("max_neili"));
	tell_object(mme, "ÍÛà¸,Ì«ºÃÁË,Äã¾õµÃÈ«Éí¶¼ÊÇÁ¦Á¿!\n");
	return 1;
}
void owner_is_killed()
{

	write(HIY "Ö»¼ûÑÛÇ°½ğ¹âÒ»ÉÁ...ºÃÏóÊÇ.....\n" NOR);
	destruct(this_object());
}
