//
// Created by 陈磊 on 2020/8/11.
//

#ifndef CPP_NOTES_TEST_H
#define CPP_NOTES_TEST_H

#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/core.hpp>

void test_statck() {
    std::stack<char> s;
    std::cout << s.top() << std::endl;
}

void test_transform() {
    std::vector<std::vector<float>> m = {{0.1, 0.3},
                                         {0.2, 0.7},
                                         {0.8, 0.2}};
    std::vector<std::vector<uint8_t>> bit_map(m.size(), std::vector<uint8_t>(m[0].size()));
    std::transform(m.begin(), m.end(), bit_map.begin(), [](std::vector<float> p) {
        std::vector<uint8_t> res(p.size());
        std::transform(p.begin(), p.end(), res.begin(), [](float i) { return i > 0.3f ? 1 : 0; });
        return res;
    });
    std::for_each(bit_map.begin(), bit_map.end(), [](std::vector<uint8_t> &b) {
        std::for_each(b.begin(), b.end(), [](uint8_t &i) {
            i = i * 255;
        });
    });

    std::for_each(bit_map.begin(), bit_map.end(), [](std::vector<uint8_t> b) {
        std::for_each(b.begin(), b.end(), [](uint8_t i) {
            std::cout << int(i) << " ";
        });
        std::cout << std::endl;
    });

    std::cout << "arr = \n";
    uchar arr[bit_map.size()][bit_map[0].size()];
    for (size_t i = 0; i < bit_map.size(); i++) {
//        arr[i] = bit_map[i].data();
        for (size_t j = 0; j < bit_map[0].size(); j++) {
            arr[i][j] = bit_map[i][j];
            std::cout << int(arr[i][j]) << " ";
        }
        std::cout << std::endl;
    }
    cv::Mat mat(bit_map.size(), bit_map[0].size(), CV_8UC1, (uchar *) arr);
    std::cout << mat.rows << ", " << mat.cols << ", " << mat.type() << std::endl;
    std::cout << "mat = \n";
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            std::cout << int(mat.at<uchar>(i, j)) << " ";
        }
        std::cout << std::endl;
    }
}

bool fun(cv::Point2f p1, cv::Point2f p2) {
    return p1.x < p2.x;
}

struct Po {
    float x, y;
};

void test_numpy() {
    std::vector<int> num = {1, 5, 6, 7, 2};
    std::cout << *std::min_element(num.begin(), num.end()) << std::endl;

    cv::Point2f points[3] = {{4.1, 5.3},
                             {5.5, 0.2},
                             {1.2, 6.1}};
    float xmin = std::min_element(points, points + 3, [](cv::Point2f p1, cv::Point2f p2) { return p1.x < p2.x; })->x;
    float xmax = std::max_element(points, points + 3, [](cv::Point2f p1, cv::Point2f p2) { return p1.x < p2.x; })->x;
    float ymin = std::min_element(points, points + 3, [](cv::Point2f p1, cv::Point2f p2) { return p1.y < p2.y; })->y;
    float ymax = std::max_element(points, points + 3, [](cv::Point2f p1, cv::Point2f p2) { return p1.y < p2.y; })->y;

    std::cout << xmin << ", " << xmax << ", " << ymin << ", " << ymax << std::endl;

    Po p[2] = {{1, 2},
               {5, 1}};
    std::cout << std::max_element(p, p + 2, [](Po p1, Po p2) { return p1.x < p2.x; })->x << std::endl;
}

#endif //CPP_NOTES_TEST_H
