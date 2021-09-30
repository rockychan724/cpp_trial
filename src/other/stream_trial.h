//
// Created by chenlei on 2021/9/28.
//

#ifndef CPP_TRIAL_STREAM_TRIAL_H
#define CPP_TRIAL_STREAM_TRIAL_H

#include <fstream>
#include <sstream>

void test_fstream() {
    // std::ofstream ofs("./test.txt");
    // ofs << "hello" << endl;
    // ofs.close();
    std::stringstream ss;
    ss << "hello" << endl;
    ss << "你好" << endl;
    std::ofstream ofs2("./test2.txt", std::ios::app);
    ofs2 << ss.rdbuf();
    ofs2.close()
;}

#endif //CPP_TRIAL_STREAM_TRIAL_H
