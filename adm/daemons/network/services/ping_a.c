// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
/* File    : ping_a.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is used to answer a ping request from another mud.
 */

// Ported to ES2 mudlib by Annihilator@ES2 (06/15/95)

 
inherit F_CLEAN_UP;

#include <net/dns.h>
#include <net/macros.h>

 
// set our uid
void create()
{
   seteuid(ROOT_UID);
}

// Someone has answered our ping of them.
void incoming_request(mapping info)
{
    if(!ACCESS_CHECK(previous_object())) return;
 
    // set the name in the network master
    if (info["NAME"] && info["NAME"] != Mud_name()) {
     DNS_MASTER->set_mud_info( htonn(info["NAME"]), info);
     // If there's mail to send out, do it now!
     MAIL_Q -> check_for_mail( info["NAME"], 3 );
    }
}
 
