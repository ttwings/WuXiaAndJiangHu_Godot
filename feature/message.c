// message.c

#include <ansi.h>
#include <dbase.h>

#define MAX_MSG_BUFFER 500

static string *msg_buffer = ({});

void receive_message(string msgclass, string msg)
{
	string subclass, *ch;

	if( !interactive(this_object()) ) {
		this_object()->relay_message(msgclass, msg);
		return;
	}
        if (msgclass == "telnet")
        {
                receive(msg);
                return;
        }

	if( sscanf(msgclass, "%s:%s", subclass, msgclass)==2 ) {
		switch(subclass) {
			case "channel":
				if( !pointerp(ch = query("channels"))
				||	member_array(msgclass, ch)==-1 )
					return;
				break;
			case "outdoor":
				if( !environment() || !environment()->query("outdoors") )
					return;
				break;
			default:
				error("Message: Invalid Subclass " + subclass + ".\n");
		}
	}

	if( query_temp("block_msg/all") || query_temp("block_msg/" + msgclass) )
		return;

	if( in_input(this_object()) || in_edit(this_object()) ) {
		if( sizeof(msg_buffer) < MAX_MSG_BUFFER )
			msg_buffer += ({ msg });
	} else
		receive( msg );
}

void write_prompt()
{
	if( sizeof(msg_buffer) ) {
		receive(BOLD "[输入时暂存讯息]\n" NOR);
		for(int i=0; i<sizeof(msg_buffer); i++)
			receive(msg_buffer[i]);
		msg_buffer = ({});
	}
	if(query("env/prompt"))
		write(HIG+query("jing")+NOR"/"HIR+query("qi")+NOR"/"HIY+query("neili")+NOR">");
	else
		write("> ");
}

void receive_snoop(string msg)
{
	receive("%" + msg);
}
