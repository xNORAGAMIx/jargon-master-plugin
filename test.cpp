#include <iostream>
#include <utility>

class Base {
public:
    virtual void show() {}
};

class Derived : public Base {
public:
    void show() {} // missing override
};

int main() {

    int x = 10;
    int y = (int)x; // C-style cast

    int *p = reinterpret_cast<int*>(&x); // reinterpret_cast

    return 0;
}