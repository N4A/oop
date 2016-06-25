#include <fstream>
//#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

ofstream cout("result.txt");

class Item
{
public:
	//��Ʒ��
	string name;
	//��Ʒ�۸�
	double price;
	Item(string name_in, double price_in)
	{
		name = name_in;
		price = price_in;
	}
	~Item()
	{
		cout<<"Item "<<name<<" deleted"<<endl;
	}

	//TODO Part.1 ����==���������ж�������Ʒ�Ƿ�һ��
	const bool operator==(const Item& item){
	    return (name == item.name)&&(price == item.price);
	}
};
class Shelf
{
private:
	//�����ϵ�������Ʒ
	int size;
	//Item* items[10];
	vector<Item*> items;
	//���ÿ������캯��
	Shelf(Shelf& s){}
public:
	//���ܷ���
	string name;

	Shelf(string name_in)
	{
		size = 0;
		name = name_in;
	}
	~Shelf()
	{
		cout<<"Shelf "<<name<<" deleted"<<endl;
	}
	//��ȡ��Ʒ����
	int getItemSize()
	{
		return size;
	}
	//��ȡ��index����Ʒ
	Item* getItem(int index)
	{
		return items[index];
	}

    //�����Ʒ
	void clearAll() {
        items.clear();
        size = 0;
	}

	//TODO Part.1 ����+=������������������Ʒ
	void operator+=(Item* item) {
        items.push_back(item);
        size++;
	}

	//TODO Part.1 ����-=���������Ƴ����ܵ���Ʒ
	//���ܴ��ڸ���Ʒreturn true�� ���� return false
	const bool operator-=(Item* item) {
        for(int i = 0; i<size; i++) {
            if(items[i] == item) {
                items.erase(items.begin() + i);
                size--;
                return true;
            }
        }
        return false;
	}

	//TODO Part.1 ����<<����������һ�����ܵ���Ʒ���뵱ǰ����
	void operator<<(Shelf& s) {
        for(int i = 0; i < s.getItemSize(); i++) {
            (*this)+=(s.getItem(i));
        }
        s.clearAll();
	}
};
class Shop
{
private:
	//ÿ���̵�����������
	Shelf* shelf1;
	Shelf* shelf2;

    //deep copy s2 to s1
    void copyShelf(Shelf** s1, Shelf* s2) {
        (*s1) = new Shelf("");
		(*s1)->name = s2->name;
		int num = s2->getItemSize();
		for (int i = 0; i<num; i++) {
            Item* tp = s2->getItem(i);
            Item* item = new Item(tp->name,tp->price);
            (**s1) += item;
		}
    }

public:
	//�̵�����
	string name;
	Shop(string name_in, Shelf* s1, Shelf* s2)
	{
		name = name_in;
		shelf1 = s1;
		shelf2 = s2;
	}
	~Shop()
	{
		cout<<"Shop "<<name<<" deleted"<<endl;
	}
	Shop(Shop& s)
	{
		//TODO Part.2 ʵ��Shop��Ŀ������캯��
		name = s.name;
        copyShelf(&shelf1,s.getShelf1());
        copyShelf(&shelf2,s.getShelf2());
	}
	Shelf* getShelf1()
	{
		return shelf1;
	}
	Shelf* getShelf2()
	{
		return shelf2;
	}
};

//for test
void printShelf(Shelf& shelf) {
    int max = shelf.getItemSize();
    cout << shelf.name << ":[";
    for (int i = 0; i < max; i++) {
        cout  << shelf.getItem(i)->name << ",";
    }
    cout << "]" << endl;
}

//for test print shop
void printShop(Shop& s) {
    cout << s.name << ":{" << endl;
    printShelf(*s.getShelf1());
    printShelf(*s.getShelf2());
    cout << "}" << endl;
}

int main()
{
	//TODO ��д��������

	//test Item ==
	cout << "test Item ==" << endl;
	Item i1("apple",1);
	Item i2("apple",2);
	Item i3("banana",1);
	Item i4("apple",1);
	cout << "i1(apple,1)==i2(apple,2):" << (i1==i2) << endl;
	cout << "i1(apple,1)==i3(banana,1):" << (i1==i3) << endl;
	cout << "i1(apple,1)==i4(apple,1):" << (i1==i4) << endl;
	cout << endl;

	//test shelf +=
	Shelf shelf1("shelf1");
	cout << "test Shelf +=" << endl;
	cout << "add i1(apple)" << endl;
    shelf1+=&i1;
    cout << "add i2(apple)" << endl;
    shelf1+=&i2;
    cout << "add i3(banana)" << endl;
    shelf1+=&i3;
    printShelf(shelf1);
    cout << endl;

    // test shelf -=
    cout << "test Shelf -=" << endl;
    cout << "remove i3(banana)" << endl;
    shelf1-=&i3;
    printShelf(shelf1);
    cout << endl;

    //test shelf <<
    cout << "test Shelf <<" << endl;
    Shelf shelf2("shelf2");
    printShelf(shelf2);
    cout << "shelf2 << shelf1" << endl;
    shelf2 << shelf1;
    printShelf(shelf1);
    printShelf(shelf2);
    cout << endl;

    //test Shop copy constructor
    cout << "test Shop copy constructor" << endl;
    Shop shop1("shop1", &shelf1, &shelf2);
    cout << "shop2 = shop1" << endl;
    Shop shop2 = shop1;
    printShop(shop1);
    printShop(shop2);
    cout << "shop2 shelf2 remove i2(apple)" << endl;
    (*shop2.getShelf2())-=&i2;
    cout << "rename shop2 shelf2 item[0]" << endl;
    shop2.getShelf2()->getItem(0)->name += "_renamed";
    cout << "shop2 change name to shop2" << endl;
    shop2.name = "shop2";
    printShop(shop1);
    printShop(shop2);

    cout << endl;
}
