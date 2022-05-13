#include <iostream>
#include <stdexcept>

class A {
public:
    A() {
        std::cout << "Construct.\n";
    }

    ~A() {
        std::cout << "Destruct.\n";
    }
};

int div_(int a, int b) {
    A ss;
    if (b == 0) {
        throw std::runtime_error("b can't be 0");
    }
    return a / b;
}

int main() {
    int a, b;
    std::cout << "Please input a and b:";
    std::cin >> a >> b;
    try {
        std::cout << div_(a, b) << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    std::cout << "Over!\n";
    return 0;
}
