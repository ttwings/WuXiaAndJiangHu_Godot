// daojing.c

inherit ITEM;

void create()
{
	set_name("万寿道藏", ({"wanshou book", "book"}));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一部万寿道藏。徽宗皇帝于政和年间，遍搜普天下道家之书，雕版印行，一共有五千四百八十一卷，委派刻书之人，便是黄裳……。\n");
		set("value", 5000);
		set("material", "paper");
		set("skill", ([
								 "name":"taoism",
						 "exp_required":200000,
							"jing_cost":50,
						   "difficulty":30,
							"min_skill":99,
							"max_skill":149,
		]));
	}
}
