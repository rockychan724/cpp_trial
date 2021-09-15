#ifndef TEST_SHARED_PTR_H
#define TEST_SHARED_PTR_H

#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <unistd.h>


class Run {
private:
    std::shared_ptr<std::string> sp;
    std::thread *thr;
public:
    Run(std::shared_ptr<std::string> &p) {
        this->sp = p;
        thr = new std::thread([this] { this->print(); });
    }

    ~Run() {
        delete thr;
        thr = nullptr;
    }

    void set(std::shared_ptr<std::string> p) {
        this->sp = p;
    }

    void print() {
        while (true) {
            std::cout << "sp = " << this->sp << ", " << this->sp->data() << std::endl;
            sleep(1);
        }
    }
};

void test_shared_ptr() {
    static std::shared_ptr<std::string> p(new std::string("aaa"));
    std::cout << "p = " << p << ", " << p->data() << std::endl;
    Run r(p);
    sleep(2);
//    r.set(std::shared_ptr<std::string>(new std::string("bbb")));
    p.reset(new std::string("bbb"));
    std::cout << "p = " << p << ", " << p->data() << std::endl;
    sleep(2);
    exit(0);
}

void test_shared_ptr_old() {
//    std::string a("hhh");
//    std::string *b = &a;
//    std::shared_ptr<std::string> p;
//    std::cout << a << std::endl;
//    std::cout << *b << std::endl;
//    std::cout << p << std::endl;
//    p = std::shared_ptr<std::string>(new std::string(a));
//    a = "aaa";
//    std::cout << a << std::endl;
//    std::cout << *b << std::endl;
//    std::cout << p->data() << std::endl;

//    std::string *c = new std::string("in");
//    run(c);
//    print();
//    std::cout << "c: " << c->data() << std::endl;
//    c = new std::string("out");
//    print();
}

#endif // TEST_SHARED_PTR_H
