// action.c
// From ES2
// Adapted for XKX

static mixed busy, interrupt  ;
int old_busy = 0;

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
	if( !new_busy ) return;
	if( !intp(new_busy) && !functionp(new_busy) )
		error("action: Invalid busy action type.\n");
// Add being busy time to New busy. By winder. 2001.10.18
// ¸Ädazuo×´Ì¬ÏÂ start_busy(3)µÄbug 
	if( this_object() ->is_busy())
	{
		if (functionp(busy))	old_busy += new_busy;
		else if (intp(busy))	busy += new_busy;
	}
	else
	{
		busy = new_busy;
	}
	if( !intp(new_interrupt) && !functionp(new_interrupt) )
		error("action: Invalid busy action interrupt handler type.\n");
	if (functionp(new_interrupt))
	interrupt = new_interrupt;
	set_heart_beat(1);
}

nomask mixed query_busy() { return busy; }
nomask int is_busy() { return busy!=0; }

// This is called by heart_beat() instead of attack() when a ppl is busy
// doing something else.

void continue_action()
{
	if( intp(busy) && (busy > 0) ) {
		busy--;
		return;
	} else if( functionp(busy) ) {
		if( !evaluate(busy, this_object()) ) {
//			busy = 0;
			busy = old_busy;
			old_busy = 0;
			interrupt = 0;
		}
	} else {
		busy = 0;
		interrupt = 0;
	}
}

void interrupt_me(object who, string how)
{
	if( !busy ) return;

	if( intp(busy) && intp(interrupt) ) {
		if( busy < interrupt ) busy = 0;
	} else if( functionp(interrupt) ) {
		if( evaluate(interrupt, this_object(), who, how) ) {
			busy = old_busy;
			old_busy = 0;
			interrupt = 0;
		}
	}
}
void remove_busy()
{
	old_busy = 0;
	busy = 0;
	interrupt = 0;
}

// This function is for temporary conditions's recovery call_outs, bcz
// such recovery function call_out might be destroyed if some wizard
// destructed the object that is reponsible of it, so we let users launch
// the call_out themself. Thus we can make sure the recovery call_out.
// 
// Because this could cause a serious security problem, so we need highest
// security check here.
int start_call_out(function fun, int delay)
{
	if( !previous_object()
	||  (geteuid(previous_object()) != ROOT_UID
	     && sscanf(base_name(previous_object()),"/kungfu/skill/%*s/%*s")!=2
	     && userp(this_object())
	     && this_player(1) != this_object()))
		return 0;

	call_out("eval_function", delay, fun);
	return 1;
}

 void eval_function(function fun) { evaluate(fun); }

