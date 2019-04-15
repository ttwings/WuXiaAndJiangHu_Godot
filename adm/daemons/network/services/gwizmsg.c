// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
/*
 * File    : gwizmsg.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is used to broadcast a channel to other muds.
 */

// Ported to ES2 mudlib by Annihilator (06/15/95)
inherit F_CLEAN_UP;
inherit F_DBASE;

#undef DEBUG

#include <net/macros.h>
#include <net/dns.h>
#include <net/daemons.h>
#include <net/services.h>



void create() { seteuid(ROOT_UID); }

// This is the interface to the intermud channels
void send_msg(string channel, string id, string name, string msg, int emoted)
{
   string *names;
   int i;
   mapping muds;
   mapping svcs;
   mapping minfo;

   if( !this_player()     // Prevent from being called by ourself.
   ||   !ACCESS_CHECK(previous_object())) return;
#ifdef DEBUG
   set("channel_id", "网际巫师频道精灵");
   CHANNEL_D->do_channel(this_object(), "sys", "prepare to send gwizmsg");
#endif
   muds = (mapping)DNS_MASTER->query_muds();
   svcs = (mapping)DNS_MASTER->query_svc();
   msg = replace_string(msg, "|", "");
   msg = replace_string(msg, "@@@", "");
   // use keys(svcs) because none of the muds not in svcs can possibley
   // receive the message
   names = keys(svcs);
   i = sizeof(names);
   while(i--)
     if (names[i] != mud_nname()) {
        minfo = muds[names[i]];
        if(!mapp(minfo) || !mapp(svcs[names[i]])
        || !(svcs[names[i]]["gwizmsg"] & SVC_UDP))
          continue;
        DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
          "@@@" + DNS_GWIZMSG +
          "||NAME:" + Mud_name() +
          "||PORTUDP:" + udp_port() +
          "||WIZNAME:" + capitalize(id) +
          "||CNAME:" + name +
          "||GWIZ:" + msg +
          "||CHANNEL:" + channel +
          (emoted?"||EMOTE:1":"") + "@@@\n");
     }
}

void incoming_request(mapping info)
{
   mapping minfo;
   string tmsg;

#ifdef DEBUG
   set("channel_id", "网际巫师频道精灵");
   CHANNEL_D->do_channel(this_object(), "sys", "gwizmsg received from " + info["NAME"]);
#endif
   if(!ACCESS_CHECK(previous_object())) return;

   if (info["NAME"]) {
     if (info["NAME"] == Mud_name()) return ;

     minfo = DNS_MASTER->query_mud_info(info["NAME"]);
     if (!minfo || !strlen(info["WIZNAME"])
     || !DNS_MASTER->dns_mudp(info["NAME"]))   {
        // We don't accept the message.  But ping them anyway.
        PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);

        return ;
     }
     if (info["HOSTADDRESS"] != minfo["HOSTADDRESS"]) {
        if (info["EMOTE"])
          tmsg = info["WIZNAME"]+"@"+info["NAME"]+" "+info["GWIZ"];
        else
          tmsg = info["WIZNAME"]+"@"+info["NAME"]+": "+info["GWIZ"];

        // Faked.  sheeze... 
        dns_log("dns_fake",sprintf( "Gwiz: %s %s\n%s", ctime(time()),
          info["HOSTADDRESS"],tmsg));
        DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
          "@@@"+DNS_WARNING+
          "||NAME:"+Mud_name()+
          "||MSG: Fake gwiz msg: "+tmsg+
          "||FAKEHOST:"+info["HOSTADDRESS"]+
          "@@@\n");
        return;
     }
     if( undefinedp(info["CNAME"]) )
        set("channel_id", sprintf("%s@%s", info["WIZNAME"], info["NAME"]));
     else
        set("channel_id", sprintf("%s(%s@%s)", info["CNAME"], info["WIZNAME"], info["NAME"]));

     CHANNEL_D->do_channel(this_object(), "gwiz", info["GWIZ"], info["EMOTE"]);

    } //if (info["NAME"])
}

