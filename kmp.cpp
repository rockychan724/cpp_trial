#include "kmp.h"

void KMP::getNext(std::string str, int *next)
{
    int i = 0;
    next[0] = 0;
    for (i = 1; i < str.length(); i++) {
        if (str[i] == str[next[i - 1]]) {
            next[i] = next[i - 1] + 1;
        } else {
            next[i] = 0;
        }
    }
}

bool KMP::match(std::string longStr, std::string shortStr, int *next)
{
    int i = 0;
    int j = 0;
    bool result = false;
    while (i<longStr.length() && j<shortStr.length()){
        if (longStr[i] == shortStr[j]){
            i ++;
            j ++;
        }else {
            if (j == 0) {//长的那个往后移动一位，短的那个不需要动
                i++;
            }else {
                int m = j - next[j-1];//需回溯的位数，，包含上面的j=1的情况，即已匹配的字符数 - 对应的部分匹配值
                j = j - m;//设置下一次的起始坐标
            }
        }
    }
    if (j == shortStr.length()){
        result = true;
    }
    return result;
}
