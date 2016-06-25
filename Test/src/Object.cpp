#include "Object.h"

Object::Object()
{
    //ctor
    std::cout << "hello" << std::endl;
}

Object::~Object()
{
    //dtor
}

int Object::getInt() {
    return i;
}
