// lady1.c

#include <ansi.h>
inherit NPC;
object ob;
int is_ename(string id);
int is_cname(string name);

void create()
{
        set_name("项长老", ({"xiang zhanglao", "xiang", "zhanglao"}));
        set("nickname", "丐帮六老");
        set("gender", "男性");
        set("age", 59);
        set("attitude", "peaceful");
        set("class", "beggar");
        set("beggarlvl", 9);
        set("long",
            "这是丐帮的传功长老，也负责收集各地弟子打听到的各种小道消息。\n" +
                "天下之大，没有他不知道的人物。\n");

        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);

        set("combat_exp", 1500000);
        set("score", 200000);
        set("shen", 100000);

        set_skill("force", 150);          // 基本内功
        set_skill("huntian-qigong", 150); // 混天气功
        set_skill("dodge", 150);          // 基本躲闪
        set_skill("xiaoyaoyou", 150);     // 逍遥游
        set_skill("parry", 150);          // 基本招架
        set_skill("hand", 150);           // 基本手法
        set_skill("suohou-hand", 150);    // 锁喉擒拿手
        set_skill("blade", 150);          // 基本刀法
        set_skill("liuhe-blade", 150);    // 四象六合刀
        set_skill("begging", 100);        // 叫化绝活
        set_skill("checking", 100);       // 道听途说
        set_skill("training", 100);       // 驭兽术

        map_skill("force", "huntian-qigong");
        map_skill("hand", "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("blade", "liuhe-blade");
        map_skill("parry", "liuhe-blade");
        prepare_skill("hand", "suohou-hand");

        set("party/party_name", HIC "丐帮" NOR);
        set("party/rank", RED "九袋长老" NOR);
        set("party/level", 9);
        create_family("丐帮", 10, "传功长老");

        setup();

        carry_object(WEAPON_DIR "gangdao")->wield();
        carry_object("kungfu/class/gaibang/obj/cloth")->wear();
}

int accept_ask(object ob, string topic)
{
        object fob;
        object *livings;
        int i;

        if (topic == ob->query("id") || topic == ob->query("name"))
        {
                command("laugh " + ob->query("id"));
                return 1;
        }
        if (is_cname(topic) && !(ob->query_temp("pay_for_ask")))
        {
                ob->set_temp("give_for_ask", 1);
                ob->set_temp("pending/ask_value", 10000);
                command("say 重名的人可多着呢，我得多花点心思，先拿点黄金出来。");
                return 1;
        }

        if (is_cname(topic) && ob->query_temp("pay_for_ask"))
        {
                livings = livings();
                for (i = sizeof(livings) - 1; i >= 0; i--)
                {
                        if ((livings[i]->query("name") == topic || livings[i]->query("fname") == topic) && environment(livings[i]))
                        {
                                fob = livings[i];
                                break;
                        }
                }
                if (!fob)
                {
                        //        	command("shake");
                        //          command("say 我从没听说过江湖上有这号人物。");
                        //          return 1;
                        return 0;
                }
                ob->delete_temp("pay_for_ask");
        }

        if (is_ename(topic))
        {
                fob = find_player(topic);
                if (!fob || !ob->visible(fob))
                        fob = find_living(topic);
                if (!fob || !ob->visible(fob))
                {
                        //        	command("shake");
                        //          command("say 我从没听说过江湖上有这号人物。");
                        //          return 1;
                        return 0;
                }
                if (!environment(fob))
                {
                        message_vision(CYN "$N" CYN "对$n" CYN "小"
                                           "声道：好像是听说有这么个人物，不过没有弟子向我汇报过他的行踪。\n" NOR,
                                       this_object(), ob);
                        return 1;
                }
        }
        if (!is_ename(topic) && !is_cname(topic))
                return 0;
        if (!environment(fob) || explode(file_name(environment(fob)), "/")[0] != "d")
                return 0;

        //        if ( !ob->query("know_ask_cheap") ||ob->query("ask_cheap")   )
        if (!fob->query("owner") && !userp(fob))
        {
                //        	      ob->set("know_ask_cheap",1);
                ob->set_temp("pending/ask_about", topic);
                if (!objectp(fob))
                {
                        command("slap");
                        return 1;
                }
                ob->set_temp("pending/ask_who", file_name(fob));
                ob->set_temp("pending/ask_value", 2000);
                message_vision(CYN "$N" CYN "皱了皱眉头，对$n" CYN "摇摇"
                                   "头道：看来你这次确实是遇到了困难，收你二十"
                                   "两白银就是了。\n" NOR,
                               this_object(), ob);
                return 1;
        }
        else if (fob->query("owner") && !fob->query("level"))
        {
                ob->set_temp("pending/ask_about", topic);
                ob->set_temp("pending/ask_who", file_name(fob));
                ob->set_temp("pending/ask_value", 30000);
                message_vision(CYN "$N" CYN "嘿嘿奸笑两声，对$n" CYN "小"
                                   "声道：没有问题，不过得要三两黄金，不二"
                                   "价！\n" NOR,
                               this_object(), ob);
                return 1;
        }
        else if (fob->query("owner") && fob->query("level") < 3)
        {
                ob->set_temp("pending/ask_about", topic);
                ob->set_temp("pending/ask_who", file_name(fob));
                ob->set_temp("pending/ask_value", 1000);
                message_vision(CYN "$N" CYN "皱了皱眉头，对$n" CYN "摇摇"
                                   "头道：看来你这次确实是遇到了困难，收你十"
                                   "两白银就是了。\n" NOR,
                               this_object(), ob);
                return 1;
        }
        else if (fob->query("owner") && fob->query("level") >= 3)
        {
                ob->set_temp("pending/ask_about", topic);
                ob->set_temp("pending/ask_who", file_name(fob));
                ob->set_temp("pending/ask_value", 100000);
                message_vision(CYN "$N" CYN "嘿嘿奸笑两声，对$n" CYN "小"
                                   "声道：没有问题，不过得要十两黄金，不二"
                                   "价！\n" NOR,
                               this_object(), ob);
                return 1;
        }
        else if (userp(fob))
        {
                ob->set_temp("pending/ask_about", topic);
                ob->set_temp("pending/ask_who", file_name(fob));
                ob->set_temp("pending/ask_value", 1000000);
                message_vision(CYN "$N" CYN "嘿嘿奸笑两声，对$n" CYN "小"
                                   "声道：找玩家也没有问题，不过得要一百两黄金，不二"
                                   "价！\n" NOR,
                               this_object(), ob);
                return 1;
        }
}

int accept_object(object me, object ob)
{
        string wid;
        object fob;
        int va;
        string old_fob;
        int flag;
        string env;
        string str;
        if (clonep(this_object()))
        {
                command("hehe");
                command("say 俺是真的项长老，如假包换啊！");
                return 1;
        }
        if (!stringp(ob->query("money_id")))
        {
                switch (me->query_temp("beichou_refused"))
                {
                case 0:
                        command("heihei");
                        command("say 这种破烂你留着吧。");
                        me->set_temp("beichou_refused", 1);
                        return 0;

                case 1:
                        message_vision(HIC "$N" HIC "飞起一脚，把$n" HIC "踢了出去，骂道：捣什么乱"
                                           "？\n" NOR,
                                       this_object(), me);
                        break;

                case 2:
                        message_vision(HIC "$N" HIC "飞起一脚，狠狠"
                                           "的把$n" HIC "踢了出去，骂道："
                                           "居然还敢来捣乱？\n" NOR,
                                       this_object(), me);
                        me->receive_damage("qi", 100);
                        me->receive_wound("qi", 10);
                        break;

                default:
                        message_vision(HIC "$N" HIC "大怒，一招飞龙"
                                           "在天，就见$n" HIC "像纸片一"
                                           "样飞了出去。\n" NOR,
                                       this_object(), me);
                        command("chat* kick4 " + me->query("id"));
                        me->unconcious();
                        break;
                }

                me->add_temp("beichou_refused", 1);
                me->move("/d/city/shilijie5");
                message_vision(HIC "只听“啪嗒”的一声，$N" HIC
                                   "狠狠的摔在了地上。\n" NOR,
                               me);
                return 0;
        }
        me->delete_temp("beichou_refused");
        va = me->query_temp("pending/ask_value");
        if (wizardp(me))
                va = 1;
        if (me->query_temp("give_for_ask") && ob->value() >= va)
        {
                me->delete_temp("give_for_ask");
                me->set_temp("pay_for_ask", 1);
                command("say 好吧，说说你想找谁。");
                return 1;
        }
        if (stringp(wid = me->query_temp("pending/ask_about")))
        {
                if (ob->value() < va)
                {
                        message_vision(CYN "$N" CYN "冷笑一声道：就这点钱？"
                                           "打发店小二还差不多。\n" NOR,
                                       this_object());
                        return 0;
                }
                me->delete_temp("pending/ask_about");
                old_fob = me->query_temp("pending/ask_who");
                flag = 1;
                if (!stringp(old_fob) || !objectp(fob = find_object(old_fob)) || !me->visible(fob) || !environment(fob))
                {
                        message_vision(CYN "$N" CYN "挠挠头对$n" CYN "道：怪事…刚"
                                           "才我还有他的消息呢，怎么这么一会儿。\n" NOR,
                                       this_object(), me);
                        return 0;
                }
                //          destruct(ob);
                if (!objectp(fob))
                {
                        command("say 好像有点问题，问一下巫师吧。");
                        return 1;
                }
                env = file_name(environment(fob));
                if (sscanf(env, "/d/%s/%*s", env) != 2)
                {
                        message_vision(CYN "$N" CYN "挠挠头对$n" CYN "道：怪事…刚"
                                           "才我还有他的消息呢，怎么这么一会儿。\n" NOR,
                                       this_object(), me);
                        return 0;
                }

                env = to_chinese(env);
                if (strsrch(env, "/") > 0 || is_ename(env))
                        env = "某个地方";
                //          command("whisper " + me->query("id") +" 刚刚有弟子前来报告：");
                log_file("xiang", me->name() + "询问" + fob->name() + "(" + fob->query("id") + ")\n");

                str = this_object()->name() + "在你的耳边悄声说道：" + fob->name() + "刚才在";
                if (stringp(fob->query("place")))
                        str += env + "的";
                str += environment(fob)->query("short") + "附近出没。\n";

                tell_object(me, str);
                //         if (va <= 2000)
                //               me->add("ask_cheap", -1);
                //         else me->set("ask_cheap", 3);
                return 1;
        }

        if (ob->value())
        {
                message_vision(CYN "$N" CYN "接过$n" CYN "递过去的" + ob->name() +
                                   NOR + CYN "，皱了皱眉，道：你有钱没地方花啊？算了，你不要就"
                                             "给我吧！\n" NOR,
                               this_object(), me);
                return 1;
        }
        return 1;
}

int is_ename(string id)
{
        int i;

        id = replace_string(id, "'s betrayer", "");
        if (strsrch(id, " ") == -1)
                if (strlen(id) < 3 || strlen(id) > 12)
                        return 0;
        id = replace_string(id, " ", "");
        i = strlen(id);
        while (i--)
                if (id[i] < 'a' || id[i] > 'z')
                        return 0;
        //        tell_object(find_player("qingyun"),"is ename\n");
        return 1;
}

int is_cname(string name)
{
        int i;

        i = strlen(name);

        if (strlen(name) < 4 || strlen(name) > 10)
                return 0;
        if (strsrch(name, "　") >= 0)
                return 0;
        while (i--)
        {
                if (name[i] <= ' ')
                        return 0;
                if (i % 2 == 0 && !is_chinese(name[i..< 0]))
                        return 0;
        }

        return 1;
}
