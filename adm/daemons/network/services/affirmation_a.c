// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
/*
 * File    : affirmation_a.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is used to confirm tells, and occasionally gwiz.
 */

// Ported to ES2 mudlib by Annihilator@ES2

inherit F_CLEAN_UP;

#include <ansi.h>
#include <net/dns.h>
#include <net/macros.h>


// Affirmation of something.

void incoming_request(mapping info)
{
   object ob;

   if(!ACCESS_CHECK(previous_object())) return;

   if (!info["NAME"] || info["NAME"] == Mud_name()) return;

   if (info["WIZTO"]) {
     if( info["MSG"][sizeof(info["MSG"])] != '\n' ) info["MSG"] += "\n";
     if (ob = find_player(lower_case(info["WIZTO"])))
     tell_object(ob, HIG + info["WIZFROM"]+"通知你："+info["MSG"] + NOR);
   }
}

void send_affirmation_a(string host, string port, string from, string to,
   string msg, string type) 
{
//   if(!ACCESS_CHECK(previous_object())) return;

   DNS_MASTER->send_udp(host, port,
     "@@@"+DNS_AFFIRMATION_A+
     "||NAME:"+Mud_name()+
     "||PORTUDP:"+udp_port()+
     "||WIZTO:"+to+
     "||WIZFROM:"+from+
     "||TYPE:"+type+
     "||MSG:"+msg+"@@@\n");
}

void create() { seteuid(ROOT_UID); }
