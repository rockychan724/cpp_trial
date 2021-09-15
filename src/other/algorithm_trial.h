//
// Created by chenlei on 2021/9/15.
//

#ifndef CPP_TRIAL_ALGORITHM_TRIAL_H
#define CPP_TRIAL_ALGORITHM_TRIAL_H

#include <iostream>
#include <algorithm>

void test_max_element() {
    int a[] = {1,2,5,2,8,3};
    long max_index = std::max_element(a, a + 6) - a;
    std::cout << "max index = " << max_index << std::endl;
}

#endif //CPP_TRIAL_ALGORITHM_TRIAL_H
