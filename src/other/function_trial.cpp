#include <iostream>

class A {
public:
    A() {
        a = 1;
        std::cout << "Construct: " << static_cast<void *>(this) << "\n";
    }

    A(int a1, int a2) {
        a = a1 + a2;
        std::cout << "Construct from list: " << static_cast<void *>(this) << "\n";
    }

    A(const A &b) {
        a = b.a;
        std::cout << "Copy construct: " << static_cast<void *>(this) << "\n";
    }

    ~A() {
        std::cout << "Destruct: " << static_cast<void *>(this) << "\n";
    }

    A& operator=(const A &b) {
        a = b.a;
        std::cout << "Operator=: " << static_cast<void *>(this) << "\n";
        return *this;
    }

    int a;
};


A returnval1(A _a) {
    std::cout << "======\n";
    return _a;
}

// 注意体会v2和v3的区别
A returnval2(A _a) {
    A aa{1, 3};
    std::cout << "======\n";
    return aa;
}

A returnval3(A _a) {
    A aa{1, 3};
    std::cout << "======\n";
    return _a;  // 为什么返回形参会构造临时变量而返回局部变量就不用构造临时变量
}

int *test_pointer() {
    // int arr[3] = {1,2,3};
    // return arr;  // error! 数组不支持返回，数组是栈上的局部变量，且数组不支持拷贝初始化和拷贝赋值
    
    int *arr = new int[3];
    arr[0] = 1, arr[1] = 2, arr[2] = 3;
    return arr;
}

void test_returnval() {
    A a;
    std::cout << "\nV1:\n";
    a = returnval1(a);
    std::cout << a.a << std::endl;
    std::cout << "\nV2:\n";
    a = returnval2(a);
    std::cout << a.a << std::endl;
    std::cout << "\nV3:\n";
    a = returnval3(a);
    std::cout << a.a << std::endl << std::endl;
}

bool fun(const int *a, const int *b) {
    
}

typedef bool func(const int *a, const int *b);

int test_fun(int a, func f) {

}

void print_array(int arr[4]) {
    for (int i = 0; i < 4; ++i) {
        std::cout << arr[i] << ",";
    }
    std::cout << std::endl;
}

void test_array_parameter() {
    int arr[4] = {1,2,3};
    print_array(arr);
}

int main() {
    // int *p = test_pointer();
    // std::cout << p[2] << std::endl;
    
    // test_returnval();
    test_array_parameter();
    return 0;
}
