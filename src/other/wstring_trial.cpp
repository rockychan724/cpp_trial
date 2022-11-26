#include <iostream>
#include <locale>
#include <string>
#include <vector>

int main() {
  wchar_t *wst = L"你好";
  std::cout << wcslen(wst) << std::endl;
  std::wcout.imbue(std::locale("chs"));
  std::wcout << wst << std::endl;
  return 0;
}