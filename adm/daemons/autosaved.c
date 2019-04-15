// autosaved.c
// file:		Autosave daemon

// 唯一续命八丸和风传通告 自动存盘由condition做 

inherit F_DBASE;

#include <ansi.h>
#include <net/daemons.h>
#include <net/macros.h>
#include <command.h>

#pragma save_binary



void auto_save();
void check_dns();

void create()
{
	seteuid(ROOT_UID);
	set("channel_id", "内存精灵");
	CHANNEL_D->do_channel(this_object(), "sys", "风闻频道系统已经启动。\n");
	remove_call_out("auto_save");
	call_out("auto_save", 10);
}

void auto_save()
{
	string *ms = ({
HIM"有人：“想逞英雄么？扬州忠烈祠的神龛里的东西，就够你灌一壶的了。”",
HIM"有人：“自古哪个门派没有不肖之徒？问问你掌门师尊你能否协助清理门户，诛杀本门叛徒，追回本门秘籍。”",
HIM"林震南：“我福威镖局近年来越发兴旺了，满货仓的货等待发运，诚请天下有为镖师，共图富贵！”",
HIM"衙役：“最近年成不好，兵匪流行，扬州知府大人正在招募捕快，维持治安。虽无薪水，也能露脸！”",
HIR"某人：“江湖中人最恨欺师叛教之辈了。叛徒都无法得到师长真传，据说各派掌门人都不收叛徒了。”",
HIR"醉仙楼冼老板：“小店承办寿宴、婚宴、豪宴，有钱的大老爷二妹子们快快有请哪！”",
HIR"茶博士：“长安乐坊里，骰子、棋牌、斗鸡、赛龟，真是应有尽有。何不去试试手气？”",
HIR"红娘：“小小红娘我，也算有尺寸功劳。这西湖断桥边，聚散都是有缘的人。”",
HIG"胡庆余：“老夫我，世居杭州，悬壶济世，欲知端的，来看招牌。”",
HIG"某人：“把人卖到丽春院可也太损了，不过大爷我就喜欢卖人，积点德，卖给唐楠也凑合了。”",
HIC"守园道长：“我武当的人参果为万木之祖，那是我辈练武之人梦寐以求的灵丹。”",
HIC"萧峰：“据说关外有新鲜熊胆，吃了大长功力。”",
HIC"某人：“如果你还没想好拜哪个门派，就先到扬州武馆或成都金牛武馆学点基本功。”",
HIG"欧冶子：“天下工匠，我从不做二人想。想要称手兵刃，还到回疆沙漠来找我。”",
HIG"某人：“听说结婚后，在桃花村可以自己盖房生子，真是大妙！夫人，同去同去。”",
HIB"有人：“朱熹老夫子在扬州授业颁发学位，你我兄弟也去混张文凭如何？”",
HIB"梅超风：“老贼，师父他老人家精通阴阳八卦，掐指一算，立知我们所在。我们还是往北逃得越远越好。”",
HIY"风清扬：“独孤九剑为天下剑术之最。要想多胜少败，苦练二十年，便可和天下英雄一较长短了。”",
HIG"慕容复：“以彼之道，还施彼身！如果想体会天下所有绝招的乐趣，与天下英雄一试高低，便得好好学好斗转星移。”",
HIG"王语嫣：“在我家的琅缳玉洞和燕子坞的还施水阁，收藏着普天下门派的秘籍。”",
HIY"张无忌：“乾坤大挪移源自波斯。可化敌攻势于无形，或借势反击，以彼之力，制敌于飘逸之间，是天下一等一的腾挪功夫。”",
HIR"洪七公：“丐帮是天下第一大帮会。探听江湖信息是本帮的拿手本事，本帮的密道穷极数代帮众之力，四通八达。”",
HIG"柳含翠：“想给心上人送朵花儿吗？维扬花店代办时鲜花卉。”",
HIG"殷天正：“老夫内功修为差强人意，火蟾之功却也不小。”",
/*HIW"
    古墓幽居痴心人
    倚天屠龙恨太迟
    绿茵浪子来时路
    酒国英雄遽已逝
    惊涛漫卷千重浪
    梵音轻诵百卷诗
    巴蜀狂人放歌处
    泥潭挚友长相思"*/
	});
	string hui_chun, yan_yang;
	int huichun, yanyang, usernum, i, t, e, p;
	object *ob, *inv;
	object linkob;

message("channel:snow", HIY"【风闻】"+ms[random(sizeof(ms))]+"\n"NOR,users());
	if (file_size("/d/shenlong/cangku.c"))
	  if (!find_object("/d/shenlong/cangku"))
	    load_object("/d/shenlong/cangku");
	if (uptime()<400)
	{
		write_file("/data/XUMING", "1", 1);
		write_file("/data/HUICHUN", "0", 1);
		write_file("/data/YANGYAN", "0", 1);
	}
	hui_chun = read_file("/data/HUICHUN", 1, 1);
	huichun = atoi(hui_chun);
	if(huichun == 0 && uptime() > 86400)
	{
		write_file("/data/HUICHUN", "1", 1);
	}
	yan_yang = read_file("/data/YANGYAN", 1, 1);
	yanyang = atoi(yan_yang);
	if(yanyang == 0 && uptime() > 43200)
	{
		write_file("/data/YANGYAN", "1", 1);
	}
// 清除断线或发呆20分钟以上的玩家 锋锐兵器定时消失
//	ob = objects();
	ob = children(USER_OB);
	for (usernum=0; usernum<sizeof(ob); usernum++)
	{
		if (!clonep(ob[usernum])) continue;
		if (!environment(ob[usernum])) {destruct(ob[usernum]);continue;}
		if(userp(ob[usernum]) && !wizardp(ob[usernum]))
		{
			if( !interactive(ob[usernum])  ||
				( query_idle(ob[usernum]) > 2400 && !environment(ob[usernum])->is_chat_room()))
			{
				if (!interactive(ob[usernum]) && random(3)>0)
				continue;
				if (time()-ob[usernum]->query_temp("LAST_PKER_TIME")<7200)
					continue;
				"/cmds/usr/exit"->savequit(ob[usernum]);
			}
			else
			{
				inv = all_inventory(ob[usernum]);
				for(i=0; i<sizeof(inv); i++)
				{
				 if ( ob[usernum]->is_fighting())
                			inv[i]->set_temp("keep",0);
        			 else
        			  {					   
					  if( !inv[i]->is_unique()	
					  &&  inv[i]->query("weapon_prop/damage") >= 100
				    &&  !inv[i]->query("ownmake"))
					     inv[i]->add_temp("keep", 1);
					  if( inv[i]->query_temp("keep") > 6 )
				  	{
					  	message("channel:snow",HIM"【谣言】某人："+"遗失多年的"NOR+inv[i]->name()+HIM"又重现江湖啦。\n"NOR, users());
				  		log_file( "WEAPON", sprintf("%20s leave %10s at %s.\n", ob[usernum]->query("name")+ "(" + ob[usernum]->query("id")+")", inv[i]->name(), ctime(time())));
					  	destruct(inv[i]);
					  }
				   }
				}
			}
		}
	}

// 泥巴互联启动
	check_dns();
// 判断浩劫系统是否引发
	if ( LOGIN_D->get_dienpc() > 3000 ) call_out("haojie",0);
	remove_call_out("auto_save");
	call_out("auto_save", 1200+random(20));
}

void check_dns()
{
	mapping mud_list;
	mixed *muds;
	object dns;

	if(!dns = find_object(DNS_MASTER))
	// dns not started, not our problem
	return;
	mud_list = (mapping) DNS_MASTER->query_muds();
	muds=keys(mud_list);
	if(sizeof(muds)<= 1)
	{
		destruct(dns);
		call_other(DNS_MASTER,"???");
	}
	return;
}
// 浩劫系统的开始
void haojie()
{
	message("channel:snow",HIM"【谣言】江湖。。。一个充满神秘和危险的世界，太久的平静似乎预示着暴风雨来\n临的前夕，人在江湖，身不由己，总是要去面对一次一次的挑战和危机，谁又能知道明\n天是否依然是如此的安宁呢？\n\n"NOR,users());
	message("channel:snow",HIM"【谣言】江湖上最近出现一个神秘组织，妄想消灭各门派，一统江湖。\n\n\n"NOR,users());
	DISASTER_D->disaster(0);
}

