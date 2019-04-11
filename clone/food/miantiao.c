// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

string *names = ({
  "刀削面",
  "阳春面",
  "细面",
  "钢丝面",
  "鸡丝面",
  "牛肉丝面",
  "盖浇面",
  "卤味面",
  "排骨面",
  "豆丝面",
  "羊杂碎面",
  "海鲜面",
  "馄饨面",
  "车仔面",
  "肉煮面",
  "长寿面",
  "老家招牌面",
});

void create()
{
  set_name("各式面条", ({"mian tiao", "miantiao", "mian"}));
  set_weight(100);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一碗热气腾腾的面条。\n");
    set("unit", "碗");
    set("value", 200);
    set("food_remaining", 5);
    set("food_supply", 35);
  }
}

void init()
{
  if (query("name")=="各式面条")
    set_name(names[random(sizeof(names))], ({"mian tiao","miantiao","mian"}));
  ::init();
}
