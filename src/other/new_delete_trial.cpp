#include <iostream>

using namespace std;

class A1 {
public:
    int operator=(int a) {
        return 8;
    }

    int operator+(int a) {
        return 9;
    }

    void *operator new(size_t sz) {
        cout << "Widget::new: " << sz << "bytes" << endl;
        return ::new char[sz];
    }

    void operator delete(void *p) {
        cout << "Widget::delete " << endl;
        ::delete[]p;
    }

    void *operator new[](size_t sz) {
        cout << "Widget::new[]: " << sz << "bytes" << endl;
        return ::new char[sz];
    }

    void operator delete[](void *p) {
        cout << "Widget::delete[] " << endl;
        ::delete[]p;
    }
};

class B1 : public A1 {
public:
    int operator-(int a) {
        return 7;
    }
};

int main() {
    B1 v;
    cout << (v + 2) << endl; // OK, print 9
    cout << (v - 2) << endl; // OK, print 7
    // cout << (v = 2) << endl; // Error, see below
    A1 *a = new A1;
    B1 *b = new B1;
    delete a;
    delete b;
    a = new A1[5];
    delete[] a;
    return 0;
}
