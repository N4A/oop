#ifndef COMMODITY_H
#define COMMODITY_H
#include "Date.h"
#include <string>

using namespace std;

class Commodity
{
    public:
        Commodity();
        Commodity(string name, double price, Date* production_date, int shelf_life);
        ~Commodity();

        bool is_expired(Date* now);
        string get_name();
        double get_price();
        int get_shelf_life();
        Date* get_production_date();
    protected:
    private:
        string name;
        double price;
        Date* production_date;
        int shelf_life;
};

#endif // COMMODITY_H
