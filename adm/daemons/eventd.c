// eventd.c
// 自然奇观系统主程序
// for XKX100 , by Sir 2003.11.3

#include <dbase.h>
#include <ansi.h>
#include <localtime.h>
int start;

// 待触发的事件
// 登记在某个绝对的时间启动事件
// 设定的参数是零或负数
// 比如：month = 0  day = 0   hour = -5    表示实际时间每天早上5点钟
//	 month = -8 day = -15 hour = -5    表示实际时间每年8月15的5点钟
mapping *event_list = ({
    (["month":0, "day":0, "hour":-7, "ename":"emei.c", "cname":"峨嵋金顶日出"]),         //早上7点
    (["month":0, "day":-15, "hour":-23, "ename":"wuliang.c", "cname":"无量山玉壁剑舞"]), //每月15日晚11点
    (["month":0, "day":0, "hour":-22, "ename":"tianchi.c", "cname":"长白山天池流星"]),   //每晚10点
    (["month":-8, "day":-15, "hour":-10, "ename":"qiantang.c", "cname":"钱塘江潮信"]),   //每年8月15日10点
    (["month":0, "day":0, "hour":-17, "ename":"hspb.c", "cname":"衡山水帘洞瀑布"]),      //每日下午5点
});

void create()
{
        int i;
        seteuid(ROOT_UID);

        message("channel:sys", HIR "【自然奇观】自然奇观已经启动。\n" NOR, users());
        message("channel:sys", HIR "【自然奇观】系统已登记的自然奇观如下:\n" NOR, users());

        for (i = 0; i < sizeof(event_list); i++)
        {
                message("channel:sys", HIR "【自然奇观】" + event_list[i]["cname"] + "。\n" NOR, users());
        }

        set_heart_beat(30); // 每分钟心跳一次
}

// 每分钟心跳一次，1,10时检查所有的事件
void heart_beat()
{
        mixed *lt;
        object eob;
        int tt, i, num;
        int month, day, hour;
        string time;

        lt = localtime(time());
        num = 0;

        if (start == 59)
        {
                start = 0;
        }
        else
                start = start + 1;

        time = "";

        time = chinese_number(start);

        //        message("channel:sys",HIR"【自然奇观】 这个时间段内心跳"+time+"次\n"NOR, users());

        if (start == 1 || start == 10)
        {

                for (i = 0; i < sizeof(event_list); i++)
                {
                        month = event_list[i]["month"];
                        day = event_list[i]["day"];
                        hour = event_list[i]["hour"];

                        if (month < 0)
                                month = -month - 1;
                        else
                                month += lt[LT_MON];
                        if (day < 0)
                                day = -day;
                        else
                                day += lt[LT_MDAY];
                        if (hour < 0)
                                hour = -hour;
                        else
                                hour += lt[LT_HOUR];
                        if (month == lt[LT_MON] && day == lt[LT_MDAY] && hour == lt[LT_HOUR])
                        {
                                if (start == 1)
                                        message("channel:rumor", HIM "【谣言】" + "听说" + event_list[i]["cname"] + "蔚为奇观，不少江湖人士纷纷前往观赏。\n" NOR, users());
                                else
                                {
                                        eob = new (EVENT_DIR + event_list[i]["ename"]);
                                        destruct(eob);
                                }
                        }
                        else
                                continue;
                }
        }
}
