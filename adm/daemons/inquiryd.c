// inquiryd.c
// Created by Annihilator@ES2 (01-19-95)
// Modified by Xiang for XKX (12/20/95)

// This function handles the default inquiry between ppls and npcs to
// make npc more talktive. This is the '<me> ask <ob> about <topic>'
// case.

#include <ansi.h>

int parse_inquiry(object me, object ob, string topic)
{
	switch( topic ) {
		case "name":
			message_vision( CYN "$N向$n问道：敢问" + RANK_D->query_respect(ob)
				+ "尊姓大名？\n" NOR, me, ob);
			return 1;
		case "here":
			message_vision(CYN "$N向$n问道：这位" + RANK_D->query_respect(ob)
				+ "，" + RANK_D->query_self(me) + "初到贵宝地，不知这里有些什麽风土人情？\n" NOR,
				me, ob);
			return 1;
		case "rumors":
			message_vision(CYN "$N向$n问道：这位" + RANK_D->query_respect(ob)
				+ "，不知最近有没有听说什么消息？\n" NOR, me, ob);
			return 1;
		default:
			return 0;
	}
}
