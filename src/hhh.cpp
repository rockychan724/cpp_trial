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
int main() {
    Derived d(1, 10);
    std::cout << d.m_a << std::endl; // 1
    std::cout << d.m_b << std::endl; // 未初始化
    std::cout << d.m_c << std::endl; // 10
    std::cout << d.m_d << std::endl; // 1
    return 0;
}