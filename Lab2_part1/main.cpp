#include <iostream>
#include "Store.h"
#include "Commodity.h"
#include "Date.h"
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;


int main()
{
    Date today(2014,5,1);
    Store store;//build store;
    char sell[5][10] = {"sell0.txt","sell1.txt","sell2.txt","sell3.txt","sell4.txt"};

    for (int i = 0; i < 5; i ++) {
        //prepare commodities, 因为只有一个文件，所以规则为
        //5月1会将此前所有产品都读进来，以后每天只读当天产品
        store.add_commodities("purchase.txt", &today);

        //open store
        store.open(&today);

        cout << "show commidities:" << endl;
        store.show_commodities();//for checking error;

        //sell, 每天都会被要求卖文件中的东西
        cout << "prepared to sell commodities:" << endl;
        cout << sell[i] << endl;
        cout << "total cost: " << store.sell_commodities(sell[i])<< endl;

        //close
        cout << "close store and expired-checking:" << endl;
        store.close(&today);

        today.pass_one_day();//a day pass
    }

    //避免直接退出
    string ww;
    cin >> ww;

    return 0;
}
