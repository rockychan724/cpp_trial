#ifndef TEST_DB_PP_H
#define TEST_DB_PP_H

#include "bzc_db_pp.h"
#include <fstream>
#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

void DrawRotatedRectangle(cv::Mat &image, cv::RotatedRect rotatedRectangle, cv::Scalar color) {
    cv::Point2f vertices2f[4];
    rotatedRectangle.points(vertices2f);
    cv::Point root_points[1][4];
    for (int i = 0; i < 4; ++i) {
        root_points[0][i] = vertices2f[i];
    }
    const cv::Point *ppt[1] = {root_points[0]};
    int npt[] = {4};
    cv::polylines(image, ppt, npt, 1, 1, color, 3, 8, 0);
}

void test_db_pp() {
    bzc_db_pp db_pp;
    std::vector<std::vector<float>> pred_map;
    cv::Point2f scales;

    std::ifstream ifs("/home/chenlei/Desktop/db_test_demo/test2_pred_map.txt");
    if (!ifs.good()) {
        std::cout << "There are some errors when open input file!!!\n";
        std::exit(1);
    }
    int i = 0;
    std::string line;
    std::vector<cv::Size> size(2);
    while (std::getline(ifs, line)) {
        if (i < 2) {
            line = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
            int index = line.find(",");
            std::string h = line.substr(0, index), w = line.substr(index + 1);
            std::cout << "(" << h << ", " << w << ")" << std::endl;
            size[i].height = std::atoi(h.c_str());
            size[i].width = std::atoi(w.c_str());
        } else {
            std::vector<float> pred_line(size[1].width);
            std::stringstream ss;
            ss << line;
            for (int i = 0; i < size[1].width; i++) {
                ss >> pred_line[i];
            }
            pred_map.push_back(pred_line);
        }
        i++;
    }
    ifs.close();
    std::cout << "i = " << i << std::endl;

    scales.x = (static_cast<float>(size[1].width)) / size[0].width;
    scales.y = (static_cast<float>(size[1].height)) / size[0].height;
    std::vector<cv::RotatedRect> boxes = db_pp.parse_output(pred_map, scales);
    cv::Mat img = cv::imread("/home/chenlei/Desktop/db_test_demo/test2.jpg");
    for (auto rr : boxes) {
        std::vector<int> v = {0, 255, 0};
        cv::Scalar s{0, 0, 0};
        s[0] = v[0];
        s[1] = v[1];
        s[2] = v[2];
        DrawRotatedRectangle(img, rr, s);
    }
    cv::imwrite("/home/chenlei/Desktop/db_test_demo/test2_out_cpp.jpg", img);
}

#endif // TEST_DB_PP_H
