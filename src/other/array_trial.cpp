#include <iostream>
#include <string>
#include <vector>

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

public:
    char b;
    int a;
    char c;
};

void test_array_class() {
    AAA aa[5];
    AAA bb;
    std::cout << sizeof(aa) << "," << sizeof(bb) << std::endl;
    std::cout << &bb << "," << (void *)&(bb.b) << "," << &(bb.a) << ", " << (void *)&(bb.c) << std::endl;
}

void test_array_pointer() {
    int arr1[10] = {1,2,3};
    int (*p1)[10] = &arr1;
    int *p2 = arr1;
    for (auto i: arr1) {
        std::cout << i << std::endl;
    }
    std::cout << "arr1:" << arr1 << std::endl;
    std::cout << "p1:" << p1 << std::endl;
    std::cout << "p2:" << p2 << std::endl;
    std::cout << "*p1:" << *p1 << std::endl;
    std::cout << "sizeof(p1):" << sizeof(p1) << std::endl;      // 指针
    std::cout << "sizeof(*p1):" << sizeof(*p1) << std::endl;    // 数组
    std::cout << "sizeof(**p1):" << sizeof(**p1) << std::endl;  // 数组元素
    char *(*p3)[3][6];  // 一个指向二维数组的指针，二维数组中存放的元素类型是char *
    std::cout << "sizeof(p3):" << sizeof(p3) << std::endl;      // 指针 8
    std::cout << "sizeof(*p3):" << sizeof(*p3) << std::endl;    // 二维数组 3*6*8
    std::cout << "sizeof(**p3):" << sizeof(**p3) << std::endl;  // 二维数组的第一行 6*8
    std::cout << "sizeof(***p3):" << sizeof(***p3) << std::endl;    // 二维数组的第一个元素(char *) 8
    std::cout << "sizeof(****p3):" << sizeof(****p3) << std::endl;  // 二维数组的第一个元素指向的数据(char) 1
}

int main() {
    test_array_class();
    // test_array_pointer();
    return 0;
}
