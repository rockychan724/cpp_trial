//
// Created by chenlei on 2021/10/26.
//

#ifndef CPP_TRIAL_UUID_TRIAL_H
#define CPP_TRIAL_UUID_TRIAL_H

#include <iostream>
#include "uuid/uuid.h"

void test_uuid() {
    uuid_t uu;
    uuid_generate(uu);
    for (int i = 0; i < 16; i++) {
        printf("%d-", int (uu[i]));
    }
    printf("\n");
    std::cout << uu << std::endl;
}

/*
 * cmd：待执行命令
 * result：命令输出结果
 * 函数返回：0 成功；-1 失败；
 */
int ExecuteCMD(const char *cmd, char *result)
{
    const int CMD_RESULT_BUF_SIZE = 1024;
    int iRet = -1;
    char buf_ps[CMD_RESULT_BUF_SIZE];
    FILE *ptr;

    if((ptr = popen(cmd, "r")) != nullptr)
    {
        while(fgets(buf_ps, sizeof(buf_ps), ptr) != nullptr)
        {
            // strcat(result, buf_ps);
            // if(strlen(result) > CMD_RESULT_BUF_SIZE)
            // {
            //     break;
            // }
            std::string line(buf_ps);
            int index1 = line.find("UUID: ");
            int index2 = line.find_last_of(")");
            if (index1 != -1 && index2 != -1) {
                std::string uuid = line.substr(index1 + 6, index2 - (index1 + 6));
                std::cout << "uuid:" << uuid << std::endl;
                iRet = 0;  // 处理成功
            }
        }
        pclose(ptr);
        ptr = nullptr;
    }
    else
    {
        printf("popen %s error\n", cmd);
        iRet = -1; // 处理失败
    }

    return iRet;
}

static void test_cmd() {
    char result[1024]={0};

    if (ExecuteCMD("nvidia-smi -L", result) == -1) {
        printf("Error!\n");
    } else {
        printf("This is an example\n\n");
        printf("%s", result);
        printf("\n\nThis is end\n");

    }
}

#endif //CPP_TRIAL_UUID_TRIAL_H
