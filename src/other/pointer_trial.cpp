//
// Created by chenlei on 2021/9/16.
//

#ifndef CPP_TRIAL_POINTER_H
#define CPP_TRIAL_POINTER_H

#include <iostream>
#include <cstdlib>


class AA {
public:
    AA() {
        d = new char[99];
    }

    ~AA() {
        delete d;
    }

    void fun() const {
        std::cout << "Hello, " << c << std::endl;
    }

private:
    // int a;
    // double b;
    std::string c;
    char *d;
    // char e;
};


void test_datatype() {
    // std::cout << "void: " << sizeof(void) << std::endl;
    std::cout << "void *: " << sizeof(void *) << std::endl;
    std::cout << "int *: " << sizeof(int *) << std::endl;
    std::cout << "float *: " << sizeof(float *) << std::endl;
    std::cout << 0x14 << std::endl;
    AA a;
    AA *b = new AA();
    std::cout << "A: " << sizeof(AA) << std::endl;
    std::cout << "a: " << sizeof(a) << std::endl;
    std::cout << "b: " << sizeof(b) << std::endl;
    std::cout << "char: " << sizeof(char) << std::endl;
    std::cout << "wchar_t: " << sizeof(wchar_t) << std::endl;
    std::cout << "short: " << sizeof(short) << std::endl;
    std::cout << "short int: " << sizeof(short int) << std::endl;
    std::cout << "int: " << sizeof(int) << std::endl;
    std::cout << "long int: " << sizeof(long int) << std::endl;
    std::cout << "long long: " << sizeof(long long) << std::endl;
    std::cout << "long long int: " << sizeof(long long int) << std::endl;
}

int main() {
    test_datatype();
    return 0;
}

#endif //CPP_TRIAL_POINTER_H
