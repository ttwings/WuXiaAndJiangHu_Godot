// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
/*
 * File    : rhow_q.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is used to ask a mud for a list of users logged on.
 */

// Ported to ES2 mudlib by Annihilator@ES2.

inherit F_CLEAN_UP;
inherit F_DBASE;

#include <command.h>
#include <net/dns.h>
#include <net/macros.h>
#include <net/daemons.h>



/*
* Someone has asked us for a remote who...
* Lets oblige them.
*/
void incoming_request(mapping info)
{
   object *who;
   string str, *bits;
   int i, len, packet, j;

   if(!ACCESS_CHECK(previous_object())) return;

   if (stringp(info["NAME"]) && stringp(info["PORTUDP"])) {
     if (info["NAME"] == Mud_name())   return ;
     if (!DNS_MASTER->dns_mudp(info["NAME"])) {
        PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);
        CHANNEL_D->do_channel( this_object(), "sys",
          sprintf("rwho request from %s rejected, ping_q sent.", info["NAME"] ) );
          return;
     }

//     str = WHO_CMD->main(0, info["VERBOSE"] ? "-l -i": "-i", 1);
                
     str = WHO_CMD->main(0, strlen(info["VERBOSE"])>1 ?
           info["VERBOSE"]: "", 1);
// the above line check strlen is because some MUD send
// VERBOSE:0 as default.
// mon 10/17/97

                //break up into smaller packets.
                len=strlen(str)-1;
                packet=1024; //length of each packet
     for(i=0;i<=len;) {
                  j=i+packet-1;
       while(j<len && str[j..j]!="\n" ) j++;
       if(j>len) j=len;
       DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
        "@@@" + DNS_RWHO_A +
        "||NAME:" + Mud_name() +
        "||PORTUDP:" + udp_port() +
        "||RWHO:" + str[i..j] + 
        "||ASKWIZ:" + info["ASKWIZ"] +
        "@@@\n");
                  i=j+1;
                }
    } //if (stringp(info["NAME"]) && stringp(info["PORTUDP"]))
}

void send_rwho_q(string mud, object them, string verbose)
{
   mapping info;
   string askwiz;

   if(!ACCESS_CHECK(previous_object())
   &&   base_name(previous_object()) != WHO_CMD) return;

   if (!them) them = this_player();
   askwiz = geteuid(them);
   info = DNS_MASTER->query_mud_info(mud);
   if (!info) return ;
   DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
     "@@@"+DNS_RWHO_Q+
     "||NAME:"+ Mud_name() +
     "||PORTUDP:"+ udp_port() +
     "||ASKWIZ:"+ askwiz +
//     (verbose ? "||VERBOSE:1" : "") +
                (strlen(verbose)>0 ? "||VERBOSE:"+ verbose: "") +
     "||@@@\n");
}

void create() { seteuid(ROOT_UID); }

int visiblep(object obj) { return 1; }

string get_name(object obj) { return capitalize(geteuid(obj)); }

int support_rwho_q_VERBOSE() { return 1; }
