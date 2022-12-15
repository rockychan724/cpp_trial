#include "op.h"

#include <iostream>

int main() {
  Add<int> add_i;
  Add<double> add_d;
  Sub<int> sub_i;
  std::cout << add_i(1, 2) << std::endl;
  std::cout << add_d(1.0, 2.0) << std::endl;
  std::cout << sub_i(5, 1) << std::endl;

  // 注意，此处可以定义 Sub<double> 类型的变量，想想为什么？
  // 因为此处定义 Sub<double> 类型的变量是调用 Sub<double> 的默认构造函数，
  // 而 Sub 类模板中没有显示定义默认构造函数，因此该模板可以实例化成任意类型的
  Sub<double> sub_d;
  // 注意，此处编译会报错，想想为什么？
  // std::cout << sub_d(5.0, 1.0) << std::endl;
  return 0;
}
