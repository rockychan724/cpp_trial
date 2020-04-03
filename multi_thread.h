#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H

#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void thread01()
{
    std::cout << "thread01 id: " << std::this_thread::get_id() << std::endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Thread 01 is working ！" << endl;
        sleep(1);
    }
}
void thread02()
{
    std::cout << "thread02 id: " << std::this_thread::get_id() << std::endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Thread 02 is working ！" << endl;
        sleep(1);
    }
//    while(1);
}

#endif // MULTI_THREAD_H
