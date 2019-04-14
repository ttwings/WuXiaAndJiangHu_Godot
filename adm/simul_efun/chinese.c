
string chinese_number(int i)
{
	return CHINESE_D->chinese_number(i);
}

string to_chinese(string str)
{
	return CHINESE_D->chinese(str);
}

int is_chinese(string str)
{
	if( strlen(str)>=2 && str[0] > 160 && str[0] < 255 ) return 1;
	return 0;
}
