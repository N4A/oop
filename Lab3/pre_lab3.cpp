#include "iostream"
int a;
int b;
int sum(int arg1, int arg2){
	return arg1 + arg2;
}

using namespace std;


int main(){
	a = 3;
	b = 5;
	int s = sum(a, b);
	int p = (a*b);



	cout<<"DEBUG 1 !"<<endl;



	cout<<"if 1 !"<<endl;

	cout<<"s:"<<s<<",p:"<<p<<endl;
	return 0;
}


