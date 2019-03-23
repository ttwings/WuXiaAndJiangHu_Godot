// command.c
// From ES2
// Modified by Xiang@XKX (12/15/95)

#include <command.h>
#include <dbase.h>
#include <origin.h>

// Let command path be static, thus we can make sure no one can get command
// path directly from restore_object().
static string *path;

// Leave this to allow other objects can search your commands such as
// help, which...
string find_command(string verb)
{
	return (string)COMMAND_D->find_command(verb, path);
}

string remove_leading_space(string arg)
{
	int i;
	for (i = 0; i < strlen(arg); i++)
		if (arg[i..i] != " ")
			return arg[i..strlen(arg)];
	return "";
}

// This is the add_action hook handling movement, commands, emotes and
// channels. Optimization is needed.
private nomask int command_hook(string arg)
{
	string verb, file;

#ifdef PROFILE_COMMANDS
	int mem, utime, stime;
	mapping info;

	mem = memory_info();
	info = rusage();
	utime = info["utime"];
	stime = info["stime"];
#endif

	verb = query_verb();
        if ((verb = remove_leading_space(verb)) == "")
                return 0;
	if( !arg 
	&&	(environment() && stringp(environment()->query("exits/" + verb)))
	&&	stringp(file = find_command("go"))
	&&	call_other(file, "main", this_object(), verb))
		;
	
	else if( stringp(file = find_command(verb)) 
	&& call_other(file, "main", this_object(), arg))
		;

	else if( EMOTE_D->do_emote( this_object(), verb, arg ) )
		;

	else if( CHANNEL_D->do_channel( this_object(), verb, arg ) )
		;


	else return 0;

#ifdef PROFILE_COMMANDS
	info = rusage();
	PROFILE_D->log_command(verb, memory_info() - mem, info["stime"] - stime,
		info["utime"] - utime);
#endif

	return 1;
}

private nomask void set_path(string *p)
{
//	if( origin() != ORIGIN_LOCAL
//	&&	geteuid(previous_object()) != ROOT_UID )
//		return;
	path = p;
}

string *query_path() { return path; }
mixed *query_commands() { return commands(); }

int force_me(string cmd)
{
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;

	return command( this_object()->process_input(cmd) );
}

nomask void enable_player()
{
	if( stringp(query("id")) ) set_living_name(query("id"));
	else set_living_name(query("name"));

	enable_commands();
	add_action("command_hook", "", 1);

	if( !userp(this_object()) )
		set_path(NPC_PATH);
	else if ( this_object()->query("registered") == 0)
		set_path(UNR_PATH);
	else
	switch( wizhood(this_object()) )
	{
		case "(admin)":
			set_path(ADM_PATH);
			enable_wizard();
			break;
		case "(arch)":
			set_path(ARC_PATH);
			enable_wizard();
			break;
		case "(wizard)":
			set_path(WIZ_PATH);
			enable_wizard();
			break;
		case "(apprentice)":
			set_path(APR_PATH);
			enable_wizard();
			break;
		case "(immortal)":
			set_path(IMM_PATH);
			break;
		default:
			set_path(PLR_PATH);
	}
}

nomask void disable_player(string type)
{
	if( geteuid(previous_object())!=ROOT_UID
	&&	previous_object()!=this_object()) return;

	set("disable_type", type);
	disable_commands();
}

