// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
/*
//
//  File    :  mail_a.c
//  Author  :  Inspiral@Tabor
//  Created :  93-12-23
//  Purpose :  Part of the DNS mail system.
//
*/
inherit F_CLEAN_UP;
 
#define WHO find_player( "inspiral" )
#define TELL( x ) if( WHO ) tell_object( WHO, x + "\n" )
 
#include <mudlib.h>
#include <net/daemons.h>
#include <net/dns.h>
 

 
// We get here when we get affirmations from muds we are sending
// mail packets to.
void incoming_request( mapping info ) {
  int flag;
  
  flag = 0;
  
  if( !info["NAME"] || !info["PORTUDP"] ) return;
  
  if( info["ENDMSG"] ) {
    // We've received an acknowledgement of an ENDMSG..meaning, they
    // affirm that they got the last part of a message we sent them.
    // We pop it off the stack.
    if( !NETMAIL_D -> pop_mud( info["NAME"] ) ) {
      // Hmm..there apparently was nothing on the stack, yet we got
      // affirmation of an ENDMSG...log this.
      log_file( "mail_a", "unexpected mail_a from " + info["NAME"] + "\n" );
      return;
    }
    TELL( "MAILA: Popped " + info["NAME"] + "." );
    flag = 2;
  }
  
  else {
    if( info["RESEND"] ) {
      // They want us to resend the current message, because either
      // too much time has passed since the last received packet, or
          // some fields got messed up along the way.
      TELL( "MAILA: Got RESEND." );
      flag = 1;
    }
  }
  
  // Let mail_q know that we are ready to either send a new message,
  // or resend the current one.
  MAIL_Q -> check_for_mail( info["NAME"], flag );
}
 
/* EOF */
