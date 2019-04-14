// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
/* File    : mudlist_q.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is used to request a list of muds from another mud.
 */

// Ported to ES2 mudlib by Annihilator (06/15/95)
inherit F_CLEAN_UP;

#include <mudlib.h>
#include <net/dns.h>
#include <net/macros.h>



void create() { seteuid(ROOT_UID); }

/*
 * Incoming mudlist query.  They want to know which muds we know.
 * We will only tell them about the DNS-enabled muds and not the
 * old tcp ones...
 */
string *build_mudlist(mapping muds)
{
   string *names, *ret;
   mapping svc;
   int i, pos;

   // only want to send them DNS muds
   svc = (mapping)DNS_MASTER->query_svc();
   names = keys(svc);
   ret = ({ "" });

   // we want to break the mudlist up into smaller packets
   for (i=0,pos=0;i<sizeof(names);i++) {
     // add the mud to the packet
     ret[pos] += "||"+i+":"+
             (undefinedp(muds[names[i]]["MUDNAME"]) ? ""
          :"|MUDNAME:"+muds[names[i]]["MUDNAME"])+
             (undefinedp(muds[names[i]]["USERS"]) ? ""
          :"|USERS:"+muds[names[i]]["USERS"])+
        "|NAME:" + muds[names[i]]["NAME"] +
        "|HOST:"+muds[names[i]]["HOST"]+
        "|HOSTADDRESS:"+muds[names[i]]["HOSTADDRESS"]+
        "|PORT:"+muds[names[i]]["PORT"]+
        "|PORTUDP:"+muds[names[i]]["PORTUDP"]+
        (undefinedp(muds[names[i]]["MUDLIB"]) ? "" 
             : "|MUDLIB:"+muds[names[i]]["MUDLIB"]);
        (undefinedp(muds[names[i]]["TCP"]) ? "" 
             : "|TCP:"+muds[names[i]]["TCP"]);
     if (strlen(ret[pos]) > 256) {
        // start a new packet
        ret += ({ "" });
        pos++;
     }
   }
   return ret;
}

void send_mudlist_q(string host, string port)
{
   if(!ACCESS_CHECK(previous_object())) return;

   DNS_MASTER->send_udp(host, port, "@@@"+DNS_MUDLIST_Q+
     "||NAME:"+Mud_name()+
     "||PORTUDP:"+udp_port()+ "@@@\n");
}

// someone has requests a mudlist from us
void incoming_request(mapping info)
{
   int i;
   string *bits;

   if(!ACCESS_CHECK(previous_object())) return;

   if (info["PORTUDP"]) {
     bits = build_mudlist((mapping)DNS_MASTER->query_muds());
     for (i=0;i<sizeof(bits);i++) 
        DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
          "@@@"+DNS_MUDLIST_A+ bits[i]+ "@@@\n");
   }
}

