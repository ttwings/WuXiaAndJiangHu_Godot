// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by mon@xyj 10/2/97
// for inter mud emote messages.
inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_SAVE;

#include <command.h>
#include <net/dns.h>
#include <net/macros.h>
#include <net/daemons.h>
#include <ansi.h>



mapping emote;

void create()
{
   if(!restore()&&!mapp(emote)) {
     emote = ([]);
   }
}

string query_save_file() {return DATA_DIR + "emoted";}

// send request to another mud.

void send_msg(string channel, object me, string verb, string id, 
       string mud, mixed filter)
{
   mapping minfo;
   string msg;

//   if(!ACCESS_CHECK(previous_object())
//   &&   base_name(previous_object()) != TELL_CMD) return;

   mud = htonn( mud );

   if(mud == mud_nname() || !geteuid(me)) return;

   minfo = (mapping)DNS_MASTER->query_mud_info(mud);
   if (!minfo) return ;

        if(!mapp(emote)) return ;
   if(undefinedp(emote[verb])) return;

   if(!stringp(msg=emote[verb]["others_target"])) return;

   msg=replace_string(msg, "$P", gender_pronoun(me->query("gender")));
   msg=replace_string(msg, "$S", RANK_D->query_self(me));
   msg=replace_string(msg, "$s", RANK_D->query_self_rude(me));
   msg=replace_string(msg, "$C", RANK_D->query_respect(me));
   msg=replace_string(msg, "$c", RANK_D->query_rude(me));
// $N should be replaced upon return of the message.

   msg = replace_string(msg, "|", "");
   msg = replace_string(msg, "@@@", "");
   DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
     "@@@" + "gemote_q" +
     "||NAME:" + Mud_name() +
     "||PORTUDP:" + udp_port() +
     "||CNAME:" + me->name(1) +
     "||MYID:" + me->query("id") +
     "||TARGET:" + id +
//     "||FILTER:" + filter +
                "||CHANNEL:" +channel+
     "||MSG:"+msg+"@@@\n");
        tell_object(me, "网路讯息已送出，请稍候。\n");
}

// Someone on another mud has sent us an intermud emote.
void incoming_request(mapping info)
{
   mapping minfo;
   object target;
   string msg, tar;

   if (info["NAME"] && info["PORTUDP"]) {
     // dont want to tell to ourselves
     if (info["NAME"] == Mud_name())   return;

     // get our info about the sender, ping them if we don't have any
     minfo = DNS_MASTER->query_mud_info(info["NAME"]);
     if (!minfo || !DNS_MASTER->dns_mudp(info["NAME"]))
        PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);

     if (minfo && minfo["HOSTADDRESS"] != info["HOSTADDRESS"]) {
        // Its been faked! 
        dns_log("dns_fake", "Gemote: "+info["NAME"]+
          "("+info["HOSTADDRESS"]+") message:"
          +" "+ info["MSG"]+"\n");
        DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
          "@@@"+DNS_WARNING+
          "||MSG: Faked gemote message: "
          +info["NAME"]+" "+info["MSG"]+
          "||FAKEHOST:"+info["name"]+
          "@@@\n");
        return ;
     }

     msg="";
     tar=info["TARGET"];
     if(stringp(tar)&&tar!="") target=find_player(tar);

     if(objectp(target)) {
       if(target->is_character()&&
          target->query("env/invisibility")<1) {
          msg=info["MSG"];
          msg=replace_string(msg, "$R", RANK_D->query_respect(target));
          msg=replace_string(msg, "$r", RANK_D->query_rude(target));
          msg=replace_string(msg, "$n", target->name()+"("+target->query("id")+"@"+Mud_name()+")");
          msg=replace_string(msg, "$p", gender_pronoun(target->query("gender")));
                  }
                }

       DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
     "@@@" + "gemote_a" +
     "||NAME:" + Mud_name() +
     "||PORTUDP:" + udp_port() +
     "||CNAME:" + info["CNAME"] +
     "||MYID:" + info["MYID"] +
     "||TARGET:" + tar +
//     "||FILTER:" + info["FILTER"] +
                "||CHANNEL:"+info["CHANNEL"]+
     (msg==""? "":"||MSG:"+msg) +
     "@@@\n");

                
   } //if (info["NAME"] && info["PORTUDP"])
}
