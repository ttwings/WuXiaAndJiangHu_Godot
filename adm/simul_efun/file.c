// file.c

void cat(string file)
{
	write(read_file(file));
}

void log_file(string file, string text)
{
	write_file(LOG_DIR + file, text);
}

void assure_file(string file)
{
	string path, *dir;
	int i;

	if( file_size(file)!=-1 ) return;

	seteuid(ROOT_UID);
	dir = explode(file, "/");
	dir = dir[0..sizeof(dir)-2];
	path = "/";
	for(i=0; i<sizeof(dir); i++) {
		path += dir[i];
		mkdir(path);
		path += "/";
	}
}

string base_name(object ob)
{
	string file;

	if( sscanf(file_name(ob), "%s#%*d", file)==2 )
		return file;
	else
		return file_name(ob);
}
