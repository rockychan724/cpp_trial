//
// Created by chenlei on 2021/10/17.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

class A {
public:
    A() {
        val = 1;
        std::cout << "a";
    }

    A(int _val) : val(_val) {
        std::cout << "a";
    }

    ~A() {
        val = -1;
        std::cout << "~";
    }

    friend std::ostream &operator<<(std::ostream &ost, const A &a) {
        ost << a.val;
        return ost;
    }

private:
    int val, b, c;
};

template<typename T>
void print_vector(const T &a) {
    for (const auto &i : a)
        std::cout << i << ",";
    std::cout << "\b\n";
}

class B {
public:
    B(int a) {

    }
};

int arr1[10];

int main() {
    std::vector<A> a;
    print_vector(a);
    std::cout << "====== resize to 10 ======\n";
    a.resize(10);
    std::cout << std::endl;
    print_vector(a);
    std::cout << "====== resize to 20 ======\n";
    a.resize(25, 3);
    std::cout << std::endl;
    print_vector(a);
    std::cout << "capacity:" << a.capacity() << std::endl;
    a.push_back(3);
    std::cout << "capacity:" << a.capacity() << std::endl;
    std::cout << "====== resize to 5 ======\n";
    a.resize(5, 2);
    std::cout << std::endl;
    print_vector(a);
    std::cout << "capacity:" << a.capacity() << std::endl;
    std::cout << a[6] << std::endl;

    {
        std::vector<A> b(3, 10);
        // b.push_back(A(7));
        // b.push_back(8);
        b.clear();
        std::cout << "clear over.\n";
        std::cout << b.capacity() << std::endl;
    }
    std::cout << "Over!\n";
    // B bb[10];  // 报错
    bool arr2[10] = {true};
    print_vector(arr1);
    print_vector(arr2);

    std::vector<std::string> v_s = {10, "abc"};
    print_vector(v_s);
    v_s = {10, "efg"};
    print_vector(v_s);

    int size = 10;
    int arr[size];
    // print_vector(arr);
    for (auto &i: arr)
        std::cout << i << ",";
    std::cout << std::endl;
    return 0;
}

static void test_vector() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6};
    std::vector<int> b(a.begin(), a.begin() + 5);
    std::vector<int> c(a.begin(), a.end());
    std::for_each(b.begin(), b.end(), [](int bb) { std::cout << bb << " "; });
    std::cout << std::endl;
    std::for_each(c.begin(), c.end(), [](int cc) { std::cout << cc << " "; });
    std::cout << std::endl;
}
