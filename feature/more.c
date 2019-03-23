// more.c

#include <ansi.h>

void more(string cmd, string *text, int line)
{
	int i,j;

	switch(cmd) {
		case "":
			for(i=line + 23; line<sizeof(text) && line<i; line++)
				write(text[line] + "\n");
			if( line>=sizeof(text) ) return;
			break;
	case "b":
	line = line - 46;
	if(line<-22) return;
	for(i=line + 23; line < i;line++)
		write(text[line]+"\n");
	break;
		case "q":
			return;
	}
	printf(HIW"== 未完继续 " HIY "%d%%" HIW " == (ENTER 继续下一页，q 离开，b 前一页)\n"NOR,
		(line*100/sizeof(text)) );
	input_to("more", text, line);
}

void start_more(string msg)
{
	more("", explode(msg, "\n"), 0);
}
