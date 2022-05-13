//
// Created by chenlei on 2021/9/15.
//

#include <iostream>

void test_1_shift() {
    std::cout << (1 << 0) << std::endl;
    std::cout << (1 << 1) << std::endl;
    std::cout << (1 << 2) << std::endl;
    // std::cout << (1 << -2) << std::endl;

    int s_a = 0x80000000;
    std::cout << sizeof(s_a) << std::endl;
    std::cout << s_a << std::endl;
    std::cout << "left shift 1:" << (s_a << 1) << std::endl;
    std::cout << "left shift 2:" << (s_a << 2) << std::endl;
    std::cout << "right shift 1:" << (s_a >> 1) << std::endl;
    std::cout << "right shift 2:" << (s_a >> 2) << std::endl;
    int temp = 0xe0000000;
    std::cout << temp << std::endl;
}

int main() {
    test_1_shift();
    return 0;
}

