#include <bits/stdc++.h>
#include "unistd.h"

using namespace std;

class A {
public:
    virtual void testA() = 0;

    virtual void print() = 0;
};

class B : public A {
public:
    virtual void testA() = 0;

    virtual void print() override {
        std::cout << "B::print" << std::endl;
    }

    virtual void testB() {
        std::cout << "testB" << std::endl;
    }
};

class C : public B {
public:
    virtual void testA() {}

    virtual void print() override {
        std::cout << "C::print" << std::endl;
    }
};

class Base {
public:
    Base(int _val) : val(_val) {}

    Base() {}

private:
    int val;
};

class Sub : public Base {
public:
    int a{};
};

class Test {
private:
    // Test() {
    //     std::cout << "默认构造函数" << std::endl;
    // }

    Test(int a) {
        std::cout << "a = " << a << std::endl;
    }

public:
    static Test *get_object(int a) {
        return new Test(a);
    }
};

// 日志上报Class
class ReportClass {
private:
    ReportClass() {}

    ReportClass(const ReportClass &) = delete;

    ReportClass &operator=(const ReportClass &) = delete;

    ReportClass(const ReportClass &&) = delete;

    ReportClass &operator=(const ReportClass &&) = delete;

private:
    std::mutex mutex_;
    int count_ = 0;

    void addWorkThread();

public:
    void pushEvent(std::string event);

private:
    static void workThread(ReportClass *report);

private:
    static ReportClass *instance_;
    static std::mutex static_mutex_;

public:
    static ReportClass *GetInstance();

    static void ReleaseInstance();
};

std::mutex ReportClass::static_mutex_;
ReportClass *ReportClass::instance_;

ReportClass *ReportClass::GetInstance() {
    // 单例简单实现，非本文重点
    std::lock_guard<std::mutex> lock(static_mutex_);
    if (instance_ == nullptr) {
        instance_ = new ReportClass();
        instance_->addWorkThread();
    }
    return instance_;
}

void ReportClass::ReleaseInstance() {
    std::lock_guard<std::mutex> lock(static_mutex_);
    if (instance_ != nullptr) {
        delete instance_;
        instance_ = nullptr;
    }
}

// 轮询上报线程
void ReportClass::workThread(ReportClass *report) {
    while (true) {
        // 线程运行过程中，report可能已经被销毁了
        std::unique_lock<std::mutex> lock(report->mutex_);
        if (report->count_ > 0) {
            report->count_--;
        }

        usleep(1000 * 1000);
    }
}

// 创建任务线程
void ReportClass::addWorkThread() {
    std::thread new_thread(workThread, this);
    new_thread.detach();
}

// 外部调用
void ReportClass::pushEvent(std::string event) {
    std::unique_lock<std::mutex> lock(mutex_);
    this->count_++;
    std::shared_ptr<int> a = std::make_shared<int>(9);
}

class X {
public:
    X() {
        val = 0;
        std::cout << "Construct function.\n";
    }

    X(int _val) {
        val = _val;
        std::cout << "Construct function.\n";
    }

    ~X() {
        std::cout << "Destruct function.\n";
    }

    X(const X &x) {
        val = x.val;
        std::cout << "Copy construct function.\n";
    }

    X operator=(X &x) {
        val = x.val;
        std::cout << "Assign function.\n";
        return *this;
    }

    int val;
};

void test_shared(std::shared_ptr<X> a) {
    std::cout << a.use_count() << std::endl;
}

class parent;

class children;

class parent {
public:
    ~parent() { std::cout << "~parent()" << std::endl; }

public:
    std::shared_ptr<children> child;
};

class children {
public:
    ~children() { std::cout << "~children()" << std::endl; }

public:
    std::shared_ptr<parent> parent;
};

void Verify() {
    std::shared_ptr<parent> p(new parent);
    std::shared_ptr<children> c(new children);

    p->child = c;
    c->parent = p;
    p->child.reset();
}

int main1() {
    std::cout << "Begin" << std::endl;

    Verify();

    std::cout << "Done" << std::endl;
    return 0;
}

class A1 {
public:
    A1() {
        std::cout << "A1 init.\n";
    }

    ~A1() {
        std::cout << "A1 end.\n";
    }
};

class B1 {
public:
    B1() {
        std::cout << "B1 init.\n";
    }

    B1(int a) {
        std::cout << "B1 " << a << " init.\n";
    }

    ~B1() {
        std::cout << "B1 end.\n";
    }
};

class A2 {
public:
    A2() : b2(new B1()), b1(new B1(1)) {
        std::cout << "A2 init.\n";
    }

    ~A2() {
        std::cout << "A2 end.\n";
    }

    static void fun() {
        std::cout << "static fun.\n";
    }

private:
    B1 *b1;
    A1 a1;
    B1 *b2;
};

int main2() {
    // Test *t = Test::get_object(10);
    // ReportClass::GetInstance()->pushEvent("test");
    X a(10);
    X b(a);
    X c;
    X d = a;
    c = a;
    std::cout << "c.val = " << c.val << std::endl;
    std::cout << "Over.\n";
    std::shared_ptr<X> a1 = std::make_shared<X>();
    std::cout << a1.use_count() << std::endl;
    std::weak_ptr<X> a2 = a1;
    std::cout << a1.use_count() << std::endl;
    std::cout << a2.use_count() << std::endl;
    test_shared(a1);
    std::cout << a1.use_count() << std::endl;

    A2 aa2;
    // A2::fun();
    return 0;
}

class ClxBase {
public :
    ClxBase() {};

    virtual ~ ClxBase() { std::cout << "Destructor from base class.\n"; };

    virtual void DoSomething() { cout << " Do something in class ClxBase! " << endl; };
};

class ClxDerived : public ClxBase {
public :
    ClxDerived() {};

    ~ ClxDerived() { cout << " Output from the destructor of class ClxDerived! " << endl; };

    void DoSomething() { cout << " Do something in class ClxDerived! " << endl; };
};

class Point {
public:
    virtual ~Point() {

    }

    // int x;
    // int y;
    unsigned short a;
    // unsigned short b;
    // unsigned short c;
    // unsigned short d;
    // unsigned short e;
};

int main3() {
    ClxBase *pTest = new ClxDerived;
    pTest->DoSomething();
    delete pTest;
    Point p;
    std::cout << sizeof p << std::endl;
    std::cout << &p << std::endl;
    // std::cout << &p.x << std::endl;
    // std::cout << &p.y << std::endl;
    std::cout << &p.a << std::endl;
    // std::cout << &p.b << std::endl;
    // std::cout << &p.c << std::endl;
    // std::cout << &p.d << std::endl;
    // std::cout << &p.d << std::endl;

    const int a = 5;
    int *b = const_cast<int *>(&a);
    *b = 6;
    std::cout << "&a = " << &a << ", b = " << b << std::endl;
    std::cout << "a = " << a << ", *b = " << *b << std::endl;
    std::cout << typeid(p).name() << std::endl;
    return 0;
}

class AA {
public:
    virtual void m() {} // C现在是 多态
    // int a = 1;
};

class BB : public AA {
// public:
    // int b = 2;

    // void m() {}
};

int main4() {
    // BB *bb = new BB;
    // AA *aa = dynamic_cast<AA *> (bb);//基类指针向下转换为派生类指针  // AA *aa = bb;

    AA *aa = new AA;
    BB *bb = dynamic_cast<BB *>(aa);
    if (bb == nullptr)
        std::cout << "nullptr" << std::endl;
    return 0;
}

class A3 {
    // ......
};

class B2 : public A3 {
    // ......
};

// class C2 : public B2
// {
//      // ......
// };
int main5() {
    // C2 *pC = new C2;
    // B2 *pB = dynamic_cast<B2 *>(pC); // OK
    B2 *pB = new B2;
    A3 *pA = dynamic_cast<A3 *>(pB); // OK
    if (pB == nullptr)
        std::cout << "nullptr" << std::endl;
    if (pA == nullptr)
        std::cout << "nullptr" << std::endl;
    return 0;
}

int main6() {
    std::vector<bool> a(100);
    std::for_each(a.begin(), a.end(), [](int i) { std::cout << i << ","; });
    std::cout << std::endl;
    int *b = new int[100];
    std::for_each(b, b + 100, [](int i) { std::cout << i << ","; });
    std::cout << std::endl;
    for (int i = 0; i < 10; i++) {
        static int c = 0;
        c++;
        std::cout << c << std::endl;
    }
    return 0;
}

class CC {
public:
    CC(int _v) : v(_v) {
        std::cout << "Construct, v = " << v << "\n";
    }

    ~CC() {
        std::cout << "Destruct, v = " << v << "\n";
    }

    int v = 0;
};

CC test_value_pass(CC c) {
    CC d(0);
    d.v = c.v + 1;
    std::cout << "d\n";
    return d;
    // return c;
}

int main7() {
    CC c(0);
    std::cout << "c\n";
    auto res = test_value_pass(c);
    std::cout << res.v << std::endl;
    return 0;
}

class Base2 {
public:
    int m_a;
public:
    Base2(int a) : m_a(a) {
        std::cout << "Base obj constructed !" << std::endl;
    }
};

class Derived : public Base2 {
public:
    int m_b;
    int m_c;
    int m_d;
public:
    Derived(int a, int c) : m_c(c), m_b(m_a + m_c), Base2(a) {
        std::cout << "m_b = " << m_b << std::endl;
        std::cout << "Derived obj constructed !" << std::endl;
    }
};

int main() {
    Derived d(1, 10);
    std::cout << d.m_a << std::endl; // 1
    std::cout << d.m_b << std::endl; // 未初始化
    std::cout << d.m_c << std::endl; // 10
    std::cout << d.m_d << std::endl; // 1
    return 0;
}
