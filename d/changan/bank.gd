# // /d/changan/bank.c

#include  <ansi.h>
# inherit  ROOM;
extends Room

# func reset_balance(object  me);

func create():
	set  ("short",  "相记钱庄");
	set  ("long",  """
这是一家老字号的钱庄，相老板是山西人，这家钱庄从他的爷爷的
爷爷的爷爷的爷爷那辈开始办起，一直传到他手里，声誉非常好，在全
国各地都有分店。它发行的银票通行全国。钱庄的门口，挂有一块牌子
(paizi)。""");
	set("item_desc",  {
		"paizi":  """
这里是钱庄，目前我们提供的服务有：

check		    查帐。
deposit		  存款。
withdraw		取款。
convert		  兑换钱币。
"""
	}  );
	set("no_fight", 1);
	set("exits",  { 
	    "north"  :  __DIR__ + "center",
	});
	set("objects",  {
		__DIR__ + "npc/tiesuanpan"  :  1,
	});
# //		set("outdoors",  "changan");
	set("no_clean_up",  0);
	setup();
# }
# /*
func  _init():
	reset_balance(this_player());
	# ::init();
	create()

func  reset_balance(me):
	var myexp=me.query("combat_exp")/1000;
	var allowed
	var removed_gold;
	var myid=me.query("id");
	var NPCNAME="铁算盘";

	if(myexp<1):
		myexp=1;
	if(myexp>100):
		myexp=100;
	allowed=myexp*1000000;
	# //each  year  can  have  100  gold,  range  100-10000.  
	if  (me.query("balance")  >  allowed):
		me.set("balance_old",  me.query("balance"));
		me.set("balance",  allowed);
		removed_gold  =  (me.query("balance_old")  -  me.query("balance"))/10000;
		log_file("MONEY_RESET",  ctime(  time()  )+"：魏大人收缴了"+me.query("name")+"("+me.query("id")+")"+removed_gold+"两黄金。\n");
		tell_object(me,  GRN+NPCNAME+"在你的耳边悄声说道："+RANK_D.query_respect(me)+
			"，这、这真不知怎么说是好．．．\n"NOR);
		tell_object(me,  GRN+NPCNAME+"在你的耳边悄声说道："+
			"昨日魏大人派人前来察案，发觉你老的黄金来路．．．\n"NOR);
		tell_object(me,  GRN+NPCNAME+"在你的耳边悄声说道："+
			"若不是在下帮你老辩解，你老的钱就全都充公了．．．\n"NOR);
	return;

