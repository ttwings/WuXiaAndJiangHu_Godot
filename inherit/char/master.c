#include <dbase.h>
#include <login.h>
#include <ansi.h>

string *all_basic= ({
"array",	"axe",			"blade",	"claw",		"club",	
"cuff",		"dagger",		"dodge",	"finger",	"force",	
"hammer",	"hand",			"hook",		"leg",		"magic",
"parry",	"spear",		"staff",	"stick",	"strike",
"sword",	"throwing",	"unarmed","whip",
});

int prevent_learn(object me, string skill)
{
	int betrayer;

	if( betrayer = me->query("betrayer") ) {
		if( me->query_skill(skill, 1) >= this_object()->query_skill(skill, 1) - betrayer * 20 ) {
			message_vision("$N神色间似乎对$n不是十分信任，也许是想起$p从前背叛师门的事情 ...。\n",
				this_object(), me );
			command("say 嗯 .... 师父能教你的都教了，其他的你自己练吧。");
			return 1;
		}
	}

	if( !me->is_apprentice_of(this_object())
	&&	(int)this_object()->query_skill(skill, 1) <= (int)me->query_skill(skill, 1) * 3 ) {
//		command("hmm");
//		command("pat " + me->query("id"));
		command("say 虽然你是我门下的弟子，可是并非我的嫡传弟子 ....");
		command("say 我只能教你这些粗浅的本门功夫，其他的还是去找你师父学吧。");
		return 1;
	}

	return 0;
}
public mixed teach_perform(object me,object master,mapping args)
{
        string family,name,perform,msg,msg1,msg2;
        string sk1, sk2, sk3, sk4	;
        int lv1, lv2, lv3, lv4		;
        int i,free,gongxian,shen,force,neili;

        // 至少要三个参数：武功名、绝招中文名、绝招英文名
        if (! stringp(name = args["name"])
           || ! stringp(perform = args["perform"])
           || !stringp(sk1 = args["sk1"])
           )
                return 0;

        // 判断所属门派，如为公共传授，应添加 free 参数
        if (! intp(free = args["free"]) || free <= 0)
        {
                family = master->query("family/family_name");

                if (me->query("family/family_name") != family)
                        return RANK_D->query_respect(me) + "与我" +
                               family + "素无渊源，不知此话从何说起。";
        }

        // 如果已经学会，则返回
        if (me->query("can_perform/"+sk1+"/"+perform))
          return "这招你不是已经会了么，还来问我做什么？";
				//判断神
        if (intp(shen = args["shen"]))
        {
          if (shen < 0 && me->query("shen") > shen)
             return "哼！像你这样的心慈手软之辈，又能干成什么大事？";
          if (shen > 0 && me->query("shen") < shen)
             return "你目前所做的侠义正事不够，这招暂时还不能传你。";
        }

        // 判断门派贡献的要求
        if (intp(gongxian = args["gongxian"])
           && me->query("family/fealty") < gongxian)
           return "你还是多为本门作一些贡献再来吧。";

        // 判断特定的武功需求，其中 sk1 应为主 skills 
         if (!me->query_skill(sk1,1))
            return "你连" + to_chinese(sk1) + "都没学过，还问什么绝招？";
         if (intp(lv1= args["lv1"]) && me->query_skill(sk1,1) < lv1)
           return "你的" + to_chinese(sk1) + "还没学到家，去练好了再来吧。";

        if (stringp(sk2 = args["sk2"]) && intp(lv2 = args["lv2"]) && me->query_skill(sk2,1) < lv2)
            return "你的" + to_chinese(sk2) + "还没有到家，去练好了再来吧。";

        if (stringp(sk3 = args["sk3"]) && intp(lv3 = args["lv3"]) && me->query_skill(sk3,1) < lv3)
            return "你的" + to_chinese(sk3) + "还没到家，去练好了再来吧。";

        if (stringp(sk2 = args["sk4"]) && intp(lv2 = args["lv4"]) && me->query_skill(sk4,1) < lv4)
            return "你的" + to_chinese(sk4) + "还没到家，去练好了再来吧。";

        // 判断绝招对内功的要求
        if (intp(force = args["force"]) && me->query_skill("force") < force)
                return "你的基本内功火候还不够，等练好了再来吧。";

        // 判断绝招对内力上限的要求
        if (intp(neili = args["neili"]) && me->query("max_neili") < neili)
                return "你的内力修为还不够，学不了这招！";

        // 给予学习绝招的描述信息
        if (stringp(msg1 = args["msg1"]))
        {
                msg = msg1;
        } else
        {
                switch (random(4))
                {
                case 0 :
                        msg = "$N微微点了点头，伸手将$n" HIY "招"
                              "至身前，低声在$n" HIY "耳畔讲述了"
                              "半天，还不时伸手比划演示着什么，所"
                              "讲全是" + to_chinese(sk1) + "的精"
                              "微要诣。$n" HIY "听后会心一笑，看"
                              "来对$N的教导大有所悟。";
                        break;

                case 1 :
                        msg = "$N凝视了$n" HIY "许久，方才微微点"
                              "了点头，说道：“我给你演示一遍，可"
                              "看清楚了。”$N话音刚落，随即起身而"
                              "立拉开架势，慢慢的演示开" +
                              to_chinese(sk1) + "的招式。$n" HIY
                              "只觉$N招式精奇，神妙非凡，实乃前所"
                              "未闻，顿时大有感悟。";
                        break;

                case 2 :
                        msg = "$N看了看$n" HIY "，颇为赞许的说道"
                              "：“想不到你的" + to_chinese(sk1) +
                              "进展如此神速，已达此般境界。不易，"
                              "不易。今日我便传你这招，可记清楚了"
                              "。”说完$N便将$n" HIY "招至跟前，"
                              "耐心讲述" + name + "的诸多精要，$n"
                              HIY "一边听一边不住的点头。";
                        break;

                default :
                        msg = "$N哈哈一笑，对$n" HIY "赞道：“不"
                              "错，不错。依照你现在" +
                              to_chinese(sk1) + "的造诣，我便传授"
                              "你" + name + "又有何妨？”说完便只"
                              "见$N从怀中摸出一本颇为古旧的小册子"
                              "，指着其中一段对$n" HIY "仔细讲解"
                              "。$n" HIY "听后沉思良久，若有所悟。";
                        break;
                }
        }
        message_vision(HIY "\n" + msg + "\n\n" NOR, master, me);

        // 学会该项绝招
        me->add("can_perform/"+sk1+"/"+perform, 1);

        // 给予提示信息
        tell_object(me, HIC "你学会了「" HIW + name +
                         HIC "」。\n" NOR);

        // 提升相对应的武功技能
        if (stringp(sk1) ) me->improve_skill(sk1, 500000);
        if (stringp(sk2) ) me->improve_skill(sk2, 500000);
        if (stringp(sk3) ) me->improve_skill(sk3, 500000);
        if (stringp(sk4) ) me->improve_skill(sk4, 500000);


        // 提升主 skill 的基本技能
        for (i = 0; i < sizeof(all_basic); i++)
        {
                if (SKILL_D(sk1)->valid_enable(all_basic[i]))
                        me->improve_skill(all_basic[i], 500000);
        }

        // 消耗门派贡献值
        if (intp(gongxian) && gongxian > 0)
                me->add("family/fealty", -gongxian);
        // 最后的回答信息
        if (stringp(msg2 = args["msg2"]))
        {
                msg = msg2;
        } else
        {
                // 最后的回答信息
                switch (random(5))
                {
                case 0 :
                        msg = "刚才的招式，你明白了多少？";
                        break;
                case 1 :
                        msg = "招式便是如此，你自己下去领悟吧。";
                        break;
                case 2 :
                        msg = "刚才我所传授的全是该招的精意，可记牢了。";
                        break;
                case 3 :
                        msg = "这招你下去后需勤加练习，方能运用自如。";
                        break;
                default :
                        msg = "这招其实并不复杂，你自己下去练习吧。";
                        break;
                }
        }
        return msg;
}
/* 例子
string ask_skill2(object me,string arg)
{
	return teach_perform(this_player(),this_object(),([
                                "perform" : "fugu",				//pfm的代码必需参数
	                              "name"		: "附骨缠身",		//pfm的名称
                                "sk1"			: "jinshe-zhang",//主要的武功的id
                                "lv1"			: 100,					//主要的武功的等级
                                "sk2"			: "strike",		//需要武功sk2的id
	                              "lv2"			: 100,					//需要武功sk2 的等级
//	                            "sk3"			: "throwing",	//武功sk3
//	                            "lv3"			: 100,					
//	                            "sk4"			: "throwing",	//武功sk4
//	                            "lv4"			: 100,					
	                              "neili"		: 300,					//需要内力多少
	                              "free"		: 1, 						//free=1不需要同一门派
//	                            "shen"		: 100,					//需要的shen
//	                            "msg1"		: "教的描述",
//	                            "msg2"		: "教完的描述",
										
																]));
}
*/