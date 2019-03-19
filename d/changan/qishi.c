// /d/changan/qishi.c
 
#define WQ_BLACK 1
#define WQ_WHITE 2
#define WQ_BLANK 0
#define WQ_AUX_COLOR 8

#define WQ_NOT_PLAYING 3
#define WQ_PLAYING 4
#define WQ_PLAYING_WUZI 7
#define WQ_JIE_POSSIBLE 5    // jie banned-position possibly exists
#define WQ_NO_JIE 6          // currently no jie-banned position
#define WQ_WINNING 9

#define WQ_POS_OCCUPIED -2
#define WQ_JIE_BANNED  -3
#define WQ_NO_QI_BANNED -4
#include <ansi.h>
inherit ROOM;

int bsize;  // board size bsize*bsize, bsize <= 19
int * game = allocate(361);  // records the current board
int * move = allocate(512);  // records the playing sequence
int move_index;
int * eat_flag = allocate(512);  // records eating information

int jie_flag;  // This flag is set after each 1-stone eat.
int jie_x_ban, jie_y_ban;  // record possible jie-banned position
/* This possible jie-banned position would become real jie-banned
  position if putting in a stone incurs a 1-stone eat. */

int status;
int handicap;
string lastmove; //for undo use
string lastlastmove; //for undo use
int WQ_Started; // for undo and refresh use
int WQ_Undoed; // for undo use
string turn;     // either "black" or "white"

mapping pl = allocate_mapping(2); // black player and white player
int *h_list = ({ 3*19+3, 15*19+15, 15*19+3, 3*19+15, 3*19+9,
     15*19+9, 9*19+3, 9*19+15 }); // for use of handicap
string *xindex = ({ "Ａ","Ｂ","Ｃ","Ｄ","Ｅ","Ｆ","Ｇ","Ｈ","Ｉ",
     "Ｊ","Ｋ","Ｌ","Ｍ","Ｎ","Ｏ","Ｐ","Ｑ","Ｒ","Ｓ" });
string *yindex = ({ "⑴","⑵","⑶","⑷","⑸","⑹","⑺","⑻","⑼",
     "⑽","⑾","⑿","⒀","⒁","⒂","⒃","⒄","⒅","⒆" }); 
string *Ucase = ({ "A","B","C","D","E","F","G","H","I","J","K",
   "L","M","N","O","P","Q","R","S" });
string *lcase = ({ "a","b","c","d","e","f","g","h","i","j","k",
   "l","m","n","o","p","q","r","s" });
string *nindex = ({ "1","2","3","4","5","6","7","8","9","10",
   "11","12","13","14","15","16","17","18","19" });

string lookbook();
void create ()
{
  set ("short", "入神坐照室");
  set ("long", @LONG
只见好大一间房中，除了一张石桌、两只石凳之外，空荡荡的一无
所有，石桌上刻着纵横十九道棋路，对放着一盒黑子、一盒白子。靠窗
处茶几上放着一本棋书(book)和刘仲甫的《棋诀》(jue) ，有空可以读
读(read)看。这棋室中除了几椅棋子之外不设一物，当是免得对局者分
心。围棋十诀云：“贪不得胜  逢危须弃  入界宜缓  慎勿轻速  攻彼
顾我  动须相应  弃子争先  彼强自保  舍小就大  势孤取和”，你可
得小心了。 
    墙上贴了一张小帖子(tie)。
LONG);

  set("objects", ([ /* sizeof() == 4 */
      __DIR__"obj/table" : 1,
      __DIR__"obj/seat" : 2,
  ]));
  set("item_desc", ([ 
	"jue":  HIG"\n	棋诀\n\n"NOR,
	"book": (: lookbook :),
	"tie" :
"
在这里您可以下围棋或五子棋，以下告诉您下棋的步骤：
一、先找好对手，然后分别用 sit black 和 sit white 入座；
二、使用 new 开始一盘新的棋局：new [-5] [-b(numbers)] [-h(numbers)]
    其中 -5 代表下五子棋，不选即为下围棋；
　　-b指定所用棋盘的大小；
    -h指定让子的数目；
　　例如：
　　围棋：new
　　十五乘十五的五子棋：new -5 -b15
　　让九子围棋：new -h9
三、使用 play 轮流走棋：例如 play d4 等等。
四、使用 refresh观看棋盘。
五、使用 undo 悔棋。(目前只提供五子棋的悔棋功能。)
六、使用 leave 站起来开路。
"
  ]));
  set("exits", ([ /* sizeof() == 1 */
      "north" : __DIR__"club3",
  ]));

	set("coor/x", -5030);
	set("coor/y", 1000);
	set("coor/z", 30);
	setup();
}

void init()
{
	status = WQ_NOT_PLAYING;
	add_action("do_sit","sit");
	add_action("do_leave","leave");
	add_action("do_play","play");
	add_action("do_pass","pass");
	add_action("do_resign","resign");
	add_action("do_new","new");   // new game command
	add_action("do_undo","undo"); //undo last move
	add_action("do_refresh","refresh");
	add_action("do_read", "read");
}
string lookbook()
{
	return HIR"\n	棋经十三篇\n\n"NOR;
}
int do_read(string arg)
{
	if (arg=="book")
		this_player()->start_more(read_file(__DIR__"obj/go_book"));
	if (arg=="jue")
		this_player()->start_more(read_file(__DIR__"obj/go_jue"));
	else
                return notify_fail("你要读什么？\n");
	return 1;
}

void check_players()
{
   object bp,wp;
   object rm = this_object();
   if(pl["black"]) {
     bp = pl["black"];
     if(!objectp(bp) || !living(bp) || !present(bp,rm)) {
        map_delete(pl,"black");
        if(living(bp)) bp->delete_temp("weiqi_seat");
     }
   }
   if(pl["white"]) {
     wp = pl["white"];
     if(!objectp(wp) || !living(wp) || !present(wp,rm)) {
        map_delete(pl,"white");
        if(living(wp)) wp->delete_temp("weiqi_seat");
     }
   }
   call_out("check_players",3);
}

int do_sit(string arg)
{
   object me = this_player();

   if(me->query_temp("weiqi_seat"))
     return notify_fail("你已经坐着了。\n");

   if(!arg || (arg != "black" && arg != "white"))
     return notify_fail("你想玩黑棋还是白棋？\n");   

   if (objectp(pl[arg]))
     return notify_fail("这个位子上已经有人了！\n");

   pl[arg] = me;
   me->set_temp("weiqi_seat",arg);
   if(arg == "black")
     message_vision("$N坐上了深色的石凳。\n",me);
   else    message_vision("$N坐上了浅色的石凳。\n",me);
   return(1);
}

int do_leave(string arg)
{
   string s;
   object me = this_player();
   if(!me->query_temp("weiqi_seat"))
     return notify_fail("你没有在下棋。\n");
   s = (string)me->query_temp("weiqi_seat");
   message_vision("$N不想再下了，站了起来。\n",me);
   map_delete(pl,s);
   me->delete_temp("weiqi_seat");
   status=WQ_NOT_PLAYING;   
   return 1;
}

string show_game()
{
   int i,j;
   string s ="\n";

   for(i=0;i<bsize;i++) {
     s += xindex[i];
     s += "　";
     for(j=0;j<bsize;j++) {
        if(game[i*bsize+j]==WQ_BLACK) s += "●";
        else if(game[i*bsize+j]==WQ_WHITE) s+="○";
        else if(i==0 && j==0) s += "┌";
        else if(i==0 && j==bsize-1) s += "┐";
        else if(i==bsize-1 && j==0) s += "└";
        else if(i==bsize-1 && j==bsize-1) s +="┘";
        else if(i==0) s += "┬";
        else if(j==0) s += "├";
        else if(j==bsize-1) s += "┤";
        else if(i==bsize-1) s += "┴";
        else s += "┼";
     }
     s += "\n";
   }
   s += "\n　　";
   for(i=0;i<bsize;i++) s += yindex[i];
   s += "\n\n";
   return(s);
}

int str_to_int(string s)
{
   int i;
   for(i=0;i<19;i++) if(s==nindex[i]) return(i+1);
   return 0;
}

/* Here we allow handicapped game by specifying the number of 
  handicap stones in the command line.  */

int do_new(string arg)
{
        int i,j,num;
        object me = this_player();
   object rm = environment(me);
   object player;
   string * ar;
   string s;

        if(!me->query_temp("weiqi_seat"))
                return notify_fail("你还没坐好呐。\n");
        if(!objectp(pl["black"]) || !objectp(pl["white"]) )
                return notify_fail("还没有对手呐。\n");

   status = WQ_PLAYING;
   jie_flag = WQ_NO_JIE;
   turn="black";
   bsize = 19;
   handicap = 0;

   if(arg) { ar = explode(arg," "); num = sizeof(ar); }
    else num = 0;
   for(i=0;i<num;i++) {
     s = ar[i];
     if(s[0..1]=="-5") status = WQ_PLAYING_WUZI;
     if(s[0..1]=="-b") {
        bsize = str_to_int(s[2..strlen(s)-1]);
        if( bsize<=0 || bsize>19 ) bsize = 19;
     }
     if(s[0..1]=="-h") {
        handicap = str_to_int(s[2..strlen(s)-1]);
        if(handicap<2 || handicap>9) handicap = 0;
     }
   }
   if(bsize!=19 || status!=WQ_PLAYING) handicap = 0;

   for(i=0;i<bsize;i++) for(j=0;j<bsize;j++) game[i*bsize+j]=WQ_BLANK;
   if(handicap!=0) {
     if(handicap%2) {
        game[9*19+9] = WQ_BLACK;
        for(i=0;i<handicap-1;i++) game[h_list[i]]=WQ_BLACK;
     }
      else for(i=0;i<handicap;i++) game[h_list[i]]=WQ_BLACK;
     turn = "white";
   }
   WQ_Started=0;   
   WQ_Undoed=0;
   lastmove="";
   lastlastmove="";
   tell_room(rm,show_game());
        player = pl[turn];
        if(turn=="black") message_vision("现在轮到黑方$N走棋。\n",player);
          else message_vision("现在轮到白方$N走棋。\n",player);
   return(1);
}

int do_refresh(string arg)
{
   object me = this_player();
   object rm = environment(me);
   object player;

   if(status==WQ_NOT_PLAYING) return notify_fail("棋盘上是空的。\n");
   if (WQ_Started)
   {     
     if (turn=="black")
        { tell_object(me,"\n白棋上一步走在了"+lastmove+"\n");
        }
     else
        tell_object(me,"\n黑棋上一步走在了"+lastmove+"\n");
   }
   tell_object(me,show_game());
//   if(pl["black"] || pl["white"]) return 1;
   player = pl[turn];
        if(turn=="black")
      tell_object(me,"现在轮到黑方"+player->name()+"走棋。\n");
     else tell_object(me,"现在轮到白方"+player->name()+"走棋。\n");
   return 1;
}



/* Function 'no_qi' checks if the qi of stone (x,y) is 0.
  The qi of stone (x,y) means the qi of the block which contains (x,y). 
  no_qi works on the data of bd[19][19] with move (x,y) set. 
  Returns 1(no qi) or 0(has qi).
*/

int no_qi(int * bd, int x, int y)
{
   int i,j;
   int qi_flag=0;
   int mycolor, color;
        int * alist=allocate(bsize*bsize);
        int * blist=allocate(bsize*bsize);
   int aindex=0;
   int bindex=0;

   mycolor=bd[x*bsize+y]; // should be either WQ_BLACK or WQ_WHITE

   alist[aindex]=x*bsize+y;   aindex++;
   while(aindex>0 && !qi_flag) {
     i=alist[aindex-1]/bsize;
     j=alist[aindex-1]%bsize;
     aindex--;
     blist[bindex]=i*bsize+j;   bindex++;
     bd[i*bsize+j]=WQ_AUX_COLOR;  // in order to avoid infinite loop
     if(i>0) {
        color=bd[(i-1)*bsize+j];
        if(color==WQ_BLANK) qi_flag=1;
         else if(color==mycolor){
          alist[aindex]=(i-1)*bsize+j; aindex++;
        }
     }
     if(i<bsize-1) {
        color=bd[(i+1)*bsize+j];
        if(color==WQ_BLANK) qi_flag=1;
          else if(color==mycolor) {
          alist[aindex]=(i+1)*bsize+j; aindex++;
        }
     }
     if(j>0) {
        color=bd[i*bsize+j-1];
        if(color==WQ_BLANK) qi_flag=1;
          else if(color==mycolor) {
          alist[aindex]=i*bsize+j-1; aindex++;
        }
     }
     if(j<bsize-1) {
        color = bd[i*bsize+j+1];
        if(color==WQ_BLANK) qi_flag=1;
          else if(color==mycolor) {
          alist[aindex]=i*bsize+j+1; aindex++;
        }
     }
   }

   while(bindex>0) { bd[blist[bindex-1]] = mycolor; bindex--; }

   return(!qi_flag);

}

/* This routine removes a block of stones which contains (x,y).
  It returns the number of stones removed. */

int remove_block(int * bd, int x, int y)
{
   int i,j;
   int color;
   int * alist=allocate(bsize*bsize);
   int * blist=allocate(bsize*bsize);
   int aindex=0;
   int bindex=0;
   int num;

   color=bd[x*bsize+y]; // should be either WQ_BLACK or WQ_WHITE
   alist[0]=x*bsize+y;   aindex++;
        while(aindex>0) {
                i=alist[aindex-1]/bsize;
                j=alist[aindex-1]%bsize;
                aindex--;
                blist[bindex]=i*bsize+j;   bindex++;
                bd[i*bsize+j]=WQ_AUX_COLOR; 
                if(i>0 && color==bd[(i-1)*bsize+j]) {
                        alist[aindex]=(i-1)*bsize+j; aindex++;
                }
                if(i<bsize-1 && color==bd[(i+1)*bsize+j]) {
                        alist[aindex]=(i+1)*bsize+j; aindex++;
                }
                if(j>0 && color==bd[i*bsize+j-1]) {
                        alist[aindex]=i*bsize+j-1; aindex++;
                }
                if(j<bsize-1 && color==bd[i*bsize+j+1]) {
        alist[aindex]=i*bsize+j+1; aindex++;
     }
   }

   num=bindex;
   while(bindex>0) { bd[blist[bindex-1]]=WQ_BLANK; bindex--; }
   return(num);
}
     

/* Function 'eat' returns the number of stones eaten by move
 (x,y), according to the data of bd[19][19] with move (x,y) set.
 eat modifies bd[19][19] by removing stones eaten. 
 eat also stores the position of the last stone eaten in
 *x_eat_ptr, * y_eat_ptr.
*/
 
int eat(int * bd, int x, int y, int * x_eat_ptr, int * y_eat_ptr)
{       
   int mycolor, opcolor;
   int num=0;

   mycolor=bd[x*bsize+y];
   if(mycolor==WQ_BLACK) opcolor=WQ_WHITE;
     else opcolor=WQ_BLACK;
   if(x>0 && bd[(x-1)*bsize+y]==opcolor && no_qi(bd,x-1,y) ) {
     num += remove_block(bd,x-1,y); 
     x_eat_ptr[0]=x-1; y_eat_ptr[0]=y;
   }
   if(x<bsize-1 && bd[(x+1)*bsize+y]==opcolor && no_qi(bd,x+1,y) ) {  
     num += remove_block(bd,x+1,y);
     x_eat_ptr[0]=x+1; y_eat_ptr[0]=y;
   }
   if(y>0 && bd[x*bsize+y-1]==opcolor && no_qi(bd,x,y-1) ) { 
     num += remove_block(bd,x,y-1);
     x_eat_ptr[0]=x; y_eat_ptr[0]=y-1;
   }
   if(y<bsize-1 && bd[x*bsize+y+1]==opcolor && no_qi(bd,x,y+1) ) {
     num += remove_block(bd,x,y+1);
     x_eat_ptr[0]=x; y_eat_ptr[0]=y+1;
   }

   return(num);
}



/* Function 'weiqi_rule' decides if the move (x,y) is legal under the
 weiqi rule. Return value 1(legal) or 0(illegal). */
 
int weiqi_rule(int x, int y)
{
   int i,j;
   int n;
   int *board = allocate(bsize*bsize);
   int *x_eat_ptr=allocate(1);
   int *y_eat_ptr=allocate(1);

   if(x<0 || x>=bsize || y<0 || y>=bsize) return 0;
     // This case is avoided by exact matching in 
     // translate_position().
        if(game[x*bsize+y] != WQ_BLANK) 
     return(WQ_POS_OCCUPIED);
   
   for(i=0;i<bsize;i++) for(j=0;j<bsize;j++) 
     board[i*bsize+j] = game[i*bsize+j];
   if(turn == "black") board[x*bsize+y] = WQ_BLACK;
     else board[x*bsize+y] = WQ_WHITE;
   n = eat(board,x,y,x_eat_ptr,y_eat_ptr);
   if(n>1) {
     for(i=0;i<bsize;i++) for(j=0;j<bsize;j++) 
        game[i*bsize+j] = board[i*bsize+j];
     jie_flag = WQ_NO_JIE;
     return 1;
   }
   else if(n==1) {
     if(jie_flag==WQ_JIE_POSSIBLE && x==jie_x_ban && y==jie_y_ban)
        return(WQ_JIE_BANNED);
     for(i=0;i<bsize;i++) for(j=0;j<bsize;j++) 
        game[i*bsize+j] = board[i*bsize+j];
     jie_flag = WQ_JIE_POSSIBLE;
     jie_x_ban = x_eat_ptr[0]; 
     jie_y_ban = y_eat_ptr[0];
     return 1;
   }
   else { // (n==0)
     if(no_qi(board,x,y)) 
        return(WQ_NO_QI_BANNED);
     game[x*bsize+y] = board[x*bsize+y];
     jie_flag = WQ_NO_JIE;
     return 1;
   }
}

int wuzi_rule(int x, int y)
{
   int i,j, color;
   int count;
   if(game[x*bsize+y] != WQ_BLANK)
     return(WQ_POS_OCCUPIED);
   if(turn == "black") game[x*bsize+y] = WQ_BLACK;
     else game[x*bsize+y] = WQ_WHITE;
   color=game[x*bsize+y];

   for(count=1,i=x+1,j=y+1; i>=0 && i<bsize && j>=0 && j<bsize &&
     color==game[i*bsize+j]; i++,j++,count++);
   for(i=x-1,j=y-1; i>=0 && i<bsize && j>=0 && j<bsize &&
     color==game[i*bsize+j]; i--,j--,count++);
   if(count>=5) return(WQ_WINNING);

        for(count=1,i=x-1,j=y+1; i>=0 && i<bsize && j>=0 && j<bsize &&
                color==game[i*bsize+j]; i--,j++,count++);
        for(i=x+1,j=y-1; i>=0 && i<bsize && j>=0 && j<bsize &&
                color==game[i*bsize+j]; i++,j--,count++);
        if(count>=5) return(WQ_WINNING);

        for(count=1,i=x+1,j=y; i>=0 && i<bsize && j>=0 && j<bsize &&
                color==game[i*bsize+j]; i++,count++);
        for(i=x-1,j=y; i>=0 && i<bsize && j>=0 && j<bsize &&
                color==game[i*bsize+j]; i--,count++);
        if(count>=5) return(WQ_WINNING);

        for(count=1,i=x,j=y+1; i>=0 && i<bsize && j>=0 && j<bsize &&
                color==game[i*bsize+j]; j++,count++);
        for(i=x,j=y-1; i>=0 && i<bsize && j>=0 && j<bsize &&
                color==game[i*bsize+j]; j--,count++);
        if(count>=5) return(WQ_WINNING);

   return(1);
}


int translate_position(string s, int *x_ptr, int *y_ptr)
{
   int i, match_flag=0;
   string sl,sn;

   if (strlen(s)>3 || strlen(s)<2) return 0;
   sl=s[0..0];
   for(i=0;i<bsize;i++) {
     if(sl==Ucase[i] || sl==lcase[i]) {
        x_ptr[0] = i;
        match_flag=1;
     }
   }
   if(!match_flag) return 0;
   match_flag = 0;
   sn=s[1..strlen(s)-1];
   for(i=0;i<bsize;i++) {
     if(sn==nindex[i]) {
        y_ptr[0] = i;
        match_flag=1;
     }
   }
   if(match_flag) return 1;
   else return 0;
}
   
int do_undo()
{
    int *x_ptr=allocate(1);
    int *y_ptr=allocate(1);
    object me = this_player();
    object rm = environment(me);
    object player;
    if(!me->query_temp("weiqi_seat"))
        return notify_fail("你是旁观者，怎么好意思瞎指挥？\n");
    if(status==WQ_NOT_PLAYING) 
        return notify_fail("还没新开一局棋呐。\n");
   if (status!=WQ_PLAYING_WUZI)
     return notify_fail("目前只提供五子棋的悔棋功能。\n");
   if(!WQ_Started)
     return notify_fail("一步都没走，悔什么棋。\n");
   if (me->query_temp("weiqi_seat")!= turn)
     return notify_fail("要悔棋也得跟人家商量一下呀。\n");
   if (WQ_Undoed)
     return notify_fail("一次只能悔一步棋。\n");

   WQ_Undoed=1;
   translate_position(lastmove,x_ptr,y_ptr);
   if (status==WQ_PLAYING_WUZI)
     {
        game[x_ptr[0]*bsize+y_ptr[0]]=WQ_BLANK;
        if (lastlastmove=="")
          {
             WQ_Started=0;
             lastmove="";   
          }
        else
          {
             lastmove=lastlastmove;
          }
     }
   else
     {
     }
   if (turn=="black") 
     {
        turn="white";
        if (lastmove!="")
          tell_room(rm,"\n黑棋上一步走在了"+lastmove+"\n");
     }
   else { 
     turn="black";
     if (lastmove!="")
        tell_room(rm,"\n白棋上一步走在了"+lastmove+"\n");
        }
    tell_room(rm,show_game());
    player = pl[turn];
    if(turn=="black")
       tell_room(rm,"现在轮到黑方"+player->name()+"走棋。\n");
    else tell_room(rm,"现在轮到白方"+player->name()+"走棋。\n");

   return 1;
}
        
int do_play(string arg)
{
   int *x_ptr=allocate(1);
   int *y_ptr=allocate(1);
   object me = this_player();
   object rm = environment(me);
   object op;
   int rv;
   int wf=0; // winning flag

   if(!me->query_temp("weiqi_seat"))
     return notify_fail("你是旁观者，怎么好意思瞎指挥？\n");
   if(status==WQ_NOT_PLAYING) 
     return notify_fail("还没新开一局棋呐。\n");
   if(me->query_temp("weiqi_seat") != turn)
     return notify_fail("还没轮到你走棋。\n");
   if(!translate_position(arg,x_ptr,y_ptr))
     return notify_fail("你要下在哪里？\n");

   if(status==WQ_PLAYING_WUZI) {
     rv = wuzi_rule(x_ptr[0],y_ptr[0]);
     if(rv==WQ_POS_OCCUPIED)
        return notify_fail("这个位置上已经有子了！\n");
     if(rv==WQ_WINNING) wf=1;
   }
    else {
     rv=weiqi_rule(x_ptr[0],y_ptr[0]);
     if(rv==WQ_POS_OCCUPIED)
        return notify_fail("这个位置上已经有子了！\n");
     if(rv==WQ_JIE_BANNED)
        return notify_fail("现在还没轮到你提劫！\n");
     if(rv==WQ_NO_QI_BANNED)
        return notify_fail("这个位置是禁入点！\n");
   }
   WQ_Started=1;
   WQ_Undoed=0;
   lastlastmove=lastmove;
   lastmove=arg;
   if (turn=="black") {
     tell_room(rm, "\n黑棋上一步走在了"+arg+"\n");
               }
   else
     tell_room(rm, "\n白棋上一步走在了"+arg+"\n");
   if(wf) {
     tell_room(rm,show_game());
     if(turn=="black") message_vision("黑方$N胜。\n",me);
      else message_vision("白方$N胜。\n",me);
     status=WQ_NOT_PLAYING;
     return 1;
   }
   if(turn=="black") { turn = "white"; op = pl["white"]; }
     else { turn = "black"; op = pl["black"]; }
   tell_room(rm,show_game());
   if(turn=="black") message_vision("现在轮到黑方$N走棋。\n",op);
    else message_vision("现在轮到白方$N走棋。\n",op);
   return 1;
}
