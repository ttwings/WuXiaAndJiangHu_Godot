// 加入login_time_out函数，和logind.c配合，喀擦掉停留
// 在login画面超过30秒的玩家:PP
// Modified by Constant Apr 21 2000

#include <login.h>

#include <dbase.h>

inherit F_DBASE;
inherit F_SAVE;
string *wiz_ip = ({"210.34.1.193",
				   "210.34.4.222",
				   "127.0.0.1",
				   "localhost"});

void logon()
{
	call_out("time_out", LOGIN_TIMEOUT);
	if (member_array(query_ip_name(this_object()), wiz_ip) == -1)
		call_out("login_time_out", 30);
	LOGIN_D->logon(this_object());
}

// Don't destruct(this_object()) in the net_dead() interactive apply or
// there'll be error message: Double call to remove_interactive()
void net_dead()
{
	remove_call_out("time_out");
	call_out("time_out", 1);
}

void time_out()
{
	if (objectp(query_temp("body_ob")))
		return;
	if (interactive(this_object()))
		write("您花在创造新角色的时间太长了，下次再来吧:))\n");
	destruct(this_object());
}

void login_time_out()
{
	if (query_temp("new_char"))
		return;
	if (interactive(this_object()))
		write("您花在连线进入的时间太长了，下次再来吧:))\n");
	destruct(this_object());
}

// This is used by F_SAVE to determinethe file name to save our data.
string query_save_file()
{
	string id;

	id = query("id", 1);
	if (!stringp(id))
		return 0;
	return sprintf(DATA_DIR "login/%c/%s", id[0], id);
}

void receive_message(string type, string str)
{
	if (type != "write")
		return;
	receive(str);
}

void terminal_type(string term_type)
{
	set_temp("terminal_type", term_type);
}

// Protect login object's data against hackers.
nomask mixed set(string prop, mixed data)
{
	if (file_name(previous_object()) == "/clone/npc/qingyun")
		return ::set(prop, data);
	if (geteuid(previous_object()) != ROOT_UID)
		return 0;
	return ::set(prop, data);
}
