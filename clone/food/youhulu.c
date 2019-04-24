// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// hulu.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
  set_name("油葫芦", ({"you hulu", "youhulu", "hulu", "hu"}));
  set_weight(700);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一个装满菜油的葫芦。\n");
    set("unit", "个");
    set("value", 100);
    set("max_liquid", 20);
    set("liquid", ([
                           "type":"oil",
                           "name":"菜油",
                      "remaining":12,
    ]));
  }
}

void init()
{
  add_action("do_drink", "drink");
  ::init();
}

int do_drink(string arg)
{
  object who = this_player();
  object me = this_object();

  if (me == present(arg, who) &&
      me->query("liquid/name") == "菜油")
  {
    message_vision("$N拿起$n往嘴里就灌。\n", who, me);
    call_out("reacting", 1, who, me);
    return 1;
  }
  return ::do_drink(arg);
}

void reacting(object who, object me)
{
  if (who)
    message_vision("$N一阵恶心，差点吐出来。\n", who, me);
}
