//
// Created by chenlei on 2021/10/17.
//

#ifndef CPP_TRIAL_VECTOR_TRIAL_H
#define CPP_TRIAL_VECTOR_TRIAL_H

#include <iostream>
#include <vector>
#include <algorithm>

static void test_vector() {
    std::vector<int> a = {1, 2,3,4,5,6};
    std::vector<int> b(a.begin(), a.begin() + 5);
    std::vector<int> c(a.begin(), a.end());
    std::for_each(b.begin(), b.end(), [](int bb) {std::cout << bb << " ";});
    std::cout << std::endl;
    std::for_each(c.begin(), c.end(), [](int cc) {std::cout << cc << " ";});
    std::cout << std::endl;
}

#endif //CPP_TRIAL_VECTOR_TRIAL_H
