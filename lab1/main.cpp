#include <iostream>
#include "Lab1.h"

using namespace std;

int main()
{
    Lab1 ob;
    for (int i = 0; i < 20; i++) {
        ob.generate(i);
    }
    return 0;
}
