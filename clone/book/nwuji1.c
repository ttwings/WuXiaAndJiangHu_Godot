// Last Modified by winder on May. 29 2001
// nwuji1.c

inherit ITEM;

string *titles = ({
	"风云手手法",
	"散花掌法",
	"如来千叶手手法",
	"大金刚拳法",
	"罗汉拳法",
	"般若掌法",
	"韦陀掌法",
});

string *skills = ({
	"fengyun-hand",
	"sanhua-strike",
	"qianye-hand",
	"jingang-cuff",
	"luohan-cuff",
	"boruo-strike",
	"weituo-strike",
});

void create()
{
	int i = random(sizeof(titles));

	set_name(titles[i], ({"shaolin wuji", "wuji"}));
	set_weight(200);
	set("unit", "册");
	set("long", "这是一册" + titles[i] + "\n");
	set("value", 500);
	set("material", "paper");
	set("skill", ([
							 "name":skills[i],
					 "exp_required":10000,
						"jing_cost":15 + random(30),
					   "difficulty":25,
						"max_skill":99]));
}
