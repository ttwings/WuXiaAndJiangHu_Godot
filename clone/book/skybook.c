// skybook.c

#include <ansi.h>
inherit ITEM;
inherit F_AUTOLOAD;
void create()
{
	set_name(HIB"ÎŞ×ÖÌìÊé"NOR, ({"skybook","book"}) );
	set_weight(10);
	set("no_steal", 1);
	set("no_beg", 1);
//	set("no_get", 1);
	set("no_drop","ÍÛ£¿ÌìÊé¶¼Ïë¶ªµô,Ğ¡ĞÄÔâÌìÇ´¡£\n\n");
	set("long",@LONG
´ËÄËµ±ÄêÏÉÈËÔùÓÚ"µ°Éú"µÄ±¦Îï,ÒòÎªµ°Éú²»Ê¶×Ö,ÏÉÈËÊ©ÁË·¨,
°ÑÌìÊé±ä³ÉÁËÎŞ×ÖÌìÊé,ºÇºÇ!¾ÍÊÇÎÄÃ¤Ò²ÄÜ¶Á¶®,¿ì¿´¿´(kan)°É£¡
LONG );
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("unit", "±¾");
		set("material", "unknow");
	}
}

void init()
{
	add_action( "kan_book", "kanbook" );
	add_action( "cloud_goto", "cloud");
}

int query_autoload()
{
	return 1;
}
//½éÉÜ
int kan_book()
{
	object me;
	me=this_player();
	if (!present(this_object(), this_player())) return 0;

	tell_object(me,
    "·¨¾÷ö		    ¹¦ÄÜ
½î¶·ÔÆ(cloud)	 µ½ÏëÈ¥µÄµØ·½\n");
	return 1;
}
// ½î¶·ÔÆ

int cloud_goto(string arg)
{
	object obj,mme=this_player();
	object* ob;
	int i;
	ob = users();

	if (!present(this_object(), this_player()))
		return 0;

	for ( i=sizeof(ob); i>0; i-- )
	{
		if ((ob[i-1]->query("id")==arg) && ( !wizardp(ob[i-1])))
		{
			obj = environment(ob[i-1]);
			this_player()->move(obj);
			tell_object(mme,HIM"ÄãÒ»¸ö½î¶·´ÜÏò¿ÕÖĞ,Ö»¼ûÑÛÇ°ºìÔÆ·É¹ı,¶ú±ß·çºôºô×÷Ïì ..\n\n"NOR);
			tell_object(mme,"ÍÛà¸,ºÃÍ´¿ì,ºÃË¬,Ë¬ÍáÍá!\n\n");
			mme->move(obj);
			tell_object(mme,"Äã¼İ×ÅÔÆ»º»ºÏÂ½µ,°Èß´Ò»Éù,ºÙ!°²È«×ÅÂ½...\n");
			return 1;
		}
	}
	return 0;
}

void owner_is_killed()
{
	write(HIY"Ö»¼ûÑÛÇ°½ğ¹âÒ»ÉÁ...ºÃÏóÊÇ.....\n"NOR);
	destruct(this_object());
}
