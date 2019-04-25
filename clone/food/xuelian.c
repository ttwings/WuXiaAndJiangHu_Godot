// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// xuelian.c 雪莲
#include <ansi.h>
inherit ITEM;

void init();
void eat();

void create()
{
   set_name(HIW "雪莲" NOR, ({"xue lian", "xuelian", "lian"}));
   set_weight(20);
   if (clonep())
      set_default_object(__FILE__);
   else
   {
      set("long", "一朵雪莲花，只生长于绝峰极寒之处。\n");
      set("unit", "朵");
      set("value", 300);
   }

   setup();
}

void init()
{
   add_action("do_chi", "eat");
}

int do_chi(string arg)
{
   if (!this_object()->id(arg))
      return 0;
   if (this_player()->is_busy())
      return notify_fail("你上一个动作还没有完成。\n");

   if (!arg)
      return notify_fail("你要吃什么？\n");

   if ((int)this_player()->query("max_atman") > 0)
   {
      message_vision(RED "$N吃下一朵雪莲花，忽觉一阵反胃，又尽数吐了出来。\n" NOR, this_player());
   }
   else
   {
      if (this_player()->query("gender") == "男性")
         message_vision(GRN "$N吃下一朵雪莲花，看起来精神多了。\n" NOR, this_player());
      else
         message_vision(GRN " $N吃下一朵雪莲花，脸显酡红，倍增娇艳。\n" NOR, this_player());
   }
   destruct(this_object());
   return 1;
}
