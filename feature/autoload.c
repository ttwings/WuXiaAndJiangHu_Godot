// autoload.c
// From ES2
// Modified by Xiang for XKX (12/15/95)

string *autoload;

void clean_up_autoload() { autoload = 0; }

void save_autoload()
{
	object *inv;
	int i, j;
	mixed param;

	inv = all_inventory();
	autoload = allocate(sizeof(inv));
	for(i=0, j=0; i<sizeof(inv); i++) {
		if( !(param = inv[i]->query_autoload()) ) continue;
		autoload[j] = base_name(inv[i]);
		if( stringp(param) ) autoload[j] += ":" + param;
		j++;
	}
	autoload = autoload[0..j-1];
}

void restore_autoload()
{
	int i;
	object ob;
	string file, param, err;

	if( !pointerp(autoload) ) return;

	for(i=0; i<sizeof(autoload); i++) {
	if (autoload[i] && autoload[i] != "") {
		if( sscanf(autoload[i], "%s:%s", file, param)!=2 ) {
			file = autoload[i];
			param = 0;
		}
		err = catch(ob = new(file));
		if( err || !ob ) {
			write("你觉得似乎失落了什么重要的东西，最好通知一下巫师。\n");
			log_file("AUTOLOAD", sprintf("Fail to autoload %s of %s, error %s\n",
				file, this_object()->query("name"), err));
			continue;
		}
		export_uid(ob);
		ob->move(this_object());
		ob->autoload(param);
	}
	else {
	        write("你觉得似乎失落了什么重要的东西，最好通知一下巫师。\n"); 
                log_file("AUTOLOAD", sprintf("Fail to autoload %s of %s, error %s\n",
                         autoload[i], this_object()->query("name"), err));
	}
	}
	clean_up_autoload();		// To save memory.
}
