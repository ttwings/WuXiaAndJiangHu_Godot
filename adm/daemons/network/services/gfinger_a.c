// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
/*
 * File    : gfinger_a.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol contains the answer to a gfinger request.
 */

// Ported to ES2 mudlib by Annihilator@ES2 (06/15/95)

inherit F_CLEAN_UP;

#include <net/dns.h>
#include <net/macros.h>


// They answered our finger request.  Nice of them.
void incoming_request(mapping info)
{
   object ob;
   mapping mudinfo;

   if(!ACCESS_CHECK(previous_object())) return;

   if (info["PORTUDP"] && info["NAME"]) {
     // dont want to finger ourselves
     if (info["NAME"] == Mud_name()) return ;

     // if we haven't got an entry for the mud, get one.
     if (!DNS_MASTER->dns_mudp(info["NAME"]))
        PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);

     // send the info to the player
     ob = find_player(info["ASKWIZ"]);
     if (ob) {
       mudinfo=DNS_MASTER->query_mud_info(info["NAME"]);
       message("finger", "\n"+
         ((!mudinfo || undefinedp(mudinfo["MUDNAME"]))?
           info["NAME"]:mudinfo["MUDNAME"])+
           "告诉你：\n"+info["MSG"],ob);
     }      
   }
}
