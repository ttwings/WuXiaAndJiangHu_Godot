// Last Modified by winder on May. 29 2001
// wuji13.c

inherit ITEM;

string *titles = ({
	"韦陀棍法",
	"普渡杖法",
	"伏魔剑法",
	"弹腿腿法",
	"如影随形腿腿法",
});

string *skills = ({
	"weituo-club",
	"pudu-staff",
	"fumo-sword",
	"shaolin-leg",
	"ruying-leg",
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
