//
// Created by chenlei on 2021/9/25.
//

#ifndef CPP_TRIAL_CLASS_TRIAL_H
#define CPP_TRIAL_CLASS_TRIAL_H

#include <iostream>

using namespace std;

class Base {
public:
    Base() {
        cout << "The constructor of Base" << endl;
    }
};

class VBase {
public:
    VBase() {
        cout << "The constructor of VBase" << endl;
    }
};

class VBase_ {
public:
    VBase_() {
        cout << "The constructor of VBase_" << endl;
    }
};

/* 普通继承与虚继承 */
class A : public Base, virtual public VBase_, virtual public VBase {
public:
    A() {
        cout << "The constructor of A" << endl;
    }
};

class B {
public:
    B() {
        cout << "The constructor of B" << endl;
    }
};

class D {
public:
    D() {
        cout << "The constructor of D" << endl;
    }
};

class C : public B, public A {
public:
    C() {
        cout << "The constructor of C" << endl;
    }

private:
    /* 对象成员 */
    D obj;
};

void test_class_inherit() {
    /* 实例化类 C */
    C test = C();
}

class Animal {
public:
    Animal() {
        food = 10;
        weight = 20;
    }

    void eat() {
        print_animal(*this);
        food--;
        weight++;
    }

    void sleep() const {
        weight--;  // const成员函数可以修改mutable类型的成员变量
        print_animal(*this);
    }

    friend void print_animal(const Animal &animal) {
        std::cout << "food: " << animal.food << ", weight: " << animal.weight << std::endl;
    }

    friend class People;

private:
    int food;
    mutable int weight;
};

void test_class_Animal() {
    const Animal animal;
    animal.sleep();  // 常量对象只能调用常量成员函数，指向常量对象的引用和指针也是如此

    Animal animal2;
    animal2.eat();
    print_animal(animal2);
}

// struct默认访问权限为public，而class的默认访问权限为private
struct Base1 {
    int a = 1;
};

// struct默认继承为public，而class的默认继承为private
struct Base2 : Base1 {

};

class People {
public:
    // People() {}

    People(std::string _name = "Zhangsan") : name(_name) {}

    void clear(const Animal &animal) {
        std::cout << "food: " << animal.food << ", weight: " << animal.weight << std::endl;
    }

    std::string &get_name() {
        return name;
    }

private:
    std::string name;
};

// test explicit

class Sales_data {
public:
    Sales_data() {
        std::cout << "Default construct.\n";
    }

    explicit Sales_data(int _num) : num(_num) {
        std::cout << "Construct from int.\n";
    }

    Sales_data(const std::string &_name) : name(_name) {
        std::cout << "Construct from std::string.\n";
    }

    Sales_data(const std::string &_name, int _num) : name(_name), num(_num) {
        std::cout << "Construct from std::string and int.\n";
    }

    void print(const Sales_data &data) {
        std::cout << "name: " << data.name << ", num: " << data.num << std::endl;
    }

private:
    std::string name = "First";
    int num = 0;
};

void test_explicit() {
    std::string name = "LiXiangGuo";
    Sales_data sd;
    sd.print(name);  // 正确：隐式类型转换，const std::string&转Sales_data
    // sd.print("KuangRenRiJi");  // 错误：不能进行两层隐式类型转换，1. const char*转const std::string&，2. const std::string&转Sales_data
    // sd.print(123);  // 错误：explicit关键字表明构造函数Sales_data(int _num)必须显式构造
    sd.print(Sales_data(123));  // 正确：显式构造
    sd.print(static_cast<Sales_data>(456));  // 正确：显式转换
}

void test_init() {
    Sales_data sd1("hhh", 1);
    Sales_data sd2{"hhh", 1};
    Sales_data sd3 = {"hhh", 1};
    sd3 = {"aaa", 2};  // 先将 {"aaa", 2} 隐式转化为 Sales 临时对象，再将临时对象赋值给 sd3
}

int main() {
    test_class_inherit();
    test_class_Animal();

    Base2 b;
    std::cout << b.a << std::endl;

    People p;
    std::string &name = p.get_name();
    std::cout << p.get_name() << std::endl;
    name = "Lisi";
    std::cout << p.get_name() << std::endl;

    test_explicit();
    test_init();
    return 0;
}

#endif //CPP_TRIAL_CLASS_TRIAL_H
