#include "iostream"
#include "lab3.h"
using namespace std;

#define PRODUCT (a*b)

int main(){
#ifdef LAB3_H
	a = 3;
	b = 5;
	int s = sum(a, b);
	int p = PRODUCT;

#endif

#define DEBUG

#ifdef DEBUG
	cout<<"DEBUG 1 !"<<endl;
#undef DEBUG
#endif

#ifdef DEBUG
	cout<<"DEBUG 2 !"<<endl;
#endif

#if 0
	cout<<"if 0 !"<<endl;
#endif

#if 1
	cout<<"if 1 !"<<endl;
#endif

	cout<<"s:"<<s<<",p:"<<p<<endl;
	return 0;
}

