#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int a = 1;
    int *ap = &a;
    int &ar = a;
    ar = a++;
    cout << &a << endl;
    cout << &ap << endl;
    cout << ar << endl;
    return 0;
}
