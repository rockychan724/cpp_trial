#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

//std::string wstring_2_string(std::wstring in)
//{
//    const wchar_t *pw = in.c_str();
//    std::string val = "";
//    if(!pw)
//    {
//        return val;
//    }
//    size_t size= wcslen(pw)*sizeof(wchar_t);
//    char *pc = NULL;
//    if(!(pc = (char*)malloc(size)))
//    {
//        return val;
//    }
//    size_t destlen = wcstombs(pc,pw,size);
//    /*转换不为空时，返回值为-1。如果为空，返回值0*/
//    if (destlen ==(size_t)(0))
//    {
//        return val;
//    }
//    val = pc;
//    delete pc;
//    return val;
//}

//std::wstring string_2_wstring(std::string in)
//{
//    const char *pc = in.c_str();
//    std::wstring val = L"";

//    if(NULL == pc)
//    {
//        return val;
//    }
//    //size_t size_of_ch = strlen(pc)*sizeof(char);
//    //size_t size_of_wc = get_wchar_size(pc);
//    size_t size_of_wc;
//    size_t destlen = std::mbstowcs(0,pc,0);
//    if (destlen ==(size_t)(-1))
//    {
//        return val;
//    }
//    size_of_wc = destlen+1;
//    wchar_t * pw  = new wchar_t[size_of_wc];
//    mbstowcs(pw,pc,size_of_wc);
//    val = pw;
//    delete pw;
//    return val;
//}

std::string wstring_2_string(const std::wstring ws) {
    std::string strLocale = setlocale (LC_ALL, "");
    const wchar_t *wchSrc = ws.c_str ();
    size_t nDestSize = wcstombs (nullptr, wchSrc, 0) + 1;
    char *chDest = new char[nDestSize];
    memset(chDest, 0, nDestSize);
    wcstombs (chDest, wchSrc, nDestSize);
    std::string strResult = chDest;
    delete[] chDest;
    chDest = nullptr;
    setlocale (LC_ALL, strLocale.c_str ());
    return strResult;
}

std::wstring Utf82Unicode(const std::string& str) {
    std::wstring wstr = L"";
    size_t inLength = str.size();
    for (int i = 0; i < inLength; ) {
        wchar_t unicode = 0x00000000;
        if ((str[i] & 0xf0) == 0xf0) {
            unicode |= ((str[i]&0x07) << 18) | ((str[i+1]&0x3f) << 12) | ((str[i+2]&0x3f) << 6) | (str[i+3]&0x3f);
            i+=4;
        } else if ((str[i] & 0xe0) == 0xe0) {
            unicode |= ((str[i]&0x0F) << 12) | ((str[i+1]&0x3F) << 6) | (str[i+2]&0x3F);
            i+=3;
        } else if ((str[i] & 0xC0) == 0xC0) {
            unicode |= ((str[i]&0x1F) << 6) | (str[i+1]&0x3F);
            i+=2;
        } else if ((str[i] & 0x80) == 0x00) {
            unicode |= (str[i]&0x7F);
            i++;
        } else {
            i++;
        }

        wstr += unicode;
    }

    return wstr;
}

#endif // FUNC_H
