#include "Commodity.h"
#include <iostream>

using namespace std;

Commodity::Commodity()
{
    //ctor
}

Commodity::Commodity(string name, double price, Date* production_date, int shelf_life)
{
    this->name = name;
    this->price = price;
    this->production_date = production_date;
    this->shelf_life = shelf_life;
}

Commodity::~Commodity()
{
    cout << this->name << " is dropped" << endl;
}

bool Commodity::is_expired(Date* now)
{
    int pass_days = production_date->get_pass_days(now) + 1;//今天已经结束了，所以加一天
    if (pass_days >= this->shelf_life){
        return true;
    }
    else {
        return false;
    }
}

string Commodity::get_name()
{
    return this->name;
}

double Commodity::get_price()
{
    return this->price;
}

int Commodity::get_shelf_life()
{
    return this->shelf_life;
}

Date* Commodity::get_production_date()
{
    return this->production_date;
}
