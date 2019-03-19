/*  <SecCrypt CPL V3R05>  */
 
//  by  snowcat  on  7/5/1997  
inherit  NPC;

int  random2  (int  i)
{
	return  (random(i)+uptime())  %  i;
}
int is_douji() {return 1;}
void  create()
{
	set_name("¶·¼¦",  ({  "dou  ji",  "ji"  })  );
	set("race", "·ÉÇİ");
	set("gender",  "ĞÛĞÔ");
	set("age",  2);
	set("long",  "Ò»Ö»ĞÛôñôñµÄ¶·¼¦¡£\n");
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
}

