//
// Created by chenlei on 2021/9/28.
//

#ifndef CPP_TRIAL_STREAM_TRIAL_H
#define CPP_TRIAL_STREAM_TRIAL_H

#include <fstream>
#include <iostream>
#include <sstream>

static void test_fstream() {
    // std::ofstream ofs("./test.txt");
    // ofs << "hello" << endl;
    // ofs.close();
    std::stringstream ss;
    ss << "hello" << endl;
    ss << "你好" << endl;
    std::ofstream ofs2("./test2.txt", std::ios::app);
    ofs2 << ss.rdbuf();
    ofs2.close();
}

static void test_stream() {
    std::stringstream ss;
    ss << "hhh,ssss,";
    ss.seekp(-1, ios::end);
    ss << "\n";
    ss << "123,456,";
    ss.seekp(-1, ios::end);
    ss << "\n";
    std::cout << ss.str() << std::endl;
    std::ofstream ofs2("./test1.txt");
    ofs2 << ss.str();
    ofs2.close();

    std::ofstream outfile;
    outfile.open ("test.txt");

    outfile.write ("This is an apple",16);
    outfile.seekp (-7, ios::end);
    outfile.write (" sam",4);

    outfile.close();

}

#endif //CPP_TRIAL_STREAM_TRIAL_H
