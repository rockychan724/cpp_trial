#ifndef KMP_H
#define KMP_H

#include <iostream>
#include <string>


class KMP
{
public:
    KMP();

    void getNext(std::string str, int *next);

    bool match(std::string longStr, std::string shortStr, int *next);
};

#endif // KMP_H
