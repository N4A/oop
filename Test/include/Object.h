#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>

class Object
{
    public:
        Object();
        virtual ~Object();
        int getInt();
    protected:
    private:
        int i = 0;
};

#endif // OBJECT_H
