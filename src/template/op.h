#ifndef SRC_TEMPLATE_OP_H_
#define SRC_TEMPLATE_OP_H_

// 1. 模板的实现和实现都在 .h 中
template <typename T>
struct Add {
  T operator()(T a, T b) { return a + b; }
};

// 2. 模板的声明和实现分离：模板声明在 .h 中，实现在 .cc 中
template <typename T>
struct Sub {
  // Sub();
  T operator()(T a, T b);
};

#endif  // SRC_TEMPLATE_OP_H_
