// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// created 3/31/1997 by snowcat
#include <weapon.h>

inherit STICK;
inherit F_LIQUID;

void create()
{
  set_name("细雕青竹筒", ({"bamboo", "long bamboo"}));
  set_weight(600);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "这是一根尺把长的三节蟠虬雕花青竹筒。\n");
    set("unit", "根");
    set("value", 120);
    set("max_liquid", 100);
    set("wield_msg", "$N抽出细雕青竹筒，顺手晃荡了一下里面的水。\n");
    set("unwield_msg", "$N将细雕青竹筒插回腰间。\n");
  }

  set("liquid", ([
                         "type":"water",
                         "name":"清泉碧竹茶",
                    "remaining":90,
  ]));
  init_stick(2);
  setup();
}
