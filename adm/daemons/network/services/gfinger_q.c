// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
/*
 * File    : gfinger_q.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is a request for information about a user at another mud.
 */
 

// Ported to ES2 mudlib by Annihilator@ES2 (06/15/95)
inherit F_CLEAN_UP;

#include <net/dns.h>
#include <net/macros.h>



void create() { seteuid(ROOT_UID); }

// Finger a wiz on another mud.
void send_gfinger_q(string mud, string wiz, object them)
{
   mapping minfo;

   if(!ACCESS_CHECK(previous_object())) return;

   if (!them) them = this_player(1);
   mud = htonn( mud );

   if (mud == mud_nname()) return ;

   // make sure we have an entry for the recipient
   minfo = DNS_MASTER->query_mud_info(mud);
   if (!minfo) return ;

   // send the finger
   DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
     sprintf("@@@%s||NAME:%s||PORTUDP:%d||PLAYER:%s||ASKWIZ:%s@@@\n",
     DNS_GFINGER_Q, Mud_name(), udp_port(),
     wiz, (string)them->query("id")));
}

void incoming_request(mapping info)
{
   string reply;

   if (info["NAME"] && info["PORTUDP"] && info["PLAYER"]) {
     if (info["NAME"] == mud_nname()) return ;

     // if we don't have a record of the mud get it
     if (!DNS_MASTER->dns_mudp(info["NAME"]))
        PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);

     // send the finger reply
     reply = (string)FINGER_D->finger_user(lower_case(info["PLAYER"]));
     DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
        sprintf("@@@%s||NAME:%s||PORTUDP:%d||ASKWIZ:%s||MSG:%s@@@\n",
        DNS_GFINGER_A, mud_nname(), udp_port(),
        info["ASKWIZ"], reply));
   }
}

