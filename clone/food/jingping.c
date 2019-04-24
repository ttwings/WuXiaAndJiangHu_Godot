// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// jingping.c 净瓶

inherit ITEM;
inherit F_LIQUID;

void create()
{
  set_name("净瓶", ({"jingping", "bottle"}));
  set_weight(1000);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "南海观音盛水的净瓶。\n");
    set("unit", "个");
    set("value", 5000);
    set("max_liquid", 500);
  }

  // because a container can contain different liquid
  // we set it to contain wine at the beginning
  set("liquid", ([
                           "type":"water",
                           "name":"净水",
                      "remaining":400,
                    "drunk_apply":20,
  ]));
}
