inherit __DIR__ "shashou";

void create()
{
	::create();
	set("level", 3);
	set_name("黑衣杀手", ({"sha shou", "shashou", "hei", "heiyi"}));
	set("long", "他是七杀门的黑衣杀手。\n");
	set("qi", 1500);
	set("max_qi", 1500);
	set("eff_qi", 1500);
	set("jing", 1500);
	set("max_jing", 1500);
	set("eff_jing", 1500);
	set("neili", 2000);
	set("max_neili", 2000);
	set("combat_exp", 300000);
	set("min_kill_exp", 100000);
	set("base_level", 100);
	set("special_level", 120);
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