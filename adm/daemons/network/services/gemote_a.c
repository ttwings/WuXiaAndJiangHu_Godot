// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by mon@xyj 10/2/97
// for inter mud emote.
inherit F_DBASE;
inherit F_CLEAN_UP;

#include <net/dns.h>
#include <net/macros.h>
#include <net/services.h>



// They have answered our remote emote request.

void incoming_request(mapping info)
{
   mixed filter;
   mapping muds, svcs, minfo;
   int i;
   string msg;
   string *names;

   if( !ACCESS_CHECK(previous_object())) return;

   if (stringp(info["PORTUDP"]) && stringp(info["HOSTADDRESS"])) {
     if (info["NAME"] == Mud_name())   return ;
     if (!DNS_MASTER->dns_mudp(info["NAME"]))
        PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);
                
     if(!info["MSG"]) { // remote emote failed.
                   return;
     }
     muds=(mapping)DNS_MASTER->query_muds();
     svcs=(mapping)DNS_MASTER->query_svc();

     msg=info["MSG"];
     set("channel_id", "网路动作精灵");
                CHANNEL_D->do_channel(this_object(), lower_case(info["CHANNEL"]),
                  replace_string(msg, "$N", info["CNAME"]), 1);

                msg=replace_string(msg, "$N", info["CNAME"]+
         "("+capitalize(info["MYID"])+"@"+
         Mud_name()+")",1);
                msg=replace_string(msg, "$N", info["CNAME"]);
                  
     names=keys(svcs);
//     filter=info["FILTER"];
                filter=1;
     i=sizeof(names);
     while(i--) {
                  if((names[i]!=mud_nname()) &&
         evaluate(filter, muds[names[i]])) {
         minfo=muds[names[i]];
         if(!mapp(minfo) || !mapp(svcs[names[i]])
         || !(svcs[names[i]]["gwizmsg"] & SVC_UDP))
           continue;
                    
         DNS_MASTER->send_udp(minfo["HOSTADDRESS"],
           minfo["PORTUDP"],
           "@@@"+DNS_GCHANNEL+
           "||NAME:"+Mud_name()+
           "||PORTUDP:"+udp_port()+
           "||USRNAME:"+capitalize(info["MYID"])+
           "||CNAME:"+info["CNAME"]+
           "||MSG:"+msg+
           "||CHANNEL:"+info["CHANNEL"]+
           "||EMOTE:1@@@\n");
                  }
     }


   }
}

void create()
{
   seteuid(ROOT_UID);
}
