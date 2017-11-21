#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;
void main11() {
    /**
     * 构造函数建立一个日期
     */
    date d1(2017, 11, 11);
    date d2(2017, Nov, 21);
    date d3 = from_string("2017-11-1");
    date d4 = from_string("2017/11/2");
    date d5 = from_undelimited_string("20171101");

    //获取现在的时间
    cout << "本地日期:" << day_clock::local_day() << endl
         << "UTC时间:" << day_clock::universal_day() << endl;

    //获取一个日期的年月日
    cout << "对于2017-11-1：" << endl
         << "年：" << d1.year() << endl
         << "月：" << d1.month() << endl
         << "日：" << d1.day() << endl;

    cout << "对于2017-11-21：" << endl
         << "星期数：（0表示星期天）" << d2.day_of_week() << endl
         << "当年的第几天：" << d2.day_of_year() << endl
         << "当年的第几周：" << d2.week_number() << endl
         << "当月的最后一天：" << d2.end_of_month() << endl << endl;

    cout << "对于2003-11-01：" << endl
         << "直接打印日期：" << d3 << endl
         << "使用to_simple_string打印日期：" << to_simple_string(d3) << endl
         << "使用to_iso_string打印日期：" << to_iso_string(d3) << endl
         << "使用to_iso_extended_string打印日期：" << to_iso_extended_string(d3) << endl << endl;
}

/**
 * date_suration类
 * date_duration表示日期长度，是以天为单位的时长，值可以是任意的整数，可正可负。
 * date_time库为date_duration定义了一个常用的typedef: days。此外，
 * date_time库还提供了months、years、weeks等另外三个时长类，
 * 分别用来表示月，年和星期，它们的含义与days类型，但行为不太相同。
 */
void main12(){
    days dd1(10), dd2(-5);
    cout << "dd1 + dd2 = " << (dd1 + dd2).days() << endl;
    weeks w(3);
    cout << "3个星期的天数：" << w.days() << endl;
    months m(5);
    years y(3);
    months m2 = y + m;
    cout << "3年5个月的月数：" << m2.number_of_months() << endl << endl;

    date d1(2001, 1, 1);
    date d2(2002, 1, 1);
    cout << "d2 - d1 = " << d2 - d1 << endl;
    d1 += days(10);
    cout << "d1 + days(10)后：" << d1 << endl;
    d1 += months(2);
    cout << "d1 + months(2)后：" << d1 << endl;
    d1 -= weeks(1);
    cout << "d1 - weeks(1)后：" << d1 << endl;
    d1 -= years(10);
    cout << "d1 - years(10)后：" << d1 << endl;
}
/**
 * time_duration类
 与date_duration类似，date_time库使用time_duration度量时间长度。
 time_duration有几个子类，可以度量不同的时间分辨率，
 它们分别是：hours、minutes、seconds、millisec/millisecnods、microsec/microseconds
 和nanosec/nanoseconds。
 */
void main13(){
    /* 1小时10分钟30秒1毫秒 */
    time_duration td1 = duration_from_string("1:10:30:001");
    cout << "td1: " << td1 << endl;

    /* 子类 */
    hours h(1);
    minutes m(10);
    seconds s(30);
    millisec ms(1);
    time_duration td2 = h + m + s + ms;
    cout << "td2: " << td2 << endl
         << "hours: " << td2.hours() << endl
         << "minutes: " << td2.minutes() << endl
         << "total_seconds: " << td2.total_seconds() << endl
         << "total_milliseconds: " << td2.total_milliseconds() << endl;

    /* 字符串表示 */
    cout << "to_simple_string: " << to_simple_string(td2) << endl;    //01:10:30.001000
    cout << "to_iso_string: " << to_iso_string(td2) << endl;       //011030.001000
}
/**
 * ptime类
 * ptime类表示时间点，它相当于一个日期再加上一个小于一天的时间长度。
 */
void main14(){
    ptime p1(date(2017,11,1),hours(16));
    ptime p2=time_from_string("2017-11-1 16:00:00");
    ptime p3 = from_iso_string("20030303T030000");      //日期与时间用字母T隔开
    ptime p4 = second_clock::local_time();              //本地当前时间，秒精度
    ptime p5 = microsec_clock::universal_time();        //UTC当前时间，微秒精度
    cout << p1 << endl
         << p2 << endl
         << p3 << endl
         << p4 << endl
         << p5 << endl << endl;
/*
     * date()获得时间点中的日期
     * time_of_day()获得时间长度
     */
    date d = p1.date();
    time_duration td = p1.time_of_day();
    cout << d << ", " << td << endl << endl;

    cout << to_simple_string(p2) << endl            //转换为YYYY-mmm-DD HH:MM:SS.ffffff
         << to_iso_string(p2) << endl               //转换为YYYYMMDDTHHMMSS,ffffff
         << to_iso_extended_string(p2) << endl;     //转换为YYYY-MM-DDTHH:MM:SS,ffffff
}
int main_test1() {
    main14();
    return 0;
}