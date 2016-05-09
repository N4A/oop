#ifndef DATE_H
#define DATE_H
#include <string>
#include <strstream>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Date
{
    public:
        Date();
        Date(int year, int month, int day);
        Date(char* date_str);
        virtual ~Date();

        void pass_one_day ();
        int get_pass_days(Date* now);
        int get_year();
        int get_month();
        int get_day();
        string to_string();
    protected:
    private:
        int year;
        int month;
        int day;

        bool isLeap(int year);
        int dayInYear(int year, int month, int day);
};

#endif // DATE_H
