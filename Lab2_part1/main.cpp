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
        //prepare commodities, ��Ϊֻ��һ���ļ������Թ���Ϊ
        //5��1�Ὣ��ǰ���в�Ʒ�����������Ժ�ÿ��ֻ�������Ʒ
        store.add_commodities("purchase.txt", &today);

        //open store
        store.open(&today);

        cout << "show commidities:" << endl;
        store.show_commodities();//for checking error;

        //sell, ÿ�춼�ᱻҪ�����ļ��еĶ���
        cout << "prepared to sell commodities:" << endl;
        cout << sell[i] << endl;
        cout << "total cost: " << store.sell_commodities(sell[i])<< endl;

        //close
        cout << "close store and expired-checking:" << endl;
        store.close(&today);

        today.pass_one_day();//a day pass
    }

    //����ֱ���˳�
    string ww;
    cin >> ww;

    return 0;
}
