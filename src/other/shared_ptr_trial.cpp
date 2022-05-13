//
// Created by chenlei on 2021/10/25.
//

#ifndef CPP_TRIAL_SHARED_PTR_TRIAL_H
#define CPP_TRIAL_SHARED_PTR_TRIAL_H

#include <iostream>
#include <memory>

using namespace std;

class Foo
{
public:
    Foo() { cout << "Foo()" << endl; }
    ~Foo() { cout << "~Foo()" << endl; }

    void print() {
        cout << "hello" << endl;
    }
};

static void test_shared_ptr() {
    shared_ptr<void> vptr = std::make_shared<Foo>();
    std::shared_ptr<Foo> ptr = static_pointer_cast<Foo>(vptr);
    ptr->print();
}

int main() {
    test_shared_ptr();
    return 0;
}

#endif //CPP_TRIAL_SHARED_PTR_TRIAL_H
