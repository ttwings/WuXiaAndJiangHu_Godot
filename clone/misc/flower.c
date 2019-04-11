// flower.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;
mapping *flowers;
mapping flower;

#define flower_path "/clone/flower/"
void create()
{
	seteuid(getuid());
}
string query_save_file()
{
	string id;
	if( !stringp(id = query("owner_id")) ) return 0;
	return DATA_DIR + "flower/" + id[0..0] + "/" + id;
}
int set_owner(string id)
{
	set("owner_id", id);
	return restore();
}
void send_flower(mapping flower)
{
	if( !pointerp(flowers) )
	{
		flowers = ({ flower });
	}
	else flowers += ({ flower });
}
void modify_flower(mapping flower)
{
	if( !pointerp(flowers) )
	{
		flowers = ({ flower });
	}
	else flowers -= ({ flower });
}
int check(object me,object obj)
{
	object ob;
	int i,k;
	string str_time;
	string name_id;

	name_id=me->query("id");
	i=sizeof(flowers);
	if(!i) return 0;
	if(i>0)
	{
		//情人草
		if(flowers[0]["flower_id"]=="qingren cao")
		{
			ob=new(flower_path+"qingren_cao");
			ob->set_amount(flowers[0]["amount"]);
		}
		//红玫瑰
		if(flowers[0]["flower_id"]=="hong meigui")
		{
			ob=new(flower_path+"red_rose");
			ob->set_amount(flowers[0]["amount"]);
		}
		//白玫瑰
		if(flowers[0]["flower_id"]=="bai meigui")
		{
			ob=new(flower_path+"white_rose");
			ob->set_amount(flowers[0]["amount"]);
		}
		//丁香
		if(flowers[0]["flower_id"]=="ding xiang")
		{
			ob=new(flower_path+"ding_xiang");
			ob->set_amount(flowers[0]["amount"]);
		}
		//牡丹
		if(flowers[0]["flower_id"]=="mu dan")
		{
			ob=new(flower_path+"mu_dan");
			ob->set_amount(flowers[0]["amount"]);
		}
		//郁金香
		if(flowers[0]["flower_id"]=="yu jinxiang")
		{
			ob=new(flower_path+"yu_jinxiang");
			ob->set_amount(flowers[0]["amount"]);
		}
		//百合
		if(flowers[0]["flower_id"]=="bai he")
		{
			ob=new(flower_path+"bai_he");
			ob->set_amount(flowers[0]["amount"]);
		}
		//康乃馨
		if(flowers[0]["flower_id"]=="kangnaixin")
		{
			ob=new(flower_path+"kang_naixin");
			ob->set_amount(flowers[0]["amount"]);
		}
		//金鱼草
		if(flowers[0]["flower_id"]=="jinyu cao")
		{
			ob=new(flower_path+"jin_yucao");
			ob->set_amount(flowers[0]["amount"]);
		}
		//火鹤
		if(flowers[0]["flower_id"]=="huo he")
		{
			ob=new(flower_path+"huo_he");
			ob->set_amount(flowers[0]["amount"]);
		}
		//蝴蝶兰
		if(flowers[0]["flower_id"]=="hudie lan")
		{
			ob=new(flower_path+"hu_dielan");
			ob->set_amount(flowers[0]["amount"]);
		}
		//秋海棠
		if(flowers[0]["flower_id"]=="qiu haitang")
		{
			ob=new(flower_path+"qiu_haitang");
			ob->set_amount(flowers[0]["amount"]);
		}
		//石斛兰
		if(flowers[0]["flower_id"]=="shihu lan")
		{
			ob=new(flower_path+"shi_hulan");
			ob->set_amount(flowers[0]["amount"]);
		}
		//马蹄莲
		if(flowers[0]["flower_id"]=="mati lian")
		{
			ob=new(flower_path+"ma_tilian");
			ob->set_amount(flowers[0]["amount"]);
		}

		tell_object(me,"\n一个卖花的小姑娘脚步蹒跚的走了过来。\n");
		tell_object(me,"卖花姑娘走到你跟前欠身说道：“这里有您的花，是"+flowers[0]["from"]+"送给您的。”\n");
		tell_object(me,"卖花姑娘从花篮中拿出一束"+flowers[0]["flowername"]+"交到你手里。\n");
		tell_object(me,"卖花姑娘对你微微一笑道：“花已经送到，小女子告退。”\n");
		tell_object(me,"卖花姑娘走了出去。\n");
		if(!ob) ob=new(flower_path+"qingren_cao");
		ob->move(me);
		modify_flower(flowers[0]);
		delete("flowername");
		delete("flower_id");
		delete("to");
		delete("from");
		delete("amount");
		save();
	}
	return 1;
}

