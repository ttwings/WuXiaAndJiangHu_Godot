// condition.c
// From ES2
// Modified by Xiang for XKX (12/15/95)

#include <condition.h>

mapping conditions;
mapping type_conditions;

// This function is called by heart_beat to update "continously active"
// conditions. These conditions will be saved as well. Because such type
// of conditions costs heart beat evaluation time, don't make player got
// too much this kind of conditions or you might got lots fo "Too long
// evaluation" error message in the log file.

nomask int update_condition()
{
	mixed *cnd, err;
	int i, flag, update_flag;
	object cnd_d;

	if( !mapp(conditions) || !(i=sizeof(conditions)) ) return 0;
	cnd = keys(conditions);
	update_flag = 0;
	while(i--) {
	// In order to not casue player lost heart beat occasionally while
	// calling external condition daemons, we take careful calling
	// convention here.

		cnd_d = find_object(CONDITION_D(cnd[i]));
		if( !cnd_d )
		{
			err = catch(call_other(CONDITION_D(cnd[i]), "???"));
			cnd_d = find_object(CONDITION_D(cnd[i]));
	// If we failed to load the external condition daemon, remove
	// it before we stuff log files with error messages.
			if( err || !cnd_d )
			{
				log_file("condition.err", sprintf("Failed to load condition daemon %s, removed from %O\nError: %s\n", CONDITION_D(cnd[i]), this_object(), err));
				map_delete(conditions, cnd[i]);
				continue;
			}
		}
	// We assume since the condition daemon is loaded successfully, the
	// calling on its update_condition() should success as well. Because
	// catch() is somewhat costly, so we don't attempt to catch possible
	// error from the call_other. It is condition daemon's reponsibility
	// that don't cause error in users's heart beat.
	// If condition daemon returns 0 (or update_condition() not defined),
	// we can just assume the condition expired and remove it.
		flag = call_other(cnd_d, "update_condition", this_object(), conditions[cnd[i]]);
		if( !( flag & CND_CONTINUE ) ) map_delete(conditions, cnd[i]);
		update_flag |= flag;
	}
	if( !sizeof(conditions) ) conditions = 0;
	return update_flag;
}

// apply_condition()
//
// This function applies the specific condition to the character. Note we 
// don't check if the condition already exist before setting condition info.
// It is condition giver's reponsibility to check if the condition should
// override the old one if same condition already exists.(Use query_condition
// to check)

nomask void apply_condition(string cnd, mixed info)
{
	if( !mapp(conditions) )
		conditions = ([ cnd : info ]);
	else
		conditions[cnd] = info;
}

// query_condition()
//
// This function returns info about the specific condition if any.

nomask mixed query_condition(string cnd)
{
	if( !mapp(conditions) || undefinedp(conditions[cnd]) ) return 0;
	return conditions[cnd];
}

nomask mapping query_entire_conditions()
{
        return conditions;
}

nomask mapping query_conditions_by_type(string required_type)
{
        object cnd_d;
        int i;
        string cnd_type;
        mixed *cnd, err;

        if (!mapp(conditions) || !(i = sizeof(conditions))) return 0;
        type_conditions = 0;
        cnd = keys(conditions);
        while(i--)
	{
	// In order to not casue player lost heart beat occasionally while
	// calling external condition daemons, we take careful calling
	// convention here.
		cnd_d = find_object(CONDITION_D(cnd[i]));
		if (!cnd_d)
		{
			err = catch(call_other(CONDITION_D(cnd[i]), "???"));
			cnd_d = find_object(CONDITION_D(cnd[i]));
	// If we failed to load the external condition daemon, remove
	// it before we stuff log files with error messages.
			if (err || !cnd_d)
			{
				log_file("condition.err", sprintf("Failed to load condition daemon %s, removed from %O\nError: %s\n", CONDITION_D(cnd[i]), this_object(), err));
				if (mapp(conditions))
					map_delete(conditions, cnd[i]);
				continue;
			}
		}
	// We assume since the condition daemon is loaded successfully, the
	// calling on its update_condition() should success as well. Because
	// catch() is somewhat costly, so we don't attempt to catch possible
	// error from the call_other. It is condition daemon's reponsibility
	// that don't cause error in users's heart beat.
	// If condition daemon returns 0 (or update_condition() not defined),
	// we can just assume the condition expired and remove it.
		cnd_type = call_other(cnd_d, "query_type", this_object());
		if (cnd_type == required_type)
		{
			if (!mapp(type_conditions)) type_conditions = ([ cnd[i]: conditions[cnd[i]] ]);
			else type_conditions[cnd[i]] = conditions[cnd[i]];
		}
	}
	return type_conditions;
}

/*
nomask clear_condition()
{
	conditions = 0;
}
*/ 
nomask void clear_condition(string cnd)
{
	if (!cnd)
		conditions = 0;
	else if (mapp(conditions)) map_delete(conditions, cnd);
}
 
nomask void clear_conditions_by_type(string required_type)
{
	object cnd_d;
	int i;
	string cnd_type;
	mixed *cnd, err;

	if (!mapp(conditions) || !(i = sizeof(conditions))) return;
	cnd = keys(conditions);
	while(i--)
	{
	// In order to not casue player lost heart beat occasionally while
	// calling external condition daemons, we take careful calling
	// convention here.

		cnd_d = find_object(CONDITION_D(cnd[i]));
		if (!cnd_d)
		{
			err = catch(call_other(CONDITION_D(cnd[i]), "???"));
			cnd_d = find_object(CONDITION_D(cnd[i]));
	// If we failed to load the external condition daemon, remove
	// it before we stuff log files with error messages.
			if (err || !cnd_d)
			{
				log_file("condition.err",
					sprintf("Failed to load condition daemon %s, removed from %O\nError: %s\n", CONDITION_D(cnd[i]), this_object(), err));
				if (mapp(conditions))
					map_delete(conditions, cnd[i]);
				continue;
			}
		}
	// We assume since the condition daemon is loaded successfully, the
	// calling on its update_condition() should success as well. Because
	// catch() is somewhat costly, so we don't attempt to catch possible
	// error from the call_other. It is condition daemon's reponsibility
	// that don't cause error in users's heart beat.
	// If condition daemon returns 0 (or update_condition() not defined),
	// we can just assume the condition expired and remove it.
		cnd_type = call_other(cnd_d, "query_type", this_object());
		if (cnd_type == required_type) map_delete(conditions, cnd[i]);
	}
}

