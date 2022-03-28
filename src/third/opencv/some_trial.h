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

    cv::copyMakeBorder(test_image, test_image, 20, 2, 3, 40, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));
    imshow("rectangles", test_image);
    imshow("transpose", dst_image);
    imshow("flip", flipped_image);
    waitKey(0);
}

static void test_minAreaRect() {
    Mat test_image(200, 200, CV_8UC3, Scalar(0));
    std::vector<Point2f> points = {{0, 10}, {150, 10}, {50, 120}, {10, 150}};
    cv::RotatedRect rRect = cv::minAreaRect(points);
    Point2f vertices[4];
    rRect.points(vertices);

    for (int i = 0; i < 4; i++) {
        line(test_image, vertices[i], vertices[(i+1)%4], Scalar(0,255,0));
    }

    Rect brect = rRect.boundingRect();
    rectangle(test_image, brect, Scalar(255,0,0), 2);
    cv::Mat tmp_img;
    test_image(brect).copyTo(tmp_img);

    imshow("rectangles", test_image);
    imshow("rect", tmp_img);
    waitKey(0);
}

#endif //CPP_TRIAL_SOME_TRIAL_H
