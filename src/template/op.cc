#include "op.h"

#include <iostream>

// template <typename T>
// Sub<T>::Sub() {
//   std::cout << "Sub construct.\n";
// }

template <typename T>
T Sub<T>::operator()(T a, T b) {
  return a - b;
}

// 模板实例化
// 要实现模板的声明和实现分离，该步骤是必要的
template class Sub<int>;
