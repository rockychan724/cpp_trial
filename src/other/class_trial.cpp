//
// Created by chenlei on 2021/9/25.
//

#ifndef CPP_TRIAL_CLASS_TRIAL_H
#define CPP_TRIAL_CLASS_TRIAL_H

#include <iostream>

using namespace std;

class Base {
public:
    Base() {
        cout << "The constructor of Base" << endl;
    }
};

class VBase {
public:
    VBase() {
        cout << "The constructor of VBase" << endl;
    }
};

class VBase_ {
public:
    VBase_() {
        cout << "The constructor of VBase_" << endl;
    }
};

/* 普通继承与虚继承 */
class A : public Base, virtual public VBase_, virtual public VBase {
public:
    A() {
        cout << "The constructor of A" << endl;
    }
};

class B {
public:
    B() {
        cout << "The constructor of B" << endl;
    }
};

class D {
public:
    D() {
        cout << "The constructor of D" << endl;
    }
};

class C : public B, public A {
public:
    C() {
        cout << "The constructor of C" << endl;
    }

private:
    /* 对象成员 */
    D obj;
};

void test_class_inherit() {
    /* 实例化类 C */
    C test = C();
}

int main() {
    test_class_inherit();
    return 0;
}

#endif //CPP_TRIAL_CLASS_TRIAL_H
