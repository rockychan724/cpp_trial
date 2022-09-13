/**
 * learn virtual table: https://zhuanlan.zhihu.com/p/563418849
 */

#include <iostream>
#include <algorithm>

class A{
public:
    void show() {
        std::cout << "A show" << std::endl;
    }
    virtual void a() {
        std::cout << "A a" << std::endl;
    }
    virtual void b() {
        std::cout << "A b" << std::endl;
    }
    virtual void c() {
        std::cout << "A c" << std::endl;
    }
};

int main() {
    typedef u_long u64;
    typedef void(*func)();
    A a1, a2;
    std::cout << sizeof(a1) << ", " << sizeof(a2) << std::endl;
    printf("%p\n", &A::show);
    printf("%p\n", &A::a);
    printf("%p\n", &A::b);
    printf("%p\n", &A::c);
    u64* p1 = (u64*)&a1;
    u64* p2 = (u64*)&a2;
    std::cout << static_cast<void *>(p1) << std::endl;
    std::cout << static_cast<void *>(p2) << std::endl;
    u64* arr1 = (u64*)*p1;
    u64* arr2 = (u64*)*p2;
    func a = (func)arr1[0];
    func b = (func)arr1[1];
    func c = (func)arr1[2];
    a();
    b();
    c();
    std::cout << "the address of virtual table pointer in an object: p1 = " << p1 << ", p2 = " << p2 << std::endl;
    std::cout << "the value of virtual table pointer in an object: *p1 = " << *p1 << ", *p2 = " << *p2 << std::endl;
    // std::cout << "virtual table address of a class: arr1 = " << arr1 << ", arr2 = " << arr2 << std::endl;
    // std::cout << "virtual table address of a class: *arr1 = " << *arr1 << ", *arr2 = " << *arr2 << std::endl;
    return 0;
}
