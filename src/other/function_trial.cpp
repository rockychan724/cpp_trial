#include <iostream>

class A {
public:
    A() {
        a = 1;
        std::cout << "Construct.\n";
    }

    A(int a1, int a2) {
        a = a1 + a2;
        std::cout << "Construct from list.\n";
    }

    A(const A &b) {
        a = b.a;
        std::cout << "Copy construct.\n";
    }

    ~A() {
        std::cout << "Destruct.\n";
    }

    int a;
};


A test_returnval1(A _a) {
    return _a;
}

// 注意体会v2和v3的区别
A test_returnval2(A _a) {
    A aa = {1, 3};
    std::cout << "======\n";
    return aa;
}

A test_returnval3(A _a) {
    A aa = {1, 3};
    std::cout << "======\n";
    return _a;  // 为什么返回形参会构造临时变量而返回局部变量就不用构造临时变量
}

int *test_pointer() {
    // int arr[3] = {1,2,3};
    // return arr;  // error! 数组不支持返回，数组是栈上的局部变量，且数组不支持拷贝初始化和拷贝复制
    
    int *arr = new int[3];
    arr[0] = 1, arr[1] = 2, arr[2] = 3;
    return arr;
}

int main() {
    A a;
    std::cout << "test_returnval2:\n";
    a = test_returnval2(a);
    std::cout << a.a << std::endl;
    std::cout << "test_returnval3:\n";
    a = test_returnval3(a);
    std::cout << a.a << std::endl;
    
    // int *p = test_pointer();
    // std::cout << p[2] << std::endl;
    return 0;
}
