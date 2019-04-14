// rankd.c
// 1996-02-15 dts ranking related to "shen"

#include <ansi.h>

string query_rank(object ob)
{
        mapping fam;

        int shen;
        int budd;
        int age;

        if( ob->is_ghost() )
                return HIB "【 鬼  魂 】" NOR;

        shen = ob->query("shen");
        age = ob->query("age");
        if ( (fam = ob->query("family")) &&
		(fam["family_name"] == "少林派" ||
		fam["family_name"] == "南少林派" ||
		fam["family_name"] == "峨嵋派" ||
		fam["family_name"] == "天龙寺" ||
		fam["family_name"] == "雪山派" ||
		fam["family_name"] == "恒山派"))
                budd = ob->query_skill("buddhism",1);

        switch(ob->query("gender")) {
        case "女性":
                switch(wizhood(ob)) {
                case "(admin)"     : return HIM "【 天  后 】" NOR;
                case "(arch)"      : return HIY "【 仙  妃 】" NOR;
                case "(wizard)"    : return HIG "【 神  女 】" NOR;
                case "(apprentice)": return HIC "【 仙  女 】" NOR;
                case "(immortal)"  : return HIC "【 女仙童 】" NOR;
                default:
                        if (((int)ob->query("betrayer") > 0) &&
                            (!(ob->query("family"))))     return "【 女隐士 】";
                        if (((int)ob->query("PKS") > (int)ob->query("MKS")) &&
                            ((int)ob->query("PKS") > 10)) return "【女杀人魔】";
                        if ((int)ob->query("thief")> 10 ) return "【 女惯窃 】";
                        if (shen >= 100000)       return HIC "【旷世女侠】" NOR;
/*
                        else if (shen >= 10000)   return HIC "【 大女侠 】" NOR;
                        else if (shen >= 1000)    return HIC "【 女  侠 】" NOR;
                        else if (shen >= 100)     return HIC "【 女少侠 】" NOR;
*/
                        else if (shen <=-100000)  return HIC "【 女魔王 】" NOR;
/*
                        else if (shen <= -10000)  return HIC "【 大女魔 】" NOR;
                        else if (shen <= -1000)   return HIC "【 女  魔 】" NOR;
                        else if (shen <= -100)    return HIC "【 女少魔 】" NOR;
*/
                        else
                        switch(ob->query("class")) {
                        case "bonze":
                             if (budd >= 150)     return HIW "【 神  尼 】" NOR;
                             else if (budd >=120) return HIY "【 圣  尼 】" NOR;
                             else if (budd >= 90) return HIY "【 德  尼 】" NOR;
                             else if (budd >= 60) return HIC "【 贤  尼 】" NOR;
                             else if (budd >= 30) return HIG "【 师  太 】" NOR;
                             else if (age  <= 16) return "【 小尼姑 】";
                             else                 return "【 尼  姑 】";
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                             if (age <= 16)       return "【 小道姑 】";
                             else if (age <= 30)  return "【 道  姑 】";
                             else                 return "【 玄  女 】";
                        case "scholar":
                             if (age <= 16)       return "【 女学童 】";
                             else if (age <= 30)  return "【 才  女 】";
                             else                 return "【 女学士 】";
                        case "bandit":            return "【 女飞贼 】";
                        case "dancer":            return "【 舞  者 】";
                        case "legend":            return "【 侠  女 】";
                        case "traveller" :        return "【 浪  女 】";
                        case "ninemoon":          return "【 邪  女 】";
                        case "officer":           /* 官差 */
                             budd = (int)ob->query("officerlvl");
                             if (budd == 9)       return HIR"【 女神捕 】" NOR;
                             else if (budd == 8)  return YEL"【一等侍卫】" NOR;
                             else if (budd == 7)  return YEL"【二等侍卫】" NOR;
                             else if (budd == 6)  return YEL"【三等侍卫】" NOR;
                             else if (budd == 5)  return HIG"【女总捕头】" NOR;
                             else if (budd == 4)  return HIG"【副总捕头】" NOR;
                             else if (budd == 3)  return HIG"【 女捕头 】" NOR;
                             else if (budd == 2)  return HIG"【 女捕快 】" NOR;
                             else if (budd == 1)  return HIG"【实习捕快】" NOR;
                             else return "【 女官差 】";
                        case "fighter":           return "【 女武者 】";
                        case "swordsman":         return "【 女剑士 】";
                        case "alchemist":         return "【 女方士 】";
                        case "shaman":            return "【 女巫医 】";
                        case "lama":              return "【 藏  尼 】";
                        case "generals":          return "【 女  将 】";
                        case "guard":             return "【 女卫士 】";
                        case "minion":            return "【 女家臣 】";
                        case "prostitute":        return "【 妓  女 】";
                        case "beggar":
                             if (shen > 1000)     return "【 女侠丐 】";
                             else if (shen<-1000) return "【 女恶丐 】";
                             else                 return "【 女叫化 】";
                        default:
                                if (age <= 16)    return "【 少  女 】";
                                else              return "【 民  妇 】";
                        }
                }
        default:
                switch(wizhood(ob)) {
                case "(admin)":      if (!ob->query("no_look_wiz")) return HIM "【 天  帝 】" NOR;
                case "(arch)":       if (!ob->query("no_look_wiz")) return HIY "【 天  王 】" NOR;
                case "(wizard)":     if (!ob->query("no_look_wiz")) return HIG "【 神  仙 】" NOR;
                case "(apprentice)": if (!ob->query("no_look_wiz")) return HIC "【 半  仙 】" NOR;
                case "(immortal)":   if (!ob->query("no_look_wiz")) return HIC "【 仙  童 】" NOR;
                default:
                        if (((int)ob->query("betrayer") > 0) &&
                            (!(ob->query("family"))))     return "【 隐  士 】";
                        if (((int)ob->query("PKS") > (int)ob->query("MKS")) &&
                            ((int)ob->query("PKS") > 10)) return "【 杀人魔 】";
                        if ((int)ob->query("thief")> 10 ) return "【 惯  窃 】";
                        if (shen >= 100000)       return HIC "【旷世大侠】" NOR;
/*
                        else if (shen >= 10000)   return HIC "【 大  侠 】" NOR;
                        else if (shen >= 1000)    return HIC "【 侠  客 】" NOR;
                        else if (shen >= 100)     return HIC "【 少  侠 】" NOR;
*/
                        else if (shen <= -100000) return HIC "【 魔  王 】" NOR;
/*
                        else if (shen <= -10000)  return HIC "【 大  魔 】" NOR;
                        else if (shen <= -1000)   return HIC "【 魔  头 】" NOR;
                        else if (shen <= -100)    return HIC "【 少  魔 】" NOR;
*/
                        else switch(ob->query("class")) {
                        case "bonze":
                             if (budd >= 150)     return HIY "【 长  老 】" NOR;
                             else if (budd >=120) return HIY "【 圣  僧 】" NOR;
                             else if (budd >= 90) return HIY "【 罗  汉 】" NOR;
                             else if (budd >= 60) return HIC "【 尊  者 】" NOR;
                             else if (budd >= 40) return HIC "【 禅  师 】" NOR;
                             else if (budd >= 30) return HIG "【 比  丘 】" NOR;
                             else if (age  <= 16) return "【 小和尚 】";
                             else                 return "【 僧  人 】";
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                             if (ob->query_skill("taoism",1)>100)
                                                  return "【 真  人 】";
                             else if (age <= 16)  return "【 小道士 】";
                             else if (age <= 30)  return "【 道  士 】";
                             else                 return "【 道  长 】";
                        case "scholar":
                             if (age <= 16)       return "【 学  童 】";
                             else if (age <= 35)  return "【 书  生 】";
                             else if (age <= 50)  return "【 老秀才 】";
                             else                 return "【 儒  士 】";
                        case "bandit":            return "【 盗  贼 】";
                        case "legend":            return "【 游  侠 】";
                        case "traveller" :        return "【 浪  子 】";
                        case "ninemoon":          return "【 恶  棍 】";
                        case "officer":           /* 官差 */
                             budd = (int)ob->query("officerlvl");
                             if (budd == 9)       return HIR"【 神  捕 】" NOR;
                             else if (budd == 8)  return YEL"【一等侍卫】" NOR;
                             else if (budd == 7)  return YEL"【二等侍卫】" NOR;
                             else if (budd == 6)  return YEL"【三等侍卫】" NOR;
                             else if (budd == 5)  return HIG"【 总捕头 】" NOR;
                             else if (budd == 4)  return HIG"【副总捕头】" NOR;
                             else if (budd == 3)  return HIG"【 捕  头 】" NOR;
                             else if (budd == 2)  return HIG"【 捕  快 】" NOR;
                             else if (budd == 1)  return HIG"【实习捕快】" NOR;
                             else return "【 官  差 】";
                        case "fighter":           return "【 武  者 】";
                        case "swordsman":         return "【 剑  士 】";
                        case "alchemist":         return "【 方  士 】";
                        case "shaman":            return "【 巫  医 】";
                        case "lama":              return "【 喇  嘛 】";
                        case "generals":          return "【 武  将 】";
                        case "guard":             return "【 卫  士 】";
                        case "minion":            return "【 家  臣 】";
                        case "prostitute":        return "【 龟  公 】";
                        case "beggar":
                             if (age <= 16)       return "【 小叫化 】";
                             else if (shen >1000) return "【 侠  丐 】";
                             else if (shen<-1000) return "【 恶  丐 】";
                             else                 return "【 叫化子 】";
                        case "eunach":
                             budd = ob->query_skill("bixie-jian",1);
                             if (budd >= 110)     return HIY "【大内高手】" NOR;
                             else if (budd >=100) return HIY "【东厂万户】" NOR;
                             else if (budd >= 90) return HIY "【东厂千户】" NOR;
                             else if (budd >= 80) return HIY "【东厂百户】" NOR;
                             else if (budd >= 70) return HIY "【东厂十户】" NOR;
                             else if (budd >= 60) return HIY "【东厂公公】" NOR;
                             else                 return "【 内  侍 】";
                        default:
                             if (age <= 16)       return "【 少  年 】";
                             else                 return "【 平  民 】";
                        }
                }
        }
}

string query_respect(object ob)
{
        int age;
        string str;

        if( stringp(str = ob->query("rank_info/respect")) )
                return str;

        age = ob->query("age");
        switch(ob->query("gender")) {
                case "女性":
                        switch(ob->query("class")) {
                        case "bonze":
                        case "lama":
                                if( age < 18 ) return "小师太";
                                else return "师太";
                                break;
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                                if( age < 18 ) return "小仙姑";
                                else return "仙姑";
                                break;
                        default:
                                if( age < 18 ) return "小姑娘";
                                else if( age < 30 ) return "姑娘";
                                else if( age < 50 ) return "大婶";
                                else return "婆婆";
                                break;
                        }
                case "男性":
                default:
                        switch(ob->query("class")) {
                        case "bonze":
                        case "lama":
                                if( age < 18 ) return "小师父";
                                else return "大师";
                                break;
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                                if( age < 18 ) return "道兄";
                                else return "道长";
                                break;
                        case "scholar":
                                if( age < 18 ) return "小相公";
                                else if( age < 50 ) return "相公";
                                else return "老先生";
                                break;
                        case "fighter":
                        case "swordsman":
                                if( age < 18 ) return "小老弟";
                                else if( age < 50 ) return "壮士";
                                else return "老前辈";
                                break;
                        default:
                                if( age < 20 ) return "小兄弟";
                                else if( age < 50 ) return "壮士";
                                else return "老爷子";
                                break;
                        }
        }
}

string query_rude(object ob)
{
        int age;
        string str;

        if( stringp(str = ob->query("rank_info/rude")) )
                return str;

        age = ob->query("age");
        switch(ob->query("gender")) {
                case "女性":
                        switch(ob->query("class")) {
                        case "bonze":
                        case "lama":
                                if( age < 18 ) return "小贼尼";
                                if( age < 30 ) return "贼尼";
                                else return "老贼尼";
                                break;
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                                if( age < 18 ) return "小妖女";
                                if( age < 30 ) return "妖女";
                                else return "老妖婆";
                                break;
                        default:
                                if( age < 18 ) return "小娘皮";
                                if( age < 25 ) return "小贱人";
                                if( age < 40 ) return "贼婆娘";
                                else return "死老太婆";
                                break;
                        }
                case "男性":
                default:
                        switch(ob->query("class")) {
                        case "bonze":
                        case "lama":
                                if( age < 18 ) return "小贼秃";
                                if( age < 50 ) return "死秃驴";
                                else return "老秃驴";
                                break;
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                                if( age < 18 ) return "小杂毛";
                                if( age < 30 ) return "死牛鼻子";
                                else return "老杂毛";
                                break;
                        case "scholar":
                                if( age < 18 ) return "小书呆子";
                                else if( age < 50 ) return "臭书呆子";
                                else return "老童生";
                                break;
                        default:
                                if( age < 20 ) return "小王八蛋";
                                if( age < 30 ) return "直娘贼";
                                if( age < 50 ) return "臭贼";
                                if( age < 80 ) return "老匹夫";
                                else return "老不死";
                                break;
                        }
        }
}

string query_self(object ob)
{
        int age;
        string str;

        if( stringp(str = ob->query("rank_info/self")) )
                return str;

        age = ob->query("age");
        switch(ob->query("gender")) {
                case "女性":
                        switch(ob->query("class")) {
                        case "bonze":
                        case "lama":
                                if( age < 50 ) return "贫尼";
                                else return "老尼";
                                break;
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                                return "贫道";
                                break;
                        default:
                                if( age < 20 ) return "小女子";
                                if( age > 50 ) return "老身";
                                else return "妾身";
                                break;
                        }
                case "男性":
                default:
                        switch(ob->query("class")) {
                        case "bonze":
                        case "lama":
                                if( age < 18 ) return "小衲";
                                if( age < 40 ) return "贫僧";
                                else return "老衲";
                                break;
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                                if( age < 18 ) return "小道";
                                if( age < 30 ) return "贫道";
                                else return "老道";
                                break;
                        case "scholar":
                                if( age < 30 ) return "晚生";
                                else return "不才";
                                break;
                        default:
                                if( age < 50 ) return "在下";
                                else return "老头子";
                                break;
                        }
        }
}

string query_self_rude(object ob)
{
        int age;
        string str;

        if( stringp(str = ob->query("rank_info/self_rude")) )
                return str;

        age = ob->query("age");
        switch(ob->query("gender")) {
                case "女性":
                        switch(ob->query("class")) {
                        case "bonze":
                        case "lama":
                                if( age < 50 ) return "贫尼";
                                else return "老尼";
                                break;
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                                return "本仙姑";
                                break;
                        default:
                                if( age < 20 ) return "本姑娘";
                                if( age < 30 ) return "本姑奶奶";
                                else return "老娘";
                                break;
                        }
                case "男性":
                default:
                        switch(ob->query("class")) {
                        case "bonze":
                        case "lama":
                                if( age < 50 ) return "大和尚我";
                                else return "老和尚我";
                                break;
                        case "taoist":            /*正一派*/
                        case "quanzhen":          /*全真派*/
                                if( age < 30 ) return "本山人";
                                return "老道我";
                                break;
                        case "scholar":
                                if( age < 50 ) return "本相公";
                                else return "老夫子我";
                                break;
                        default:
                                if( age < 20 ) return "本少爷我";
                                if( age < 40 ) return "大爷我";
                                else return "老子";
                                break;
                        }
        }
}
string query_close(object ob)
{
        int a1, a2;

        if (objectp(ob))
        {
                if (a2 = (int)ob->query("mud_age"))
                {
                        a1 = this_player()->query("mud_age");
                } else
                {
                        a1 = this_player()->query("age");
                        a2 = ob->query("age");
                }
        } else
        {
                a1 = this_player()->query("age");
                a2 = 0;
        }

        switch (ob->query("gender")) {
        case "女性" :
                if (a1 >= a2)
                        return "妹妹";
                else
                        return "姐姐";
                break;
        default :
                if (a1 >= a2)
                        return "弟弟";
                else
                        return "哥哥";
        }
}

string query_self_close(object ob)
{
        int a1, a2;

        if (objectp(ob))
        {
                if (a2 = (int)ob->query("mud_age"))
                {
                        a1 = this_player()->query("mud_age");
                } else
                {
                        a1 = this_player()->query("age");
                        a2 = ob->query("age");
                }
        } else
        {
                a1 = this_player()->query("age");
                a2 = 0;
        }

        switch (this_player()->query("gender")) {
        case "女性" :
                if (a1 >= a2)
                        return "姐姐我";
                else
                        return "小妹我";
                break;
        default :
                if (a1 >= a2)
                        return "愚兄我";
                else
                        return "小弟我";
        }
}

