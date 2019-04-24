// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

#include <weapon.h>

inherit HAMMER;
inherit F_LIQUID;

void create()
{
  set_name("大茶壶", ({"teapot"}));
  set_weight(2000);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一个大茶壶。\n");
    set("unit", "个");
    set("value", 50);
    set("max_liquid", 7);
    set("wield_msg", "$N抓起一个$n，握在手中当武器。\n");
    set("material", "bone");
  }

  set("liquid", ([
                         "type":"water",
                         "name":"西湖龙井茶",
                    "remaining":8,
  ]));
  init_hammer(1);
  setup();
}
