// atoi.c

int atoi(string str)
{
	int v;

	if( !stringp(str) || !sscanf(str, "%d", v) ) return 0;
	return v;
}
/*
string itoa(int i)
{
	string s;

	if( !sscanf(i, "%s", s) ) return " ";
	return s;
}
*/
