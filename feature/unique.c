// unique.c

// This function returns 1 if this_object() is not the unique clone in
// the mud. Note that calling this function on master copy always return
// 0.
int is_unique()
{
	return 1;
}

/*nomask int violate_unique()
{
	object *ob;

	if( !clonep(this_object()) ) return 0;

	// Find all the cloned instance of this_object()
	ob = filter_array( children(base_name(this_object())), (: clonep :) );

	return sizeof(ob) > 1;
}*/
nomask object violate_unique()
{
	object *ob;
	int i;
	object env;

	ob = filter_array( children(base_name(this_object())), (: environment :) );
  i = sizeof(ob);
  for (i=0;i<sizeof(ob);i++)
  {
  	env = environment(ob[i]);
  	if (env->is_character())
  	{
  		if (objectp(environment(env))) return ob[i];
  		destruct(env);
  		continue;
  	}
  	return ob[i];
  }
  return 0;
//  if (!sizeof(ob)) return 0;
//	return ob[0];
}

// This function returns the replica of this_object() if any.
object create_replica()
{
	string replica;
	object obj;

	seteuid(getuid());
	if( stringp(replica = this_object()->query("replica_ob")) )
		obj = new(replica);
	else
		obj = 0;
	destruct(this_object());
	return obj;
}
     		         
