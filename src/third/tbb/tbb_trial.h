//
// Created by chenlei on 2021/9/30.
//

#ifndef CPP_TRIAL_TBB_TRIAL_H
#define CPP_TRIAL_TBB_TRIAL_H

#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <tbb/concurrent_vector.h>

void run(const std::vector<std::string>& input, tbb::concurrent_vector<std::string> &res) {
    for (const auto &s: input) {
        res.push_back(s);
    }
}

static void test_tbb_vector() {
    tbb::concurrent_vector<std::string> res;
    std::vector<std::string> input;
    for (int i = 0; i < 100; i++) {
        input.push_back(std::to_string(i));
    }
    std::vector<std::shared_ptr<std::thread>> threads;
    for (int i = 0; i < 2; i++) {
        auto t = std::make_shared<std::thread>(run, input, std::ref(res));
        threads.push_back(t);
    }
    for (int i = 0; i < 2; i++) {
        threads[i]->join();
    }
    for (const auto &r: res) {
        std::cout << r << " ";
    }
    std::cout << std::endl;
}

#endif //CPP_TRIAL_TBB_TRIAL_H
