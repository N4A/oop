#ifndef STORE_H
#define STORE_H
#include <map>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "Commodity.h"
#include "Date.h"

using namespace std;

typedef multimap<string, Commodity*>::iterator Commodity_it;
typedef pair<Commodity_it, Commodity_it> Commodity_pair;


class Store
{
    public:
        Store();
        ~Store();
        void open(Date* today);
        void close(Date* today);
        void add_commodities(char* file_path, Date* today);
        double sell_commodity(string name);
        double sell_commodity(string name, double discount);
        double sell_commodities(char* file_path);

        void show_commodities();//for checking error

    protected:
    private:
        multimap<string, Commodity*> coms;

        void add_commodity(Commodity* c);
        int rm_expired(Date* today);
};

#endif // STORE_H
