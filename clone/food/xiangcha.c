// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

//xiangcha.c
inherit ITEM;
inherit F_LIQUID;

void create()
{
  set_name("楠木茶盅", ({"cha zhong", "chazhong", "cha", "teapot", "tea"}));
  set_weight(50);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一只楠木茶盅。\n");
    set("unit", "只");
    set("max_liquid", 2);
  }

  set("liquid", ([
                         "type":"water",
                         "name":"云雾山香茶",
                    "remaining":2,
  ]));
  setup();
}
