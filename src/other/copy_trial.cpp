#include <iostream>

class A {
public:
    A() {}

    A(const A &a) {
        std::cout << "A: Copy construct" << std::endl;
    }

    // A(const A &a) = delete;
};

class B {
public:
    B() {}

    B(const B &b) : a(b.a) {
        std::cout << "B: Copy construct" << std::endl;
    }

private:
    A a;
};

int main() {
    B b1;
    B b2 = b1;
    return 0;
}
