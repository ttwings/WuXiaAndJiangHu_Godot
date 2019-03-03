extends GameObject

class_name Item
#
#// item.c
#
##include <dbase.h>
##include <move.h>
##include <name.h>
#
#inherit F_CLEAN_UP;
#inherit F_DBASE;
#inherit F_MOVE;
#inherit F_NAME;
#
#void setup()
#{
#	seteuid(getuid());
#	set("weight",100);
#}

func setup():
	setuid(getuid())
	set("weight",100)
