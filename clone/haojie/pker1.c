inherit __DIR__ "shashou";

void create()
{
	::create();
	set("level", 1);
	set_name("青衣杀手", ({"sha shou", "shashou", "qing", "qingyi"}));
	set("long", "他是七杀门的青衣杀手。\n");
	set("qi", 500);
	set("max_qi", 500);
	set("eff_qi", 500);
	set("jing", 500);
	set("max_jing", 500);
	set("eff_jing", 500);
	set("neili", 500);
	set("max_neili", 500);
	set("combat_exp", 10000);
	set("min_kill_exp", 1000);
	set("base_level", 50);
	set("special_level", 50);
	set_skill("force", query("base_level"));
	set_skill("taiji-shengong", query("special_level"));
	set_skill("unarmed", query("base_level"));
	set_skill("taiji-quan", query("special_level"));
	set_skill("dodge", query("base_level"));
	set_skill("tiyunzong", query("special_level"));
	set_skill("sword", query("base_level"));
	set_skill("taiji-jian", query("special_level"));
	set_skill("parry", query("base_level"));
	map_skill("force", "taiji-shengong");
	map_skill("unarmed", "taiji-quan");
	map_skill("dodge", "tiyunzong");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");
	create_family("七杀门", 11 - query("level"), "杀手");
}