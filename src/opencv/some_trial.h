//
// Created by chenlei on 2021/10/17.
//

#ifndef CPP_TRIAL_SOME_TRIAL_H
#define CPP_TRIAL_SOME_TRIAL_H

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void test_cv_point() {
    cv::Point2f a[2] = {{1.0, 1.0}, {2.9, 2.9}};
    std::cout << a << std::endl;
}

static void test_glob() {
    std::vector<cv::String> files;
    cv::glob("../src/other/*.h", files, false);
    std::cout << *files.rbegin() << std::endl;
}

static void test_rotated_rect() {
    Mat test_image(200, 200, CV_8UC3, Scalar(0));
    RotatedRect rRect = RotatedRect(Point2f(100,100), Size2f(100,50), -10);
    Point2f vertices[4];
    rRect.points(vertices);
    for (int i = 0; i < 4; i++) {
        line(test_image, vertices[i], vertices[(i+1)%4], Scalar(0,255,0), 2);
        putText(test_image, to_string(i), vertices[i], cv::FONT_HERSHEY_PLAIN, 1.0, Scalar (0, 0, 255), 2);  // debug
    }
    putText(test_image, "HELLO", rRect.center, cv::FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 2);
    Rect brect = rRect.boundingRect();
    rectangle(test_image, brect, Scalar(255,0,0), 2);
    Mat dst_image;
    transpose(test_image, dst_image);
    Mat flipped_image;
    flip(dst_image, flipped_image, 0);
    imshow("rectangles", test_image);
    imshow("transpose", dst_image);
    imshow("flip", flipped_image);
    waitKey(0);
}

#endif //CPP_TRIAL_SOME_TRIAL_H
