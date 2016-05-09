#include "Store.h"

Store::Store()
{
    cout << "The store is founded." << endl;
}

Store::~Store()
{
    cout << "The store is over." << endl;
}

void Store::add_commodity(Commodity* c)
{
    coms.insert(pair<string, Commodity*>(c->get_name(), c));
}

double Store::sell_commodity(string name)
{
    if (coms.count(name) > 0) {//right
        Commodity_it it = coms.find(name);
        double price_this = it->second->get_price();
        cout << "sell a " << it->second->get_name();
        cout << " at price " << price_this << endl;
        coms.erase(it);
        //delete it->second;
        return price_this;
    }
    else {
        return -1;//no such commodity
    }
}


double Store::sell_commodity(string name, double discount)
{
    if (coms.count(name) > 0) {//right
        Commodity_it it = coms.find(name);
        double price_this = it->second->get_price()*discount;
        cout << "sell a " << it->second->get_name();
        cout << " at price " << price_this;
        cout << ", discount:" << discount << endl;
        coms.erase(it);
        //delete it->second;
        return price_this;
    }
    else {
        return -1;//no such commodity
    }
}

void Store::add_commodities(char* file_path, Date* today) {
    char buf[256];//store every line

    //open file
    ifstream purchase(file_path);
    //check if it is successful
    if(!purchase) {
        cout << "Unable to open the file";
        exit(1); // terminate with error
    }
    //ignore the first line
    purchase.getline(buf,256);

    char name[20];
    char price[20];
    int life;
    char date[20];
    while (!purchase.eof()) {
        purchase.getline(buf,256);
        sscanf(buf, "%s %s %d %s", name, price, &life, date);
        //change to Date type
        Date* production_date = new Date(date);

        if (production_date->get_pass_days(today) < 0)//not produced yet
            continue;// skip this product

        //除了5月一号，以后每天只读当天产品
        if((today->get_day() != 1) && (production_date->get_pass_days(today) != 0)) {
            continue;
        }

        //build commodity
        Commodity* com = new Commodity(name, atof(price), production_date, life);
        //add to list
        add_commodity(com);
    }

}

double Store::sell_commodities(char* file_path) {
    double total_cost = 0;

    char buf[256];//store every line

    //open file
    ifstream sell(file_path);
    //check if it is successful
    if(!sell) {
        cout << "Unable to open the file";
        exit(1); // terminate with error
    }
    //ignore the first line
    sell.getline(buf, 256);

    char name_char[20];
    char discount[20];
    while (!sell.eof()) {
        sell.getline(buf, 256);
        sscanf(buf, "%s %s", name_char, discount);

        string name(name_char);

        //if has a discount
        bool has_discount = false;
        int len = sizeof(buf)/sizeof(buf[0]);
        for (int i = 0; i < len; i++) {
            if (*(buf+i) == '0'&&*(buf+i+1) == '.') {
                has_discount = true;
                break;
            }
        }



        double single_cost;//why when I 'write int single_cost',the complier won't report error
        if(has_discount) {
            single_cost = sell_commodity(name, atof(discount));
        }
        else {
            single_cost = sell_commodity(name);
        }

        if (single_cost <= 0) {
            cout << name << " is sold out." <<endl;
        }
        else {
            total_cost += single_cost;
        }
    }
    return total_cost;
}

void Store::open(Date* today)
{
    cout << "Today is ";
    cout << today->to_string();
    cout << ",The store opens" << endl;
}

void Store::close(Date* today)
{
    cout << "The store closes" << endl;
    int expired = rm_expired(today);
    cout << "today, " << expired << " commodities are expired" << endl;
}

int Store::rm_expired(Date* today)
{
    int expired = 0;
    for (Commodity_it it = coms.begin(); it != coms.end(); ++it) {
        Commodity * c = it->second;
        if (c->is_expired(today)) {
            delete it->second;
            coms.erase(it);
            --it;//what a fuck bug and what a stupid programmer who once forgot to add '--it'
            expired+=1;
        }
    }

    return expired;
}

void Store::show_commodities() {
    for (Commodity_it it = coms.begin(); it != coms.end(); ++it) {
        Commodity* c = it->second;

        cout << c->get_name() << "," << c->get_price() << "," << c->get_production_date()->to_string() << ",";
        cout << c->get_shelf_life() << endl;
    }
}
