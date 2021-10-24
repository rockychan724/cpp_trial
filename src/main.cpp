//
// Created by chenlei on 2021/9/15.
//

#include "opencv/some_trial.h"
#include "other/pointer.h"
#include "other/algorithm_trial.h"
#include "other/class_trial.h"
#include "other/stream_trial.h"
#include "other/tbb_trial.h"
#include "other/vector_trial.h"

void test_1_shift() {
    std::cout << (1 << 0) << std::endl;
    std::cout << (1 << 1) << std::endl;
    std::cout << (1 << 2) << std::endl;
    // std::cout << (1 << -2) << std::endl;
}

int main() {
    // test_max_element();
    // test_datatype();
    // test_1_shift();
    // test_class_inherit();
    // test_fstream();
    // test_tbb_vector();
    // test_vector();
    // test_cv_point();
    // test_glob();
    // test_stream();
    test_rotated_rect();
    return 0;
}

