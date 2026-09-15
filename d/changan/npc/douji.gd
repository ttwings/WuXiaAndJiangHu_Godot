# /*  <SecCrypt CPL V3R05>  */
 
# //  by  snowcat  on  7/5/1997  
# inherit  NPC;
extends Npc
func random2(int:i):
	return randi()%i
# {
# 	return  (random(i)+uptime())  %  i;
# }
func is_douji():
	return 1

func create():
	set_name("斗鸡",  ({  "dou  ji",  "ji"  })  );
	set_attr("race", "飞禽");
	set_attr("gender",  "雄性");
	set_attr("age",  2);
	set_attr("long",  "一只雄赳赳的斗鸡。\n");
	set_attr("attitude",  "friendly");
	set_attr("max_qi",200+random2(2));
	set_attr("max_jing",200+random2(2));
	set_attr("str",  40+random2(2));
	set_attr("spi",  40+random2(2));
	set_attr("cor",  40+random2(2));
	set_attr("con",  40+random2(2));
	set_attr("cor",  40+random2(2));
	set_attr("cps",  40+random2(2));
	set_attr("dex",  40+random2(2));
	set_attr("owner", "mud os");
	set_attr("no_get",1);
	set_skill("unarmed",  random2(2)+10);
	set_skill("dodge",  random2(2)+10);
	set_skill("parry",  random2(2)+10);
	
	setup();

