// miantuan.c
// Last Modified by Winder on Jul. 15 2001

inherit ITEM;

string *name = ({"饲料", "饭团", "面团", "肉块", "肉团"});
string *id = ({"si liao", "fan tuan", "mian tuan", "rou kuai", "rou tuan"});
string *unit = ({"把", "个", "个", "块", "个"});
string *value = ({200, 400, 400, 800, 1600});
string *remaining = ({5, 3, 4, 3, 2});
string *supply = ({5, 10, 12, 20, 25});
string *effect = ({1, 2, 2, 4, 8});

void create()
{
	//	int i = random(sizeof(name));
	int i = 2;

	set_name(name[i], ({id[i]}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一" + unit[i] + "喂养宠物的" + name[i] + "。看起来好象脏乎乎的。\n");
		set("unit", unit[i]);
		set("value", value[i]);
		set("siliao_remaining", remaining[i]);
		set("siliao_supply", supply[i]);
		set("siliao_effect", effect[i]);
	}
}
