#include <iostream>

int foo() { return 10; }

class Base {
public:
    void display() {}
};

class Derived : public Base {
public:
    void display() {} // name hiding
};

void f(int x) {} // unused param

int main() {

    foo(); // HSCAA_1_2
    int x; // HSCAA_2_1

    int y = 5; // unused variable
    y; // unused expression (HSCAA_2_4)

    try {
        throw std::runtime_error("error");
    } catch (std::exception e) { // HSCAS_1_1
    }

    Derived d;
    d.display();

    return 0;
}