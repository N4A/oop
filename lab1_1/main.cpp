#include <iostream>
using namespace std;

int main()
{
    int a = 1;
    int &ar = a;
    int *ap = &a;

    ar = 2;
    *ap = 3;

    bool c = (&ar==&a);
    bool d = (ap==&a);

    cout << &a << "," << &ar << "," << &ap << endl;

    return 0;
}
