# // /d/changan/clubpoem.c
# inherit  ROOM;
# #include  <ansi.h>
extends Room

# var POEMS=319;

# var author,title,*poem;
# var author1,title1,*poem1;
# var length,length1,running;
# var current,current_all,last,last_all;
# var curr_show;
# var index,chance;
# var poem_index,answerd,ans_curr,ans_last;

# void  new_poem();
# void  copy_to_old();
# void  do_test();
# void  do_init(object  me);
# void  poem_reward(object  me,var arg);
# void  poem_reward1(object  me);
# void  poem_penalty(object  me);
# var  find_newline();
# var mixup(var str);
# var enscript(var arg);


func create  ():
	set("short",  "乐府诗社");
	set("long",  
"""高楼之上，满城繁华尽收眼底。文人骚客都喜欢在这里品茶吟诗，
谈古论今，你瞧，不知谁在茶桌上刚刚写好一首诗(poem)。里边柜台上
新贴了张启事(qishi)，你不由得走过去看了几眼。"""
);

	set("exits",  {
        "down"  :  __DIR__ + "clubup",
        "west"  :  __DIR__ + "shaizi-room",
        "east"  :  __DIR__ + "puke-room",
        "south" :  __DIR__ + "yapai-room",
        "up":  __DIR__ + "club3",
    });

	set("objects",  {
        __DIR__ + "npc/teawaiter":  1,
        __DIR__ + "npc/suanxiucai":  1,
        # //__D + IR__"npc/gongsun":  1,
        __DIR__ + "obj/tables"  :  1,
    });

	set("coor/x", -5030);
	set("coor/y", 1010);
	set("coor/z", 20);
	setup();

    # remove_call_out("do_test");
    # poem_index=1;
    # running=0;

# func init()
# {      
# //          add_action("do_answer","answer");
#           add_action("do_look","look");
          
#           call_out("do_init",1,this_player());

#           if(running==0)  {
#               running=1;
#               new_poem();
#               copy_to_old();
#               new_poem();
#               call_out("do_test",2);
#           }
# }

# void  do_init(object  me)
# {  
#         return;
# }

# var  do_answer(var arg)
# {  
#         object  me=this_player(),ob;

#         if(!arg)  return  notify_fail("回答什么？\n");
        
#         if(me->is_busy())
#             return  notify_fail("你上一个动作还没有完成。\n");

#         if(  living(me)  )  me->receive_damage("sen",5+random(15));

#         if(objectp(ob=present("cha  boshi",this_object()))
#               &&  living(ob))  {
#         switch(random(2))  {
#           case  0:  message_vision("$N说道：是．．．"+arg+"？\n",me);
#                           break;
#           case  1:  message_vision("$N答道："+arg+"？\n",me);
#                           break;
#         }
#         arg=replace_string(arg,"  ","");
#         arg=replace_string(arg,",","");
#         arg=replace_string(arg,"，","");
#         if(arg==current&&strlen(current)>2)  {
#             if(ans_curr==1)  {
#               write("别人已经回答过这句诗了。\n");
#               return  1;
#             }
#             ans_curr=1;
            
#             //change  to  a  new  poem  once  this  one  is  answered.
#             index=length-1;

#             me->set_temp("poem/index",poem_index);
#             poem_reward(me,current_all);
#         }  else  if(arg==last&&strlen(last)>2)  {
#             if(ans_last==1)  {
#               write("别人已经回答过这句诗了。\n");
#               return  1;
#             }
#             ans_last=1;
#             poem_reward(me,last_all);
#         }  else  {
#             message_vision("茶博士摇了摇头：好象不对吧？\n",me);
#             me->add_temp("poem/wrong",1);
#             if(me->query_temp("poem/wrong")>10)  poem_penalty(me);
#         }
#         }  else  {
#             write("现在没有人裁判对错了．．．  ：（\n");
#         }
#         return  1;
# }

# void  poem_penalty(object  me)
# {
#         me->set("sen",-1);
#         me->set_temp("poem/wrong",0);

#         return;
# }

# void  poem_reward(object  me,var arg)
# {
#         me->set_temp("poem/wrong",0);
#         message_vision("茶博士点头道：“"+arg+"”不错！不错！\n",me);
#         poem_reward1(me);
# }

# void  poem_reward1(object  me)
# {    
# 	var  dx,pot,lite;
#         switch(random(3))  {
#           case  0:  dx=4+random(6);
#                           me->add("combat_exp",dx);
# 	          write("你的经验增加了！\n");
# 	          break;
#           case  1:  pot=3+random(4);
# 	          if(me->query("potential")+pot-me->query("learned_povars")<=100)
#                               me->add("potential",pot);
#                           write("你的潜能增加了！\n");
# 	          break;
#           case  2:  lite=4+random(6);
#                           me->improve_skill("literate",lite);
# 	          write("你的读书识字进步了！\n");
# 	          break;
#         }
#         me->add("poem_answered",1);
#         dx=me->query("poem_answered");
# }

# void  do_test()
# {    
#       var  newt;
#       object  ob;
#       var first,second,quest;

#       if(objectp(ob=present("cha  boshi",this_object()))
#                     &&  living(ob))  {
#       if(strlen(current)>2&&ans_curr==0)  {
#           last=current;
#           last_all=current_all;
#           ans_last=0;
#       }
      
#       newt=0;
#       while(newt==0)  {
#         if(!find_newline())  {
#           copy_to_old();
#           new_poem();
#         }  else  {
#             if(sscanf(poem[index],"%s    %s",first,second)==2  &&
#               !sscanf(poem[index],"%*s［")  &&  
#               !sscanf(poem[index],"%*s（")  &&
#               !sscanf(poem[index],"%*s□")  )  {
#                   if(strlen(first)>2&&strlen(second)>2)  {
# 	      newt=1;
#                   }  
#             }
#         }
#       }

#       first=replace_string(first,"  ","");
#       second=replace_string(second,"  ","");
#       current_all=first+"    "+second;
#       ans_curr=0;

#       if(strlen(first)>=14  &&  random(3)==0)  {
#           quest=first;
#       }  else  if  (strlen(second)>=14  &&  random(2)==0)  {
#           quest=second;
#       }  else  {
#           quest=first+second;
#       }
#           current=replace_string(quest,"，","");    //  the  answer
#           quest=mixup(quest);      //  the  question
#           curr_show=quest;
#           switch(random(1))  {
#               case  0:  
#                   tell_room(this_object(),
# 	      "茶博士提笔在墙上写道："+quest+"\n");
#                   break;
#           }
#       }

#       call_out("do_test",60);
#       return;
# }

# var mixup(var str)
# {
#       var  len=strlen(str)/2,i,j,k,l;
#       var ans;

#       for(i=1;i<=random(2)+1;i++)  {
#           j=random(len);
#           k=random(len);
#           if(j==k)  {
#               k++;
#               if(k>=len)  k=0;
#           }
#           if(j>k)  {
#               l=k;  k=j;  j=l;
#           }  //  so  j<k
#           j=j+j;  k=k+k;
#           if(j>0)  ans=str[0..j-1];  
#           else  ans="";
#           ans+=str[k..k+1]+str[j+2..k-1]+str[j..j+1];
#           if(k<len+len-2)  ans+=str[k+2..len+len-1];
#           str=ans;
#       }
#       return  str;
# }

# var  do_look(var arg)
# {      var  i;

#         if(!arg)  return  0;
  
#         if(arg=="poem")  {
#           write("\n\n        "+author1+"："+title1+"\n");
#           for  (i=0;i<length1;i++)  {
#             write("        "+poem1[i]+"\n");
#           }
#           write("\n\n\n");
#           write("当前题目：　　　"+curr_show+"\n\n");
#           return  1;
#         }  else  if(arg=="qishi")  {
#             write("\n"+@LONG
#                       本社新增猜诗游戏，由茶博士将一句诗词的若干字
#               颠倒次序，写在墙上。能准确答出(answer)原句者为胜。

#               例如：茶博士提笔在墙上写道：离离原上草一荣一枯岁
#               你应该回答：answer  离离原上草一岁一枯荣

#                           侠客行一百启: 暂时关闭 answer
# LONG);
#             write("\n\n");
#           return  1;
#         }  else  return  0;

# }

# void  copy_to_old()
# {        var  i;
#           object  ob;

#           author1=author;
#           title1=title;
#           length1=length;
#           poem1=({});
#           last="";
#           for  (i=0;i<length;i++)
#               poem1+=({poem[i]});

#           if(objectp(ob=present("suan  xiucai",this_object()))
#               &&  random(2)==0  &&  living(ob))  {
#               message_vision(({ob->name()+"摇头晃脑地吟诵道：",
#                 ob->name()+"高声朗读道：",
#                 ob->name()+"仿佛在自言自语："})[random(3)]+"\n",ob);
#               message_vision("\n        "+author1+"："+title1+"\n",ob);
#               for  (i=0;i<length1;i++)  {
#                   message_vision("        "+poem1[i]+"\n",ob);
#               }
#               message_vision("\n\n",ob);
#           }

#           return;
# }

# void  new_poem()
# {      var filename,buf;
#         var  i,j,k;

#         length=0;
#         while  (length==0)  {
#         while((k=(1+random(POEMS)))==poem_index);
#         filename=__DIR__"poem/poem"+k;
#         buf=read_file(filename,1,1);
#         sscanf(buf,"%s：%s",author,title);
#         i=0;
#         j=0;
#         poem=({});
#         while(buf=read_file(filename,2+i,1))  {
#             if(strlen(buf)>2)  {
#                 buf=replace_string(buf,"\n","");
#                 poem+=({buf});
# 	j++;
#             }
#             i++;
#         }
#         length=j;
#         }
#         poem_index=k;
#         answerd=0;
#         index=-1;
#         chance=3*100/(1+length);
#         if(length<3)  {
#             chance=100;
#         }
#         return;
# }

# var  find_newline()
# {
#       index++;
#       while(index<length)  {
#           if(random(100)<chance)  {
#               return  1;
#           }  else  index++;
#       }
#       return  0;
# }

# var enscript(var arg)
# {        var result;
#           var *color=({BLK,RED,GRN,YEL,BLU,MAG,CYN,WHT,
#                                           HIR,HIG,HIY,HIB,HBRED,HBGRN,HBYEL,
# 		          HBBLU,HBMAG,BBLK,BRED,BGRN});
#           var  len,i;

#           len=sizeof(color);
#           result="";
#           i=sizeof(arg);
#           while(i>2)  {
#               if(random(2)==0)  {
#                   result=color[random(len)]+NOR+arg[i-2..i-1]+result;
#               }  else  {
#                   result=arg[i-2..i-1]+result;
#               }
#               i-=2;
#           }
#           result=NOR+arg[0..1]+result;

#           return  result;
# }
