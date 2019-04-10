// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// npc.c
// savable NPC.
// mon 1/21/98

// How to write a savable NPC?
// 1. inherit NPC_SAVE
// 2. at the begin of create() function, put in the following:
//
//    reload("filename");
//
//          you should change "filename" to whatever string
//          which will be used as the file name to be saved
//          for this NPC, it doesn't have to be the same as
//          the filename of this npc(the .c filename).
// 3. reload() will read the saved .o file for this NPC.
//    if no .o file, then the NPC data will be unchanged.
//    you can also set other properties of the NPC after
//    the reload() function.
// 4. NPC data will be saved in /data/npc/ dir.
// 5. If need reset certain parameters, it maybe necessary
//    to remove the .o file by hand before update the NPC
//    file because it will restore from the .o filr automatically.
//    

#include <origin.h>
#include <user.h>

inherit NPC;
inherit F_AUTOLOAD;
inherit F_SAVE;

private string SAVE_NAME="npc_save";
private static int can_save=1;
//default setting

string query_save_name() {return SAVE_NAME;}

//restore saved data.
//savename is the file name to be saved for this object.
void reload(string savename)
{
      if(clonep()) {
        if(sizeof(filter_array(children(base_name(this_object())), 
          (:clonep:)))>1) {
            can_save=0;
       call_out("self_destroy",1);
       return;
   }
      }

   if(clonep() && savename && can_save) { 
   // only cloned obj can save and restore.
     SAVE_NAME=savename;
     if(!restore())
       log_file("npc_save",sprintf("Failed to restore %s(%s).\n",
         this_object()->query("id"),savename));
   }   
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
   string id;

   id = SAVE_NAME;
   if( !stringp(id) ) return 0;
   return sprintf(DATA_DIR "npc/%c/%s", id[0], id);
}

int save()
{
   int res;
   string file=query_save_file();
   string dir=DATA_DIR "npc/";
   int len=strlen(dir);
   
   if(!file || strlen(file)<=len) return 0;
   // can only save to DATA_DIR "npc/" dir.
   if(file[0..(len-1)]!=dir) return 0;

        if(clonep() && can_save) {
     save_autoload();
     res = ::save();
     clean_up_autoload();     // To save memory
     return res;
   } else
     return 0;  
}

void setup()
{
      ::setup();
      restore_autoload();
}

// create() is actually no use since all NPC has their own create().
void create()
{
     set_name("非使用者物件", ({ "npc object", "npc", "object" }) );
}

void self_destroy()
{
    if(this_object())
   destruct(this_object());
}

