// char.c

#pragma save_binary

#include <action.h>
#include <ansi.h>
#include <command.h>
#include <condition.h>
#include <dbase.h>
#include <move.h>
#include <name.h>
#include <skill.h>
#include <team.h>
#include <user.h>
#include <combat.h>

inherit F_ACTION;
inherit F_ALIAS;
inherit F_APPRENTICE;
inherit F_ATTACK;
inherit F_ATTRIBUTE;
inherit F_COMMAND;
inherit F_CONDITION;
inherit F_DAMAGE;
inherit F_DBASE;
inherit F_EDIT;
inherit F_FINANCE;
inherit F_MESSAGE;
inherit F_MORE;
inherit F_MOVE;
inherit F_NAME;
inherit F_SKILL;
inherit F_TEAM;

// Use a tick with longer period than heart beat to save cpu's work
static int tick;

void create()
{
	seteuid(0); // so LOGIN_D can export uid to us
}

// Use this function to identify if an object is a character.
int is_character() { return 1; }

// setup: used to configure attributes that aren't known by this_object()
// at create() time such as living_name (and so can't be done in create()).
void setup()
{
	seteuid(getuid(this_object()));

	set_heart_beat(1);
	tick = 5 + random(10);
	enable_player();

	CHAR_D->setup_char( this_object() );
}

void heart_beat()
{
	int wimpy_ratio, cnd_flag=0;
	mapping my;
	object ob;

	my = query_entire_dbase();

	// If we are dying because of mortal wounds?
	if( my["eff_qi"] < 0 || my["eff_jing"] < 0)
	{
		remove_all_enemy();
		die();
		return;
	}

	// If we're dying or falling unconcious?
	if( my["qi"] < 0 || my["jing"] < 0)
	{
		remove_all_enemy();
		if( !living(this_object()) ||
			this_object()->query_temp("noliving") ) die();
		else unconcious();
		return;
	}

	// Do attack if we are fighting.
	if( is_busy() )
	{
		continue_action();
		// We don't want heart beat be halt eventually, so return here.
		return;
	} else
	{
		// Is it time to flee?
		if( is_fighting() &&
			intp(wimpy_ratio = (int)query("env/wimpy")) &&
			wimpy_ratio > 0 &&
			( my["qi"] * 100 / my["max_qi"] <= wimpy_ratio ||
			my["jing"] * 100 / my["max_jing"] <= wimpy_ratio) )
			GO_CMD->do_flee(this_object());
		// Do attack or clean up enemy if we have fleed.
		if( living(this_object()) &&
			!this_object()->query_temp("noliving") )
			attack();
	}

	if( !userp(this_object()) )
	{
		if( living(this_object()) )
			this_object()->chat();
		// chat() may do anything -- include destruct(this_object())
		if( !this_object() ) return;	
	}
	if (this_object()->query("env/no_fight") && this_object()->is_killing()) 
	 this_object()->delete("env/no_fight");

	if( tick--  ) return;
	else tick = 5 + random(10);

	if (!environment()||!environment()->is_chat_room() ||
	 !query("env/halt_age")) 
	cnd_flag = update_condition();

	// If we are compeletely in peace, turn off heart beat.
	// heal_up() must be called prior to other two to make sure it is called
	// because the && operator is lazy :P
	if( ((cnd_flag & CND_NO_HEAL_UP) || !heal_up()) &&
		!is_fighting() && !interactive(this_object()))
	{
		if( environment() ) {
			ob = first_inventory(environment());
			while(ob && !interactive(ob))
				ob = next_inventory(ob);
		}
		if( !ob ) set_heart_beat(0);
	}

	if( !interactive(this_object()) ) return;

	// Make us a bit older. Only player's update_age is defined.
	// Note: update_age() is no need to be called every heart_beat, it
	//       remember how much time has passed since last call.
	this_object()->update_age();

	if(query_idle(this_object()) > IDLE_TIMEOUT && !wizardp(this_object()))
		this_object()->user_dump(DUMP_IDLE);
}

int visible(object ob)
{
	int lvl, invis;

	lvl = wiz_level(this_object());

	if( lvl > wiz_level(ob) ) return 1;
	if(wizardp(ob)) invis = (int)ob->query("env/invisibility");
	else invis=0;
	if( intp(invis) && (invis > lvl) ) return 0;

	if( ob->is_ghost() ) {
		if( is_ghost() ) return 1;
		if( query_temp("apply/astral_vision") ) return 1;
		return 0;
	}
	return 1;
}
