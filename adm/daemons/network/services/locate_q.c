// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//      /adm/daemons/network/dns_aux/locate_q.c
//      from the TMI-2 Mudlib
//      the locate_q for the UDP locate function
//      created by Descartes of Borg 931017

inherit F_CLEAN_UP;

#include <net/macros.h>
#include <net/dns.h>
#include <net/daemons.h>
#include <net/macros.h>


void send_locate_q(string who) {
    mapping info;
    string *muds;
    int i;

    i = sizeof(muds = keys(info=(mapping)DNS_MASTER->query_muds()));
    while(i--) {
        if(lower_case(muds[i]) == lower_case(Mud_name())) continue;
        DNS_MASTER->send_udp(info[muds[i]]["HOSTADDRESS"],
          info[muds[i]]["PORTUDP"], "@@@"+DNS_LOCATE_Q+
      "||NAME:"+Mud_name()+
      "||PORTUDP:"+ udp_port() +
      "||TARGET:"+lower_case(who)+
      "||ASKWIZ:"+(string)this_player()->query("name")+
        "@@@\n");
    }
    return;
}

void incoming_request(mapping info) {
    string field;

    if(!info["NAME"] || !info["PORTUDP"]) return;
    if(!DNS_MASTER->query_mud_info(info["NAME"]))
      PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);
    if(!info["TARGET"]) field = "NO";
    else field = (find_player(lower_case(info["TARGET"])) ? "YES" : "NO");
    DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
      "@@@"+DNS_LOCATE_A+"||NAME:"+Mud_name()+
      "||PORTUDP:"+udp_port()+
      "||LOCATE:"+field+
      "||TARGET:"+info["TARGET"]+
      "||ASKWIZ:"+info["ASKWIZ"]+"@@@\n");
}
