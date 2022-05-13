#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

int main() {
    std::string a = "3";
    std::string s = "abc" + a + "def" + ".";
    std::cout << s << std::endl;
    std::cout << a << std::endl;
    std::cout << std::toupper('a') << std::endl;
    typedef decltype(s.size()) size_type;
    for (size_type i = 0; i < s.size(); i++)
        std::cout << s[i];
    return 0;
}
