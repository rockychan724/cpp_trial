#include <iostream>

class Base2 {
public:
    int m_a;
public:
    explicit Base2(int a) : m_a(a) {
        std::cout << "Base obj constructed !" << std::endl;
    }
};

class Derived : public Base2 {
public:
    int m_b;
    int m_c;
    int m_d;
public:
    Derived(int a, int c) : m_c(c), m_b(m_a + m_c), Base2(a) {
        std::cout << "m_b = " << m_b << std::endl;
        std::cout << "Derived obj constructed !" << std::endl;
    }
};

// 得放到linux系统下运行
int main1() {
    Derived d(1, 10);
    std::cout << d.m_a << std::endl; // 1
    std::cout << d.m_b << std::endl; // 未初始化
    std::cout << d.m_c << std::endl; // 10
    std::cout << d.m_d << std::endl; // 1
    return 0;
}

#include<bits/stdc++.h>

using namespace std;

class A {
public:
    virtual void fun() { cout << "A"; }

};

class B : public A {
public:
    void fun() { cout << "B"; }

    void fun2() {
        cout << "B2";
    }
};

class C : public B {
public:
    void fun() { cout << "C"; }

    virtual void test() {

    }
};

class Person {
public:
    int _age;
    int &sex;

    Person(int age) : _age(age), sex(_age) {
        cout << "Construct a person." << _age << endl;
    }

    Person(const Person &p) : _age(p._age), sex(_age) {
        cout << "Copy-Construct" << _age << endl;
    }

    Person(const Person &&p) noexcept: _age(p._age), sex(_age) {
        cout << "Move-Construct" << _age << endl;
    }
};

class Foo {
public:
    int v;

    Foo() {
        v = 2;
    }
};

class Bar {
public:
    Bar() {
        b = 1;
    }

    int b;
    Foo foo;
};

int main6() {
    A *a = new C();
    a->fun();//输出B，A类中的fun在B类中重写
    // A aa; // error
    B *b = new C();
    b->fun();
    b->fun2();

    using namespace std;
    vector<Person> person;
    auto p = Person(1); // >: Construct a person.1
    person.emplace_back(move(p)); // >: Move-Construct1
    person.emplace_back(2);
    std::cout << p._age << std::endl;
    int d = 10, e = 9;
    const int &c = 0;
    std::cout << sizeof(b) << std::endl;
    Bar bar;
    std::cout << bar.foo.v << std::endl;
    return 0;
}

class BB;

class AA {
public:
    shared_ptr<BB> pb_;

    ~AA() {
        cout << "AA delete\n";
    }
};

class BB {
public:
    shared_ptr<AA> pa_;

    ~BB() {
        cout << "BB delete\n";
    }
};

void fun() {
    shared_ptr<BB> pb(new BB());
    shared_ptr<AA> pa(new AA());
    pb->pa_ = pa;
    pa->pb_ = pb;
    cout << pb.use_count() << endl;
    cout << pa.use_count() << endl;
}

int main5() {
    // fun();
    const char *s = "abc";
    std::cout << s << std::endl;
    return 0;
}

// #include <iostream>
//
// using namespace std;
//
// class A {
// public:
//     int x;
//
//     A(int x) : x(x) {
//         cout << "Constructor" << endl;
//     }
//
//     A(A &a) : x(a.x) {
//         cout << "Copy Constructor" << endl;
//     }
//
//     A &operator=(A &a) {
//         x = a.x;
//         cout << "Copy Assignment operator" << endl;
//         return *this;
//     }
//
//     A(A &&a) : x(a.x) {
//         cout << "Move Constructor" << endl;
//     }
//
//     A &operator=(A &&a) {
//         x = a.x;
//         cout << "Move Assignment operator" << endl;
//         return *this;
//     }
// };
//
// A GetA() {
//     return A(1);
// }
//
// A &&MoveA(A &a) {
//     return std::move(a);
// }
//
// int main2() {
//     cout << "-------------------------1-------------------------" << endl;
//     A a(1);
//     cout << "-------------------------2-------------------------" << endl;
//     A b = a;
//     cout << "-------------------------3-------------------------" << endl;
//     A c(a);
//     cout << "-------------------------4-------------------------" << endl;
//     b = a;
//     cout << "-------------------------5-------------------------" << endl;
//     A d = A(1);
//     cout << "-------------------------6-------------------------" << endl;
//     A e = std::move(a);
//     cout << "-------------------------7-------------------------" << endl;
//     A f = GetA();
//     cout << "-------------------------8-------------------------" << endl;
//     A &&g = MoveA(f);
//     cout << "-------------------------9-------------------------" << endl;
//     d = A(1);
//     return 0;
// }
//
// class Test {
// public:
//     Test(int _a) : a(_a) {}
//
//     int a = 1;
// };
//
// int main() {
//     Test a(1);
//     Test b = a;
//     b.a = 2;
//     Test c(b);
//     std::cout << a.a << ", " << b.a << ", " << c.a << std::endl;
//     return 0;
// }

class AAA {
public:
    AAA() {
        std::cout << "A" << std::endl;
    }

    ~AAA() {
        std::cout << "~A" << std::endl;
    }

    void print() {
        std::cout << "AAA" << std::endl;
    }

    virtual void test() {
        std::cout << "TEST" << std::endl;
    }

    virtual void test1() {
        std::cout << "TEST" << std::endl;
    }

    virtual void test2() {
        std::cout << "TEST" << std::endl;
    }

// private:
    char b;
    int a;
    char c;
};


int main() {
    // std::vector<std::string> a;
    // a.push_back("100000");
    // // a.resize(1);
    // std::cout << a.size() << "," << a.capacity() << std::endl;
    // std::cout << a[100] << std::endl;
    // a[100] = "1000000";
    // std::cout << a[100] << std::endl;
    char a[] = "Hello";
    char *p = a;
    std::cout << sizeof(p) << "," << strlen(p) << "," << sizeof(a) << std::endl;

    AAA aa[5];
    AAA bb;
    std::cout << sizeof(aa) << "," << sizeof(bb) << std::endl;
    std::cout << &bb << "," << (void *)&(bb.b) << "," << &(bb.a) << ", " << (void *)&(bb.c) << std::endl;

    union un {
        char a;
        short b;
    };
    un u;
    u.b = 0xff00;
    if (u.a == 0xff) {
        cout << "big" << endl;
    } else {
        cout << "small" << endl;
    }

    int i = 0;
    long li = 0;
    long long ll = 0;
    std::cout << sizeof(i) << "," << sizeof(li) << "," << sizeof(ll) << std::endl;

    bool boo;
    std::cout << sizeof(boo) << std::endl;

    std::string s("abcd");
    std::cout << "size:" << s.size() << ",length:" << s.length() << std::endl;
    std::string s1;
    std::cout << sizeof(s1) << std::endl;
    std::cout << sizeof(s) << std::endl;
    std::cout << sizeof("abcd") << std::endl;
    return 0;
}

