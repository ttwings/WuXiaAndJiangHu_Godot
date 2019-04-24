// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

inherit ITEM;
inherit F_FOOD;

string *names = ({
    "脆烤火鸡",
    "香熏火鸡",
    "填枣火鸡",
});

string *parts = ({
    "火鸡肉",
    "火鸡小腿肉",
    "火鸡大腿肉",
    "火鸡翅膀肉",
    "火鸡背板肉",
    "火鸡脯子肉",
    "火鸡颈子肉",
    "火鸡屁股肉",
    "火鸡头",
    "火鸡胗",
    "火鸡肝",
    "火鸡肠",
    "火鸡皱肠",
    "火鸡针线包腰子",
    "火鸡枕头肺",
    "火鸡肋骨",
    "火鸡颈骨",
    "火鸡翅骨",
    "火鸡腿骨",
});

void create()
{
  string name = "火鸡";
  set_name(name, ({"turkey"}));
  set_weight(1000);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一只硕大的感恩节火鸡。\n");
    set("unit", "只");
    set("value", 950);
    set("food_remaining", 30);
    set("food_supply", 10);
  }
  setup();
}

void init()
{
  if (query("name") == "火鸡")
  {
    string name;
    name = names[random(sizeof(names))];
    set_name(name, ({"turkey"}));
  }
  set("no_get", "喂！过节让大家吃火鸡嘛，您瞧您，鬼鬼祟祟贼头贼脑的样子！\n");
  add_action("do_get", "get");
  add_action("do_eat", "eat");
  ::init();
}

int do_eat(string arg)
{
  object me = this_object();
  object who = this_player();
  string part = parts[random(sizeof(parts))];

  me->set("eat_msg", "$N撕下一小块" + part + "，扔到嘴中吃了起来。\n");
  return ::do_eat(arg);
}

int do_get(string arg)
{
  object me = this_object();
  object who = this_player();

  if (!arg)
    return 0;

  if (present(arg, environment(who)) == me)
  {
    tell_object(who,
                "喂！过节让大家吃火鸡嘛，您瞧您，鬼鬼祟祟贼头贼脑的样子！\n");
    return 1;
  }
  return 0;
}
