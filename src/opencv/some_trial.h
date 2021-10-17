//
// Created by chenlei on 2021/10/17.
//

#ifndef CPP_TRIAL_SOME_TRIAL_H
#define CPP_TRIAL_SOME_TRIAL_H

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

static void test_cv_point() {
    cv::Point2f a[2] = {{1.0, 1.0}, {2.9, 2.9}};
    std::cout << a << std::endl;
}

static void test_glob() {
    std::vector<cv::String> files;
    cv::glob("../src/other/*.h", files, false);
    std::cout << *files.rbegin() << std::endl;
}

#endif //CPP_TRIAL_SOME_TRIAL_H
