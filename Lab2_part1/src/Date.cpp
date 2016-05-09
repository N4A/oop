#include "Date.h"

Date::Date()
{

}

Date::Date(int year, int month, int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

Date::Date(char* date_str)
{
    string s = "";

    //get year
    while(*date_str != '/') {
        s += *date_str;
        date_str++;
    }
    this->year = atoi(s.c_str());

    //get month
    s = "";
    date_str++;//ignore /
    while(*date_str != '/') {
        s += *date_str;
        date_str++;
    }
    this->month = atoi(s.c_str());

    //get day
    date_str++;//ignore /
    this->day = atoi(date_str);

    //cout << this->year << "/" << this->month << "/" << this->day << endl;//test
}

Date::~Date()
{
    //dtor
}

void Date::pass_one_day()
{
    day += 1;
    if (day > 31 && (month == 1||month == 3||month==5||month==7||month == 8||month == 10||month == 12))
    {
        month += 1;
        day %= 31;
    }
    if (day > 30 && (month == 4||month == 6||month == 9||month ==11))
    {
        month += 1;
        day %= 30;
    }
    if (day > 29 && month == 2 && (isLeap(year)))
    {

        month += 1;
        day %= 29;
    }
    if (day > 28 && month == 2 && !(isLeap(year)))
    {
        month += 1;
        day %= 28;
    }

    if (month > 12) {
        month %= 12;
        year += 1;
    }
}

int Date::get_pass_days(Date* now)
{
    if(this->year == now->year && this->month == now->month) {
        return now->day - this->day;

    //如果年相同
    }else if(this->year == now->year) {
        int d1, d2;
        d1 = dayInYear(this->year, this->month, this->day);
        d2 = dayInYear(now->year, now->month, now->day);
        return d2 - d1;

    //年月都不相同
    }else{
        //确保this->year年份比now->year早
        if(this->year > now->year)
        {
            return -1;
        }
        int d1,d2,d3;
        if(isLeap(this->year))
            d1 = 366 - dayInYear(this->year,this->month, this->day); //取得这个日期在该年还于下多少天
        else
            d1 = 365 - dayInYear(this->year,this->month, this->day);
            d2 = dayInYear(now->year,now->month,now->day); //取得在当年中的第几天
        cout<<"d1:"<<d1<<", d2:"<<d2;

        d3 = 0;
        for(int year = this->year + 1; year < now->year; year++) {
            if(isLeap(year))
                d3 += 366;
            else
                d3 += 365;
        }
        return d1 + d2 + d3;
    }
}

int Date::get_year()
{
    return this->year;
}
int Date::get_month()
{
    return this->month;
}
int Date::get_day()
{
    return this->day;
}
string Date::to_string() {
    string s = "";
    string s_temp;
    strstream ss_year;
    strstream ss_month;
    strstream ss_day;

    //add year
    ss_year << this->year;
    ss_year >> s_temp;
    s += s_temp;
    s += "/";

    //add month
    ss_month << this->month;//
    ss_month >> s_temp;
    s += s_temp;
    s += "/";

    //add day
    ss_day << this->day;
    ss_day >> s_temp;
    s += s_temp;

    return s;
}


//isLeap函数判断一个年份是否为闰年，方法如下:
bool Date::isLeap(int year)
{
    return (year % 4 ==0 || year % 400 ==0) && (year % 100 !=0);
}


//dayInYear能根据给定的日期，求出它在该年的第几天，代码如下
int Date::dayInYear(int year, int month, int day)
{
    //int _day = 0;
    int DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(isLeap(year))
    DAY[1] = 29;
    for(int i=0; i<month - 1; ++i) {
        day += DAY[i];
    }
    return day;
}


