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
	set("race", "飞禽");
	set("gender",  "雄性");
	set("age",  2);
	set("long",  "一只雄赳赳的斗鸡。\n");
	set("attitude",  "friendly");
	set("max_qi",200+random2(2));
	set("max_jing",200+random2(2));
	set("str",  40+random2(2));
	set("spi",  40+random2(2));
	set("cor",  40+random2(2));
	set("con",  40+random2(2));
	set("cor",  40+random2(2));
	set("cps",  40+random2(2));
	set("dex",  40+random2(2));
	set("owner", "mud os");
	set("no_get",1);
	set_skill("unarmed",  random2(2)+10);
	set_skill("dodge",  random2(2)+10);
	set_skill("parry",  random2(2)+10);
	
	setup();

