// message.c
#include <ansi.h>
varargs void message_vision(string msg, object me, object you)
{
	string my_gender, your_gender, my_name, your_name;
	string str1, str2, str3;

	my_name= me->name();
	my_gender = me->query("gender");
	str1 = replace_string(msg,  "$P", gender_self(my_gender));
	str1 = replace_string(str1, "$N", gender_self(my_gender));
	str3 = replace_string(msg,  "$P", my_name);
	str3 = replace_string(str3, "$N", my_name);
	if( you ) {
		your_name= you->name();
		your_gender= you->query("gender");
		str2 = replace_string(msg,  "$P", gender_pronoun(my_gender));
		str2 = replace_string(str2, "$p", gender_self(your_gender));
		str2 = replace_string(str2, "$N", my_name);
		str2 = replace_string(str2, "$n", gender_self(your_gender));
		message("vision", str2, you);
		str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
		str1 = replace_string(str1, "$n", your_name);
		str3 = replace_string(str3, "$p", your_name);
		str3 = replace_string(str3, "$n", your_name);
	}
	message("vision", str1, me);
	message("vision", str3,  environment(me), ({ me, you}) );
}

varargs void message_combatd(string msg, object me, object you)
{
// 比武现场转播 start
	int userno;
	object *player;
// 比武现场转播 end
	string my_gender, your_gender, my_name, your_name;
	string str1, str2, str3;

	player = users();
	if (me->query("env/combatd")) return;
	my_name= me->name();
	my_gender = me->query("gender");
	str1 = replace_string(msg,  "$P", gender_self(my_gender));
	str1 = replace_string(str1, "$N", gender_self(my_gender));
	str3 = replace_string(msg,  "$P", my_name);
	str3 = replace_string(str3, "$N", my_name);
	if( you ) {
		if (you->query("env/combatd") && !userp(me)) return;
		your_name= you->name();
		your_gender= you->query("gender");
		str2 = replace_string(msg,  "$P", gender_pronoun(my_gender));
		str2 = replace_string(str2, "$p", gender_self(your_gender));
		str2 = replace_string(str2, "$N", my_name);
		str2 = replace_string(str2, "$n", gender_self(your_gender));
		message("vision", str2, you);
		str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
		str1 = replace_string(str1, "$n", your_name);
		str3 = replace_string(str3, "$p", your_name);
		str3 = replace_string(str3, "$n", your_name);
	}
	message("vision", str1, me);
	message("vision", str3,  environment(me), ({ me, you}) );
// 比武现场转播 start
	if ((string)environment(me)->query("short") == "擂台")
	for (userno=0; userno<sizeof(player); userno++)
	    if ((player[userno])->query_temp("view_leitai") &&
             (string)environment(player[userno])->query("short") == "武道场" &&
	        (player[userno]) != me &&
	        (player[userno]) != you) 
	       tell_object(player[userno], str3);
// 比武现场转播 end
}
void tell_object(object ob, string str)
{
	message("tell_object", str, ob);
}

varargs void tell_room(mixed ob, string str, object *exclude)
{
	if( ob ) message("tell_room", str, ob, exclude);
}

void shout(string str)
{
	message("shout", str, users(), this_player());
}

void write(string str)
{
	if( this_player() )
		message("write", str, this_player());
	else if( previous_object() )
		message("write", str, previous_object());
	else
		efun::write(str);
}

varargs void say(string str, mixed exclude)
{
	if( living(previous_object()) )
		message("say", str, environment(previous_object()), previous_object());
	else if( this_player() )
		message("say", str, environment(this_player()), this_player());
}
int notify_fail(string msg)
{
        if (this_player()) 
        {
                this_player()->set_temp("notify_fail", msg);
                return efun::notify_fail(ESC "[256D" ESC "[K" + msg);
        } else
                return 0;
}

string query_fail_msg()
{
        return this_player()->query_temp("notify_fail");
}