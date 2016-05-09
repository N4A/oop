#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n[][3] = {10,20,30,40,50,60};
    int (*p)[3];
    p = n;

    cout << *(p+1);

    return 0;
}
