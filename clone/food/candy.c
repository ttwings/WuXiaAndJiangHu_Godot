// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

string *names = ({
  "糖果",
  "水果糖",
  "花生糖",
  "瓜子糖",
  "核仁糖",
  "松子糖",
  "桃仁糖",
  "酸梅糖",
  "杏仁糖",
  "奶糖",
  "软糖",
  "薄荷糖",
  "胶糖",
  "口香糖",
  "泡泡糖",
  "蕉糖",
  "桔香糖",
  "小馅饼",
  "小酥糕",
  "小蛋饼",
  "酸梅",
  "话梅",
  "杏话梅",
  "桃话梅",
  "李话梅",
  "果仁巧克力",
  "酒心巧克力",
  "黑仁巧克力",
  "香草巧克力",
  "南瓜巧克力",
 });

void create()
{
  string name = names[random(sizeof(names))];
  set_name(name, ({"candy", "tang guo", "tang", "guo"}));
  set_weight(400);
  set("long","一小把"+name+"。\n");
  set("unit", "小把");
  set("value", 20);
  set("food_remaining", 2);
  set("food_supply", 2);
}
