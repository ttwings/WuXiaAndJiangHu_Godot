// /clone/quest/questyinshi.c
//// Last Modified by sir on 4.20.2002

#include <login.h>
#include <ansi.h>

inherit NPC;
//inherit F_CLEAN_UP;
inherit F_UNIQUE;
int ask_me(object who);
string *msg_dunno = ({"$n摇摇头，说道：没听说过。\n",
                      "$n疑惑地看着$N，摇了摇头。\n",
                      "$n睁大眼睛望着$N，显然不知道$P在说什么。\n",
                      "$n耸了耸肩，很抱歉地说：无可奉告。\n",
                      "$n说道：嗯....这我可不清楚，你最好问问别人吧。\n",
                      "$n想了一会儿，说道：对不起，你问的事我实在没有印象。\n"});
string *reject_msg = ({"说道：您太客气了，这怎么敢当？\n",
                       "像是受宠若惊一样，说道：请教？这怎么敢当？\n",
                       "笑着说道：您见笑了，我这点雕虫小技怎够资格「指点」您什么？\n"});
string *name_msg = ({
    "书生",
    "客商",
    "锦衣卫士",
    "采药人",
    "江湖艺人",
    "进香客",
    "挑夫",
    "家丁",
    "大汉",
    "官兵",
    "卖花姑娘",
    "趟子手",
    "乞丐",
    "小贩",
    "刀客",
    "剑客",
    "吃客",
    "游方和尚",
    "游方道人",
    "江湖豪客",
});
string *long_id = ({
    "shu sheng",
    "ke shang",
    "wei shi",
    "caiyao ren",
    "jianghu yiren",
    "jinxiang ke",
    "tiao fu",
    "jia ding",
    "da han",
    "guan bing",
    "flower girl",
    "tangzi shou",
    "qi gai",
    "xiao fan",
    "dao ke",
    "jian ke",
    "chi ke",
    "seng ren",
    "dao ren",
    "jianghu haoke",
});

void create()
{
        int i;
        i = random(sizeof(name_msg));
        set_name(name_msg[i], ({long_id[i]}));
        set("gender", random(2) > 0 ? "女性" : "男性");
        set("attitude", "friendly");
        set("chat_chance", 60);
        set("chat_msg", ({
                            (
                                : call_out, "random_move", 0
                                :),
                        }));
        set("inquiry", ([
                             "隐士":(
                                        : ask_me:),
                             "归隐":(
                                        : ask_me:),
                           "yinshi":(
                                        : ask_me:),
                           "guiyin":(
                                        : ask_me:),
        ]));
        set("no_steal", 1);
        set("ask_time", 0);
        set("yinshi", 1);
        set("owner", "mud_os");
        setup();
        carry_object("/d/city/npc/obj/tiejia")->wear();
        carry_object("/clone/food/jiudai");
}

int ask_me(object who)
{
        object ob = this_object(), me = this_player();
        mapping map_status, skill_status, hp_status, skl;
        string *sname, *mname;
        string *skillname;
        int i, j, skilllvl, topexp;
        mixed perform_actions = ({});
        mixed combat_actions = ({});
        mixed msg = ({});

        if (ob->query("ask_time") < 2)
        {
                message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);
                ob->add("ask_time", 1);
        }

        else if (ob->query("ask_time") == 2)
        {
                message_vision(HIC "$N眼中寒光一闪，马上又变得漠然了，只是奇怪地看着$n。\n" NOR, ob, me);
                ob->set("owner", me->query("id"));
                ob->add("ask_time", 1);
        }

        else if (ob->query("ask_time") == 3 && ob->query("family_name") != me->query("family/family_name"))
        {
                hp_status = me->query_entire_dbase();

                ob->add("ask_time", 1);
                ob->set("str", hp_status["str"]);
                ob->set("int", hp_status["int"]);
                ob->set("con", hp_status["con"]);
                ob->set("dex", hp_status["dex"] + 10);
                ob->set("age", hp_status["age"] + 2);

                ob->set("max_jing", hp_status["max_jing"] * 3 / 2);
                ob->set("eff_jing", hp_status["max_jing"] * 3 / 2);
                ob->set("jing", hp_status["jing"] * 3 / 2);
                if ((hp_status["max_qi"] * 2) < 1500)
                {
                        ob->set("max_qi", 1500);
                        ob->set("eff_qi", 1500);
                        ob->set("qi", 1500);
                }
                else
                {
                        ob->set("max_qi", hp_status["max_qi"] * 2);
                        ob->set("eff_qi", hp_status["max_qi"] * 2);
                        ob->set("qi", hp_status["max_qi"] * 2);
                }
                if ((hp_status["max_neili"]) < 1500)
                {
                        ob->set("max_neili", 1500);
                        ob->set("neili", 1500);
                        ob->set("jiali", 50);
                }
                else
                {
                        ob->set("max_neili", hp_status["max_neili"]);
                        ob->set("neili", hp_status["max_neili"]);
                        ob->set("jiali", hp_status["max_neili"] / 30);
                }
                topexp = (int)me->query("combat_exp");
                ob->set("combat_exp", topexp * 3 / 2 + 100);
                ob->set("no_check", 1);
                skl = me->query_skills();
                skilllvl = 200;
                if (sizeof(skl))
                {
                        skillname = sort_array(keys(skl), (
                                                              : strcmp:));
                        for (j = 0; j < sizeof(skl); j++)
                        {
                                if (skilllvl < skl[skillname[j]])
                                        skilllvl = skl[skillname[j]];
                        }
                }
                if (skilllvl >= 300)
                        skilllvl = skilllvl * 5 / 6;
                skill_status = ob->query_skills();
                sname = keys(skill_status);
                for (i = 0; i < sizeof(skill_status); i++)
                {
                        ob->set_skill(sname[i], skilllvl);
                }

                message_vision(HIC "$N叹了口气，说道：“我已归隐多年，你却还要苦苦相逼？”\n" NOR, ob, me);
                message_vision(HIY "$N眼中突然闪过一道寒光，愤怒地瞪着$n，大声喝道：" + RANK_D->query_self_rude(ob) + "就是" + ob->query("fname") + "！" + RANK_D->query_rude(me) + "！纳命来吧！\n" NOR, ob, me);
                me->start_busy(1);
                ob->add_temp("apply/dodge", 150);
                ob->add("yinshi", 1);
                ob->set("title", ob->query("family_name") + "隐士");
                ob->set("name", ob->query("fname"));
                if (mapp(map_status = ob->query_skill_map()))
                {
                        mname = keys(map_status);
                        for (i = 0; i < sizeof(map_status); i++)
                        {
                                perform_actions = get_dir(SKILL_D(map_status[mname[i]]) + "/");
                                for (j = 0; j < sizeof(perform_actions); j++)
                                {
                                        sscanf(perform_actions[j], "%s.c", perform_actions[j]);
                                        if (mname[i] == "force")
                                                msg = ({(
                                                    : exert_function, perform_actions[j]
                                                    :)});
                                        else
                                                msg = ({(
                                                    : perform_action, mname[i] + "." + perform_actions[j]
                                                    :)});
                                        combat_actions += msg;
                                }
                        }
                }
                set("chat_chance_combat", 60);
                set("chat_msg_combat", combat_actions);
                fight_ob(me);
                ob->add("ask_time", 1);
        }
        else if (ob->query("ask_time") >= 3 && ob->query("family_name") == me->query("family/family_name") && ob->query("owner") == me->query("id"))
                message_vision(HIG "$N叹了口气，看着$n笑道：“原来是同门后辈，你这么辛苦地找我，所为何事？”。\n" NOR, ob, me);
        else
                message_vision(HIG "$N叹了口气，看着$n苦笑道：“你这么辛苦地找我，所为何事？”。\n" NOR, ob, me);
        return 1;
}

int random_move()
{
        mapping exits;
        string *dirs, dir, dest;
        object room;

        if (!mapp(exits = environment()->query("exits")))
                return 0;
        dirs = keys(exits);
        dir = dirs[random(sizeof(dirs))];
        dest = exits[dir];
        //if( find_object(dest)->query("no_fight")) return 0;
        //lijia
        if (dest->query("no_fight"))
                return 0;
        //room = find_object(dest);
        //if (!room) room = load_object(room);
        //if (!room || room->query("no_fight"))
        //  return 0;

        if (this_object()->is_fighting())
                return 0;
        command("go " + dir);
        return 1;
}

void init()
{
        add_action("do_hit", "hit");
        add_action("do_hit", "kill");
        add_action("do_hit", "touxi");
        add_action("do_hit", "ansuan");
        add_action("do_hit", "steal");
        add_action("do_halt", "halt");
        add_action("do_halt", "go");
        add_action("do_halt", "surrender");
        add_action("do_qingjiao", "qingjiao");
        add_action("do_look", "look");
}
int do_look(string arg)
{
        object ob = this_object();
        object me = this_player();
        if (!arg || arg != ob->query("id"))
                return 0;

        if (ob->query("yinshi") == 1)
        {
                message_vision("你想看清对方的样子，可却怎么也无法做到！\n", me);
                return 1;
        }
        else
                return 0;
}
int do_qingjiao(string arg)
{
        object ob = this_object(), me = this_player();
        string special;
        int bl, sl, i;

        if (!living(me) || !living(ob))
                return 0;
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢。\n");
        if (ob->is_fighting())
                return notify_fail("对方正忙着呢。\n");
        if (ob->query("ask_time") < 3)
        {
                message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);
        }
        else if (ob->query("owner") != me->query("id") || ob->query("family_name") != me->query("family/family_name"))
        {
                return notify_fail(ob->name() + reject_msg[random(sizeof(reject_msg))]);
        }
        else
        {
                if (!arg)
                        return notify_fail("你要请教什么？\n");
                if (!(special = me->query_skill_mapped(arg)))
                        return notify_fail("你只能从特殊技能中请教基本技能。\n");
                bl = me->query_skill(arg, 1);
                sl = me->query_skill(special, 1);
                i = random(10);
                message_vision(HIG "$N哈哈笑道：“你我既是同门，今日相见也算有缘，好吧我就告诉你些本门武功心得！”。\n" NOR, ob, me);
                if (i < 3)
                {
                        write(HIM "你听了指导，瞑思苦想，对" + to_chinese(arg) + "的体会又深了一层。\n" NOR);
                        me->set_skill(arg, bl + 1);
                }
                else
                {
                        write(HIR "你听了指导，瞑思苦想，对" + to_chinese(special) + "的体会又深了一层。\n" NOR);
                        me->set_skill(special, sl + 1);
                }
                me->add("score", 1000 + random(500));
                me->start_busy(1);
                message_vision(HIG "$N叹了口气，说道：“你我若是有缘，来日自会再聚，时候不早了，我先走一步!”。\n" NOR, ob, me);
                destruct(ob);
        }
}

int do_hit(string arg)
{
        object ob = this_object();
        object me = this_player();
        mapping map_status;
        string *mname;
        int i, j;
        mixed perform_actions = ({});
        mixed combat_actions = ({});
        mixed msg = ({});
        if (!arg || arg != ob->query("id"))
                return 0;

        //if (!ob->query("owner"))
        if ((me->query("id") == ob->query("owner")) && (ob->query("ask_time") == 3))
                return notify_fail("你我无冤无仇，你这又是何必呢？\n");

        else if (ob->query("ask_time") > 3 && ob->query("family_name") == me->query("family/family_name") && ob->query("owner") == me->query("id"))
                return notify_fail("你既然已找到本门前辈，还不趁此大好机会讨教武功？\n");

        else if (ob->query("ask_time") > 3)
        {
                if (mapp(map_status = ob->query_skill_map()))
                {
                        mname = keys(map_status);

                        for (i = 0; i < sizeof(map_status); i++)
                        {
                                perform_actions = get_dir(SKILL_D(map_status[mname[i]]) + "/");
                                for (j = 0; j < sizeof(perform_actions); j++)
                                {
                                        sscanf(perform_actions[j], "%s.c", perform_actions[j]);
                                        if (mname[i] == "force")
                                                msg = ({(
                                                    : exert_function, perform_actions[j]
                                                    :)});
                                        else
                                                msg = ({(
                                                    : perform_action, mname[i] + "." + perform_actions[j]
                                                    :)});
                                        combat_actions += msg;
                                }
                        }
                }
                ob->set("chat_chance_combat", 60);
                ob->set("chat_msg_combat", combat_actions);
                if (me->query("combat_exp") > ob->query("combat_exp"))
                        ob->set("combat_exp", (int)me->query("combat_exp"));
                kill_ob(me);
        }
}

int do_halt()
{
        object me = this_player();
        object ob = this_object();

        if (me->is_fighting(ob) && ob->query("ask_time") >= 3)
        {
                message_vision(HIW "$N喝道：“你既然识破我的身份，就休想活着离开！”\n" NOR, ob, me);
                return 1;
        }
        return 0;
}
void die()
{
        object ob = this_object();
        object me, fme;
        int pot, exp, score;
        me = query_temp("last_damage_from");
        fme = query_temp("last_opponent");

        if (fme &&
            ob->query("ask_time") > 3 && ob->query("owner") == me->query("id") && ob->query("owner") == fme->query("id") && ob->query("family_name") != me->query("family/family_name"))
        {
                pot = 400 + random(400);
                exp = 1500 + random(500);
                score = 300 + random(50);
                me->add("combat_exp", exp);
                me->add("potential", pot);
                me->add("score", score);
                tell_object(me, HIW "你在寻访过程中得到如下奖励：\n");
                tell_object(me, chinese_number(exp) + "点实战经验\n" +
                                    chinese_number(pot) + "点潜能\n" +
                                    chinese_number(score) + "点江湖阅历\n" NOR);
        }
        ::die();
}
