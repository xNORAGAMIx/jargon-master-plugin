#include <iostream>
#include <utility>

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

    foo(); // return ignored
    int x; // unused variable

    int y = 5;
    y; // unused expression

    try {
        throw std::runtime_error("error");
    } catch (std::exception e) { // catch by value
    }

    Derived d;
    d.display();

    int *p = new int(5); // memory rule

    if (p != nullptr) { // unnecessary check
        delete p;
    }

    std::string s = "hello";
    std::string t = std::move(s); // moved-from usage

    return 0;
}