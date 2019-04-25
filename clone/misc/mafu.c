// mafu.c 马夫

inherit NPC;
#include <ansi.h>
int do_ride(string arg);

mapping *road = ({
	(["title":"扬州城 ←→ 北京城",
		"from_name":"扬州城",
		  "to_name":"北京城",
		  "from_id":"yz",
			"to_id":"bj",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/beijing/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/shilijie5", "/d/city/shilijie4", "/d/city/shilijie3", "/d/city/shilijie2", "/d/city/shilijie1", "/d/city/beimendajie", "/d/city/beimen", "/d/nanyang/yidao1", "/d/nanyang/yidao2", "/d/nanyang/hanshui1", "/d/nanyang/hanshui2", "/d/nanyang/nanmen", "/d/nanyang/dajie1", "/d/nanyang/nanyang", "/d/nanyang/dajie2", "/d/nanyang/beimen", "/d/nanyang/yidao3", "/d/nanyang/ruzhou", "/d/beijing/road10", "/d/beijing/road9", "/d/beijing/road8", "/d/beijing/road4", "/d/beijing/road7", "/d/beijing/road6", "/d/beijing/road5", "/d/beijing/yongding", "/d/beijing/nandaj2", "/d/beijing/nandaj1", "/d/beijing/kedian"}),
			 "time":10]),
	(["title":"扬州城 ←→ 长安城",
		"from_name":"扬州城",
		  "to_name":"长安城",
		  "from_id":"yz",
			"to_id":"ca",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/changan/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/ganquanjie", "/d/city/shilijie4", "/d/city/tongsiqiao", "/d/city/caohexiaojie", "/d/city/tongsijie", "/d/city/ximen", "/d/luoyang/road1", "/d/luoyang/road8", "/d/luoyang/road9", "/d/luoyang/road10", "/d/luoyang/road11", "/d/luoyang/road0", "/d/luoyang/hulaoguan", "/d/luoyang/road2", "/d/luoyang/eastgate", "/d/luoyang/eastroad", "/d/luoyang/center", "/d/luoyang/westroad", "/d/luoyang/westgate", "/d/changan/road1", "/d/changan/hanguguan", "/d/changan/road2", "/d/changan/zhongnan", "/d/changan/road3", "/d/changan/road4", "/d/changan/baqiao", "/d/changan/eastgate", "/d/changan/eastroad1", "/d/changan/eastroad2", "/d/changan/center", "/d/changan/westroad2", "/d/changan/westroad1", "/d/changan/kedian"}),
			 "time":10]),
	(["title":"扬州城 ←→ 成都城",
		"from_name":"扬州城",
		  "to_name":"成都城",
		  "from_id":"yz",
			"to_id":"cd",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/chengdu/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/shilijie5", "/d/city/shilijie6", "/d/city/shilijie7", "/d/city/nanmendajie", "/d/city/nanmen", "/d/city/dujiangqiao", "/d/wudang/wdroad1", "/d/wudang/wdroad2", "/d/wudang/wdroad3", "/d/wudang/wdroad4", "/d/wudang/wdroad5", "/d/wudang/wdroad6", "/d/wudang/wdroad7", "/d/wudang/wdroad8", "/d/wudang/sanbuguan", "/d/emei/wdroad", "/d/emei/xiaolu1", "/d/emei/xiaolu2", "/d/emei/qsjie1", "/d/chengdu/road1", "/d/chengdu/road2", "/d/chengdu/fuheqiaoe", "/d/chengdu/eastgate", "/d/chengdu/dongjie3", "/d/chengdu/dongjie2", "/d/chengdu/dongjie1", "/d/chengdu/kedian"}),
			 "time":10]),
	(["title":"成都城 ←→ 大理城",
		"from_name":"成都城",
		  "to_name":"大理城",
		  "from_id":"cd",
			"to_id":"dl",
		"from_file":"/d/chengdu/majiu",
		  "to_file":"/d/dali/majiu",
			"value":200,
			 "room":({"/d/chengdu/kedian", "/d/chengdu/dongjie1", "/d/chengdu/dongjie2", "/d/chengdu/dongjie3", "/d/chengdu/eastgate", "/d/chengdu/fuheqiaoe", "/d/chengdu/road2", "/d/chengdu/road1", "/d/emei/qsjie1", "/d/emei/qsjie2", "/d/dali/road1", "/d/dali/road2", "/d/dali/road3", "/d/dali/dehuabei", "/d/dali/taihecheng", "/d/dali/dalinorth", "/d/dali/northgate", "/d/dali/paifang", "/d/dali/taihejiekou", "/d/dali/center", "/d/dali/shizilukou", "/d/dali/dahejiewest", "/d/dali/bingying"}),
			 "time":10]),
	(["title":"扬州城 ←→ 峨嵋山",
		"from_name":"扬州城",
		  "to_name":"峨嵋山",
		  "from_id":"yz",
			"to_id":"em",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/emei/majiu1",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/shilijie5", "/d/city/shilijie6", "/d/city/shilijie7", "/d/city/nanmendajie", "/d/city/nanmen", "/d/city/dujiangqiao", "/d/wudang/wdroad1", "/d/wudang/wdroad2", "/d/wudang/wdroad3", "/d/wudang/wdroad4", "/d/wudang/wdroad5", "/d/wudang/wdroad6", "/d/wudang/wdroad7", "/d/wudang/wdroad8", "/d/wudang/sanbuguan", "/d/emei/wdroad", "/d/emei/xiaolu1", "/d/emei/xiaolu2", "/d/emei/qsjie1", "/d/emei/qsjie2", "/d/emei/caopeng"}),
			 "time":10]),
	(["title":"扬州城 ←→ 佛山城",
		"from_name":"扬州城",
		  "to_name":"佛山城",
		  "from_id":"yz",
			"to_id":"fs",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/foshan/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/shilijie5", "/d/city/shilijie6", "/d/city/shilijie7", "/d/city/nanmendajie", "/d/city/nanmen", "/d/city/dujiangqiao", "/d/wudang/wdroad1", "/d/wudang/wdroad2", "/d/wudang/wdroad3", "/d/wudang/wdroad4", "/d/henshan/hsroad1", "/d/henshan/hsroad2", "/d/henshan/hsroad3", "/d/henshan/hengyang", "/d/henshan/hengyang1", "/d/henshan/hsroad4", "/d/henshan/hsroad5", "/d/henshan/hsroad9", "/d/foshan/nanling", "/d/foshan/northgate", "/d/foshan/street3", "/d/foshan/street4", "/d/foshan/yingxionglou"}),
			 "time":10]),
	(["title":"扬州城 ←→ 福州城",
		"from_name":"扬州城",
		  "to_name":"福州城",
		  "from_id":"yz",
			"to_id":"fz",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/fuzhou/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/ganquanjie", "/d/city/ninghaiqiao", "/d/city/matou", "/d/city/dashixijie", "/d/city/dashidongjie", "/d/city/dongmen", "/d/taishan/yidao", "/d/taishan/yidao1", "/d/jiaxing/jnroad1", "/d/jiaxing/jnroad2", "/d/jiaxing/jnroad3", "/d/jiaxing/jnroad4", "/d/yanping/xianxialing", "/d/yanping/erbapu", "/d/yanping/shandao1", "/d/yanping/yidao1", "/d/yanping/yidao2", "/d/yanping/gubao", "/d/yanping/banyanting", "/d/yanping/3800kan", "/d/yanping/yidao3", "/d/yanping/fengguanyan", "/d/yanping/dongmen", "/d/yanping/fuqiao1", "/d/yanping/mazhan", "/d/yanping/guandao3", "/d/yanping/milin", "/d/yanping/guandao2", "/d/yanping/guandao1", "/d/fuzhou/ximen", "/d/fuzhou/xixiaojie", "/d/fuzhou/xidajie", "/d/fuzhou/dongjiekou", "/d/fuzhou/dongdajie", "/d/fuzhou/rongcheng"}),
			 "time":10]),
	(["title":"扬州城 ←→ 延平城",
		"from_name":"扬州城",
		  "to_name":"延平城",
		  "from_id":"yz",
			"to_id":"yp",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/yanping/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/ganquanjie", "/d/city/ninghaiqiao", "/d/city/matou", "/d/city/dashixijie", "/d/city/dashidongjie", "/d/city/dongmen", "/d/taishan/yidao", "/d/taishan/yidao1", "/d/jiaxing/jnroad1", "/d/jiaxing/jnroad2", "/d/jiaxing/jnroad3", "/d/jiaxing/jnroad4", "/d/yanping/xianxialing", "/d/yanping/erbapu", "/d/yanping/shandao1", "/d/yanping/yidao1", "/d/yanping/yidao2", "/d/yanping/gubao", "/d/yanping/banyanting", "/d/yanping/3800kan", "/d/yanping/yidao3", "/d/yanping/fengguanyan", "/d/yanping/dongmen", "/d/yanping/fuqiao1", "/d/yanping/mazhan"}),
			 "time":10]),
	(["title":"扬州城 ←→ 杭州城",
		"from_name":"扬州城",
		  "to_name":"杭州城",
		  "from_id":"yz",
			"to_id":"hz",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/hangzhou/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/ganquanjie", "/d/city/ninghaiqiao", "/d/city/matou", "/d/city/dashixijie", "/d/city/dashidongjie", "/d/city/dongmen", "/d/taishan/yidao", "/d/taishan/yidao1", "/d/jiaxing/jnroad1", "/d/jiaxing/jnroad2", "/d/jiaxing/jiaxing", "/d/jiaxing/jxnanmen", "/d/hangzhou/road1", "/d/hangzhou/road2", "/d/hangzhou/road3", "/d/hangzhou/hongchunqiao", "/d/hangzhou/road4", "/d/hangzhou/road5", "/d/hangzhou/road6", "/d/hangzhou/road7", "/d/hangzhou/road8", "/d/hangzhou/road9", "/d/hangzhou/road10", "/d/hangzhou/road11", "/d/hangzhou/road12", "/d/hangzhou/road13", "/d/hangzhou/kedian"}),
			 "time":10]),
	(["title":"扬州城 ←→ 苏州城",
		"from_name":"扬州城",
		  "to_name":"苏州城",
		  "from_id":"yz",
			"to_id":"sz",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/suzhou/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/ganquanjie", "/d/city/ninghaiqiao", "/d/city/matou", "/d/city/dashixijie", "/d/city/dashidongjie", "/d/city/dongmen", "/d/taishan/yidao", "/d/taishan/yidao1", "/d/jiaxing/jnroad1", "/d/jiaxing/jnroad2", "/d/suzhou/dongmen", "/d/suzhou/dongdajie2", "/d/suzhou/dongdajie1", "/d/suzhou/canlangting", "/d/suzhou/beidajie1"}),
			 "time":10]),
	(["title":"扬州城 ←→ 武昌城",
		"from_name":"扬州城",
		  "to_name":"武昌城",
		  "from_id":"yz",
			"to_id":"wc",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/jiangling/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/shilijie5", "/d/city/shilijie6", "/d/city/shilijie7", "/d/city/nanmendajie", "/d/city/nanmen", "/d/city/dujiangqiao", "/d/wudang/wdroad1", "/d/wudang/wdroad2", "/d/wudang/wdroad3", "/d/wudang/wdroad4", "/d/henshan/hsroad1", "/d/henshan/hsroad2", "/d/henshan/hsroad3", "/d/henshan/hengyang", "/d/henshan/hengyang1", "/d/henshan/hsroad4", "/d/henshan/hsroad5", "/d/henshan/hsroad6", "/d/henshan/hsroad7", "/d/henshan/hsroad8", "/d/jiangling/tulu2", "/d/jiangling/tulu1", "/d/jiangling/hzjie5", "/d/jiangling/hzjie4", "/d/jiangling/kedian"}),
			 "time":10]),
	(["title":"扬州城 ←→ 无锡城",
		"from_name":"扬州城",
		  "to_name":"无锡城",
		  "from_id":"yz",
			"to_id":"wx",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/wuxi/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/shilijie5", "/d/city/shilijie6", "/d/city/shilijie7", "/d/city/nanmendajie", "/d/city/nanmen", "/d/city/dujiangqiao", "/d/wudang/wdroad1", "/d/wudang/wdroad2", "/d/yixing/yixing", "/d/yixing/tiandi", "/d/yixing/shulin5", "/d/yixing/shulin2", "/d/yixing/shulin3", "/d/yixing/shulin4", "/d/yixing/shanlu1", "/d/yixing/shanlu2", "/d/wuxi/road17", "/d/wuxi/road16", "/d/wuxi/road14", "/d/wuxi/kuaxiqiao", "/d/wuxi/westgate", "/d/wuxi/westroad2", "/d/wuxi/kedian"}),
			 "time":10]),
	(["title":"扬州城 ←→ 襄阳城",
		"from_name":"扬州城",
		  "to_name":"襄阳城",
		  "from_id":"yz",
			"to_id":"xy",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/xiangyang/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/ganquanjie", "/d/city/shilijie4", "/d/city/tongsiqiao", "/d/city/caohexiaojie", "/d/city/tongsijie", "/d/city/ximen", "/d/luoyang/road1", "/d/luoyang/road8", "/d/luoyang/road9", "/d/luoyang/road10", "/d/luoyang/road11", "/d/luoyang/road0", "/d/luoyang/hulaoguan", "/d/luoyang/road2", "/d/luoyang/eastgate", "/d/luoyang/eastroad", "/d/luoyang/center", "/d/luoyang/southroad", "/d/luoyang/southgate", "/d/luoyang/tianjinqiao", "/d/luoyang/road4", "/d/luoyang/longmen1", "/d/luoyang/road3", "/d/xiangyang/caodi3", "/d/xiangyang/northgate2", "/d/xiangyang/northgate1", "/d/xiangyang/northjie", "/d/xiangyang/dingzi", "/d/xiangyang/northroad2"}),
			 "time":10]),
	(["title":"扬州城 ←→ 永登城",
		"from_name":"扬州城",
		  "to_name":"永登城",
		  "from_id":"yz",
			"to_id":"yd",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/yongdeng/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/shilijie5", "/d/city/shilijie4", "/d/city/shilijie3", "/d/city/shilijie2", "/d/city/shilijie1", "/d/city/beimendajie", "/d/city/beimen", "/d/huanghe/caodi1", "/d/huanghe/caodi2", "/d/huanghe/shulin1", "/d/huanghe/shulin3", "/d/huanghe/tiandi1", "/d/huanghe/tiandi3", "/d/huanghe/tiandi4", "/d/huanghe/huanghe1", "/d/huanghe/weifen", "/d/huanghe/huanghe_1", "/d/huanghe/hetao", "/d/huanghe/huangtu", "/d/huanghe/huanghe_2", "/d/huanghe/huanghe_3", "/d/yongdeng/yongdeng", "/d/yongdeng/kedian"}),
			 "time":10]),
	(["title":"北京城 ←→ 赫图阿拉",
		"from_name":"北京城",
		  "to_name":"赫图阿拉",
		  "from_id":"bj",
			"to_id":"ht",
		"from_file":"/d/beijing/majiu",
		  "to_file":"/d/guanwai/majiu",
			"value":200,
			 "room":({"/d/beijing/kedian", "/d/beijing/nandaj1", "/d/beijing/tian_anm", "/d/beijing/dongcha1", "/d/beijing/dongcha2", "/d/beijing/dongmen", "/d/beijing/road1", "/d/beijing/road2", "/d/beijing/road3", "/d/guanwai/laolongtou", "/d/guanwai/shanhaiguan", "/d/guanwai/road1", "/d/guanwai/road2", "/d/guanwai/road3", "/d/guanwai/ningyuan", "/d/guanwai/road4", "/d/guanwai/road5", "/d/guanwai/road6", "/d/guanwai/road7", "/d/guanwai/road8", "/d/guanwai/muqiao", "/d/guanwai/nancheng", "/d/guanwai/jishi"}),
			 "time":10]),
	(["title":"长安城 ←→ 伊犁城",
		"from_name":"长安城",
		  "to_name":"伊犁城",
		  "from_id":"ca",
			"to_id":"yl",
		"from_file":"/d/changan/majiu",
		  "to_file":"/d/xingxiu/majiu",
			"value":200,
			 "room":({"/d/changan/kedian", "/d/changan/westroad1", "/d/changan/westgate", "/d/changan/road7", "/d/changan/road8", "/d/changan/road9", "/d/lanzhou/caoyuan1", "/d/lanzhou/caoyuan5", "/d/lanzhou/road1", "/d/lanzhou/southgate", "/d/lanzhou/road2", "/d/lanzhou/square", "/d/lanzhou/street2", "/d/lanzhou/street3", "/d/lanzhou/westgate", "/d/xingxiu/xxroad1", "/d/xingxiu/xxroad2", "/d/xingxiu/xxroad3", "/d/xingxiu/jiayuguan", "/d/xingxiu/silk1", "/d/xingxiu/chouchishan", "/d/xingxiu/silk2", "/d/xingxiu/songmoya", "/d/xingxiu/silk3", "/d/xingxiu/shimen", "/d/xingxiu/silk4", "/d/xingxiu/shazhou", "/d/xingxiu/tugu", "/d/xingxiu/silk5", "/d/xingxiu/shanjiao", "/d/xingxiu/yilihe", "/d/xingxiu/yiligate", "/d/xingxiu/yili", "/d/xingxiu/kezhan"}),
			 "time":10]),
	(["title":"福州城 ←→ 泉州城",
		"from_name":"福州城",
		  "to_name":"泉州城",
		  "from_id":"fz",
			"to_id":"qz",
		"from_file":"/d/fuzhou/majiu",
		  "to_file":"/d/quanzhou/majiu",
			"value":200,
			 "room":({"/d/fuzhou/rongcheng", "/d/fuzhou/dongdajie", "/d/fuzhou/dongjiekou", "/d/fuzhou/nandajie", "/d/fuzhou/nanmendou", "/d/fuzhou/nanmen", "/d/fuzhou/zhongzhou", "/d/fuzhou/puxian", "/d/quanzhou/anpingqiao", "/d/quanzhou/shanlu1", "/d/quanzhou/qingyuandong", "/d/quanzhou/huruquan", "/d/quanzhou/shanlu2", "/d/quanzhou/shanlu3", "/d/quanzhou/ruixiangyan", "/d/quanzhou/wangzhouting", "/d/quanzhou/shanlu4", "/d/quanzhou/cienyan", "/d/quanzhou/shanlu5", "/d/quanzhou/shanlu6", "/d/quanzhou/weiyuanlou", "/d/quanzhou/northroad3", "/d/quanzhou/northroad2", "/d/quanzhou/northroad1", "/d/quanzhou/kedian"}),
			 "time":10]),
	(["title":"峨嵋山脚 ←→ 峨嵋山腰",
		"from_name":"峨嵋山脚",
		  "to_name":"峨嵋山腰",
		  "from_id":"em",
			"to_id":"em",
		"from_file":"/d/emei/majiu1",
		  "to_file":"/d/emei/majiu2",
			"value":200,
			 "room":({"/d/emei/caopeng", "/d/emei/qsjie2", "/d/emei/bgsgate", "/d/emei/bgs", "/d/emei/milin1", "/d/emei/fhs", "/d/emei/milin2", "/d/emei/jietuopo", "/d/emei/guanyintang", "/d/emei/guiyunge", "/d/emei/chunyangdian", "/d/emei/shenshuian", "/d/emei/zhongfengsi", "/d/emei/qingyinge", "/d/emei/bailongdong", "/d/emei/wannianan", "/d/emei/shierpan1", "/d/emei/shierpan2", "/d/emei/shierpan3", "/d/emei/shierpan4", "/d/emei/huayanding"}),
			 "time":10]),
	(["title":"永登城 ←→ 灵州城",
		"from_name":"永登城",
		  "to_name":"灵州城",
		  "from_id":"yd",
			"to_id":"lz",
		"from_file":"/d/yongdeng/majiu",
		  "to_file":"/d/lingzhou/majiu",
			"value":200,
			 "room":({"/d/yongdeng/kedian", "/d/yongdeng/yongdeng", "/d/yongdeng/gulang", "/d/yongdeng/dacaigou", "/d/yongdeng/wuqiao", "/d/yongdeng/wuwei", "/d/yongdeng/tumenzi", "/d/yongdeng/shixiazi", "/d/yongdeng/bingcao", "/d/yongdeng/yinpanshui", "/d/yongdeng/guchangcheng", "/d/lingzhou/xuanhebao", "/d/lingzhou/mingshazhou", "/d/lingzhou/qingtongxia", "/d/lingzhou/xiaoba", "/d/lingzhou/huangyangtan", "/d/lingzhou/nanmen", "/d/lingzhou/nandajie", "/d/lingzhou/chema"}),
			 "time":10]),
	(["title":"扬州城 ←→ 开封城",
		"from_name":"扬州城",
		  "to_name":"开封城",
		  "from_id":"yz",
			"to_id":"kf",
		"from_file":"/d/city/majiu",
		  "to_file":"/d/kaifeng/majiu",
			"value":200,
			 "room":({"/d/city/kedian", "/d/city/shilijie5", "/d/city/shilijie4", "/d/city/shilijie3", "/d/city/shilijie2", "/d/city/shilijie1", "/d/city/beimendajie", "/d/city/beimen", "/d/nanyang/yidao1", "/d/nanyang/yidao2", "/d/nanyang/hanshui1", "/d/nanyang/hanshui2", "/d/nanyang/nanmen", "/d/nanyang/dajie1", "/d/nanyang/nanyang", "/d/nanyang/dajie2", "/d/nanyang/beimen", "/d/nanyang/yidao3", "/d/nanyang/ruzhou", "/d/songshan/taishique", "/d/kaifeng/shanlu2", "/d/kaifeng/shanlu1", "/d/kaifeng/jiaowai", "/d/kaifeng/xuandemen", "/d/kaifeng/road6", "/d/kaifeng/road5", "/d/kaifeng/road4", "/d/kaifeng/road3", "/d/kaifeng/road2", "/d/kaifeng/daoxiang1"}),
			 "time":10]),
});
void create()
{
	set_name("马夫", ({"ma fu", "mafu"}));
	set("age", 32);
	set("gender", "男性");
	set("long", "驯马和租马的小贩，给他租金就可以雇到马。\n");
	set("attitude", "peaceful");
	set("str", 24);
	set("dex", 16);
	set("combat_exp", 50000);
	set("shen_type", 1);

	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_skill("parry", 60);
	set_skill("force", 60);
	set_temp("apply/attack", 40);
	set_temp("apply/defense", 40);
	set_temp("apply/armor", 30);
	set("chat_chance", 2);
	setup();
}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && !is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_ride", "ride");
	add_action("do_ridebj", "ridebj");
	add_action("do_rideca", "rideca");
	add_action("do_ridecd", "ridecd");
	add_action("do_ridedl", "ridedl");
	add_action("do_rideem", "rideem");
	add_action("do_ridefs", "ridefs");
	add_action("do_ridefz", "ridefz");
	add_action("do_rideht", "rideht");
	add_action("do_ridehz", "ridehz");
	add_action("do_ridelz", "ridelz");
	add_action("do_rideqz", "rideqz");
	add_action("do_ridesz", "ridesz");
	add_action("do_ridewc", "ridewc");
	add_action("do_ridewx", "ridewx");
	add_action("do_ridexy", "ridexy");
	add_action("do_rideyd", "rideyd");
	add_action("do_rideyl", "rideyl");
	add_action("do_rideyz", "rideyz");
	add_action("do_ridekf", "ridekf");
	add_action("do_rideyp", "rideyp");
}
void greeting(object ob)
{
	int chance;
	chance = random(10);
	if (!ob || environment(ob) != environment())
		return;
	ob->set_temp("ridechance", chance);
	say("马夫点头哈腰地说道：这位客官，是想到这里挑一匹好马吧？\n");
}

int accept_object(object who, object ob)
{
	object myenv;
	if (ob->query("money_id") && ob->value() >= 100)
	{
		if ((int)who->query_temp("ridechance") <= 2)
		{
			message_vision("马夫惊慌地对$N说：对不起这位" + RANK_D->query_respect(who) + "，最近道上不太平，小的可不敢担这个险。\n", who);
			return 0;
		}
		else
		{
			message_vision("马夫对$N说：好！这位" + RANK_D->query_respect(who) + "现在就出发吗？那就上马吧。\n", who);
			who->set_temp("marks/horserent", 1);
			return 1;
		}
	}
	else
		message_vision("马夫皱眉对$N说：您给得也太少了吧？\n", who);
	return 1;
}

int do_ridebj()
{
	do_ride("bj");
	return 1;
}
int do_rideca()
{
	do_ride("ca");
	return 1;
}
int do_ridecd()
{
	do_ride("cd");
	return 1;
}
int do_ridedl()
{
	do_ride("dl");
	return 1;
}
int do_rideem()
{
	do_ride("em");
	return 1;
}
int do_ridefs()
{
	do_ride("fs");
	return 1;
}
int do_ridefz()
{
	do_ride("fz");
	return 1;
}
int do_rideht()
{
	do_ride("ht");
	return 1;
}
int do_ridehz()
{
	do_ride("hz");
	return 1;
}
int do_ridelz()
{
	do_ride("lz");
	return 1;
}
int do_rideqz()
{
	do_ride("qz");
	return 1;
}
int do_ridesz()
{
	do_ride("sz");
	return 1;
}
int do_ridewc()
{
	do_ride("wc");
	return 1;
}
int do_ridewx()
{
	do_ride("wx");
	return 1;
}
int do_ridexy()
{
	do_ride("xy");
	return 1;
}
int do_rideyd()
{
	do_ride("yd");
	return 1;
}
int do_rideyl()
{
	do_ride("yl");
	return 1;
}
int do_rideyz()
{
	do_ride("yz");
	return 1;
}
int do_ridekf()
{
	do_ride("kf");
	return 1;
}
int do_rideyp()
{
	do_ride("yp");
	return 1;
}

int do_ride(string arg)
{
	string horse, *hname = ({MAG "紫骝马" NOR, RED "枣红马" NOR, HIY "黄骠马" NOR});
	int roomi, roomttl, roadi, roadttl, thistmp, direct;
	object ob = this_player(), here = environment(ob);

	if (ob->query_temp("marks/horserent") != 1 && ob->query("age") > 14 &&
		!wizardp(ob))
	{
		if (ob->query_temp("shout"))
		{
			message_vision("马夫对$N说：这位" + RANK_D->query_respect(ob) + "，驿马需要付钱的。\n", ob);
			return 0;
		}
		command("chat 来人啦！" + ob->query("name") + "这个" + RANK_D->query_rude(ob) + "想偷马！\n");
		ob->set_temp("shout", 1);
		return 1;
	}
	roadttl = sizeof(road);
	direct = 0;
	// direct = 1 正向走, direct = 2 反向走, direct = 3 马夫位置不对, 无效
	for (roadi = 0; roadi < roadttl; roadi++)
	{
		if (arg == road[roadi]["to_id"] &&
			file_name(here) == road[roadi]["from_file"])
		{
			direct = 1;
			thistmp = roadi;
		}
		if (arg == road[roadi]["from_id"] &&
			file_name(here) == road[roadi]["to_file"])
		{
			direct = 2;
			thistmp = roadi;
		}
	}
	if (direct == 0)
	{
		message_vision("马夫对$N说：这位" + RANK_D->query_respect(ob) + "，看看牌子吧，这里没有去那儿的直达驿马。\n", ob);
		return 0;
	}
	horse = hname[random(sizeof(hname))];
	message_vision("马夫随手给$N牵来一匹" + horse + "。$N翻身跃上马背。动作潇洒利索。\n路边行人一阵起哄：喔噢喔噢。\n" NOR, ob);
	roomttl = sizeof(road[thistmp]["room"]);
	ob->delete_temp("shout");
	ob->set_temp("ride_horse", 1);
	if (direct == 1)
	{
		for (roomi = 0; roomi < roomttl; roomi++)
		{
			ob->move(road[thistmp]["room"][roomi]);
			tell_room(environment(ob), ob->query("name") + "骑着" + horse + "一路招摇疾驰而过。\n", ({ob}));
		}
		ob->move(road[thistmp]["to_file"]);
		tell_room(environment(ob), ob->query("name") + "骑着" + horse + "一路顺利到达" + road[thistmp]["to_name"] + "。\n");
	}
	else
	{
		for (roomi = roomttl - 1; roomi > -1; roomi--)
		{
			ob->move(road[thistmp]["room"][roomi]);
			tell_room(environment(ob), ob->query("name") + "骑着" + horse + "一路招摇疾驰而过。\n", ({ob}));
		}
		ob->move(road[thistmp]["from_file"]);
		tell_room(environment(ob), ob->query("name") + "骑着" + horse + "一路顺利到达" + road[thistmp]["from_name"] + "。\n");
	}
	ob->delete_temp("ride_horse");
	message_vision("\n$N身形一转，跃下马来，姿态十分优美。闲人也给$N一大哄！\n", ob);
	ob->delete_temp("marks/horserent");
	return 1;
}
