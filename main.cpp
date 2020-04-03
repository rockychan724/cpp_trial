#include "bits/stdc++.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "func.h"
#include "multi_thread.h"
#include "tree.h"
#include "kmp.h"
#include "ac_test.h"
#include "ac_tree.h"

using namespace std;
using namespace cv;

Mat scalar_demo1() {
    Mat M(4,4,CV_32FC2,Scalar(1,3));
    cout<<M<<endl;
    //    imshow("1", M);
    return M;
}

void scalar_demo2() {
    Mat M(4,4,CV_32FC3,Scalar(1,2,3));
    cout<<M<<endl;
    //    imshow("2", M);
}

void scalar_demo3() {
    Mat M(4,4,CV_32FC4,Scalar(1,2,3));
    cout<<M<<endl;
    imshow("3", M);
    waitKey();
}

void test1()
{
    int h = std::rand()%500;
    int w = std::rand()%500;
    int b = std::rand()%255;
    int g = std::rand()%255;
    int r = std::rand()%255;
    std::cout << h << "," << w << "," << b << "," << g << "," << r << std::endl;
    cv::Mat image(h, w, CV_8UC3, cv::Scalar(b, g, r));
    std::cout << "Hello World!" << std::endl;
    cv::imshow("test", image);
    cv::waitKey();
}

void test2()
{
    scalar_demo1();
    cout<<"**********************************"<<endl;
    scalar_demo2();
    cout<<"**********************************"<<endl;
    scalar_demo3();
    cv::waitKey();
}

void test3()
{
    std::string foo = "foo-string";
    std::string bar = "bar-string";
    std::vector<std::string> myvector;

    myvector.push_back (foo);                    // copies
    myvector.push_back (std::move(bar));         // moves

    std::cout << "myvector contains:";
    for (std::string& x:myvector) std::cout << ' ' << x;
    std::cout << '\n';
    std::cout << foo << std::endl;
    std::cout << bar << std::endl;
    bar = "hahah";
    std::cout << bar << std::endl;
    std::cout << "over" << std::endl;
}

void test4()
{
    std::vector<std::string> names;
    std::vector<std::string> files;
    for (int i = 1; i <= 1500; i++) {
        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << i;
        names.push_back(ss.str());
        files.push_back("/test_data/" + ss.str());
        std::cout << ss.str() << std::endl;
    }
}

class ClassA
{
public:
    ClassA()
    {

    }
    ClassA(int id, char* name)
    {
        m_nId = id;
        m_pszName = new char[strlen(name) + 1];
        strcpy(m_pszName, name);
    }
    ~ClassA()
    {
        delete m_pszName;
        m_pszName = NULL;
    }
    //private:
    char* m_pszName;
    int m_nId;
};

void test5()
{
    cv::Mat a(100, 100, CV_8UC3, cv::Scalar(200, 200, 0));
    cv::Mat b(100, 101, CV_8UC3, cv::Scalar(200, 200, 0));
    std::cout << (a.size == b.size) << std::endl;
    std::cout << a << std::endl;
}

void test6()
{
    Mat test_image(200, 200, CV_8UC3, Scalar(0));
    RotatedRect rRect1 = RotatedRect(Point2f(100,100), Size2f(100,50), 75);
    RotatedRect rRect2 = RotatedRect(Point2f(80, 80), Size2f(100, 50), 75);
    //    RotatedRect rRect = rRect1 & rRect2;
    Point2f vertices[4];
    rRect1.points(vertices);
    for (int i = 0; i < 4; i++)
    {
        line(test_image, vertices[i], vertices[(i+1)%4], Scalar(255, 0, 0));
    }
    rRect2.points(vertices);
    for (int i = 0; i < 4; i++)
    {
        line(test_image, vertices[i], vertices[(i+1)%4], Scalar(255, 0, 0));
    }
    //    rRect.points(vertices);
    //    for (int i = 0; i < 4; i++)
    //    {
    //        line(test_image, vertices[i], vertices[(i+1)%4], Scalar(255, 0, 0));
    //    }
    Rect rect1 = rRect1.boundingRect();
    rectangle(test_image, rect1, Scalar(0, 0, 255));
    Rect rect2 = rRect2.boundingRect();
    rectangle(test_image, rect2, Scalar(0, 0, 255));
    Rect rect_1 = rect1 | rect2;
    rectangle(test_image, rect_1, Scalar(0, 255, 0));
    Rect rect_2 = rect1 & rect2;
    rectangle(test_image, rect_2, Scalar(0, 255, 0));
    imshow("test", test_image);
    std::cout << rect_1.size() << " " << rect_2.size() << std::endl;
    std::cout << rect_1.area() / rect_2.area() << std::endl;
    waitKey();
}

void test7()
{
    cv::Mat img(1000, 800, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::line(img, cv::Point(50, 100), cv::Point(500, 700), cv::Scalar(0));
    cv::line(img, cv::Point(500, 700), cv::Point(500, 400), cv::Scalar(0, 0, 255));
    cv::imshow("test", img);
    cv::waitKey();
}

void test8()
{
    cv::Mat img = cv::imread("/home/chenlei/Desktop/thtf/test_data/0001.jpg");
    int num = 0;
    for (int row = 0; row < img.rows; row++)
    {
        uchar *data = img.ptr(row);
        for(int col = 0; col < img.cols*3; col++)
        {
            //            std::cout << int(data[col]) << ", ";
            num ++;
        }
    }
    std::cout << int(img.data[img.cols*3*(img.rows-1) + img.cols*3-1]) << std::endl;
    std::cout << int(img.data[img.cols*3*(img.rows-1) + img.cols*3-100]) << std::endl;
    //    std::cout << std::endl << img << std::endl;
    std::cout << "row = " << img.rows << ", col = " << img.cols << ", dim = " << img.dims << std::endl;
    std::cout << "num = " << num << std::endl;
}

void test9()
{
    cv::Mat img1 = cv::imread("/home/chenlei/Desktop/thtf/test_data/0010.jpg");
    cv::Mat img2 = cv::imread("/home/chenlei/Desktop/thtf/test_data/0011.jpg");
    cv::Rect intersection(735, 232, 427, 68);
    int dist = 0;
    int sum = 0;
    for (int row = intersection.y; row <= intersection.y+intersection.height; row++)
    {
        uchar *pre_data = img1.ptr(row);
        uchar *now_data = img2.ptr(row);
        for (int col = intersection.x*3; col <= (intersection.x+intersection.width)*3; col++)
        {
            dist += std::abs(pre_data[col] - now_data[col]);
            sum++;
        }
    }
    // get the average of frame distance of intersection part
    double aver = dist / ((intersection.height + 1) * (intersection.width*3 + 1));
    std::cout << "******intersection: x = " << intersection.x << ", y = " << intersection.y << ", width = " << intersection.width << ", height = " << intersection.height << std::endl;
    std::cout << "previous image = " << ", current image = " << ", aver dist = " << aver << std::endl;
    std::cout << "dist = " << dist << ", num = " << (intersection.height + 1) * (intersection.width*3 + 1) << std::endl;
    std::cout << "actual sum = " << sum << std::endl;
}

void test10()
{
    std::vector<std::string> a = {"abc", "def", "hig"};
    std::vector<std::string>::iterator iter = a.begin();
    for (; iter <= a.end(); ++iter)
    {
        if (*iter == "def")
        {
            a.erase(iter);
        }
        if (iter != a.end())
        {
            std::cout << *iter << std::endl;
        }
        else
        {
            std::cout << "hahaha" << std::endl;
        }
    }
    std::cout << "size: " << a.size() << std::endl;
    std::cout << "END" << std::endl;
}

void test11()
{
    std::string s = "hello";
    std::wstring ws = Utf82Unicode(s);
    //    std::cout << ws << std::endl;
    std::cout << wstring_2_string(ws) << std::endl;
}

void test12_multi_thread()
{
    std::cout << thread::hardware_concurrency() << std::endl;
    thread task01(thread01);
    thread task02(thread02);
    std::cout << "main id: " << std::this_thread::get_id() << std::endl;
    std::cout << "thread01: " << task01.get_id() << std::endl;
    std::cout << "thread02: " << task02.get_id() << std::endl;
    std::cout << "begin!!!" << std::endl;
    task01.join();
    task02.join();


    for (int i = 0; i < 5; i++)
    {
        cout << "Main thread is working ！" << endl;
        sleep(1);
    }
    exit(0);

}

void test13()
{
    int a = 10;
    int b[a];
    for (int i = 0; i < a; i++) {
        b[i] = i;
        std::cout << b[i] << std::endl;
    }
}

// for memcheck
void test14()
{
    char *p;

    char c = *p;

    printf("\n [%c]\n",c);
}

void test15()
{
    char *p = (char *)malloc(sizeof(char));
    *p = 'a'; 

    char c = *p; 

    printf("\n [%c]\n",c); 

    free(p);
    c = *p;
}

void test16()
{
    std::map<int, std::string> m;
    m[1] = "include";
    m[4] = "haha";
    std::map<int, std::string>::iterator iter = m.find(4);
    if (iter != m.end()) {
        m.erase(iter);
    }
    for (std::map<int, std::string>::iterator iter = m.begin(); iter != m.end(); iter++) {
        std::cout << iter->first << ", " << iter->second << std::endl;
    }
    std::string a = m[2];
    if (a == "")
        std::cout << "can't find!" << std::endl;
    else
        std::cout << a << std::endl;
    if (m.find(5) == m.end()) {
        std::cout << "There isn't m[5]" << std::endl;
    }
    auto i = m.find(1);
    std::cout << i->first << ", " << i->second << std::endl;
}

void test17()
{
    std::string path = "/home/chenlei/Desktop/234456.txt";
    std::cout << path.length() << ", " << path.npos << std::endl;
    std::cout << path.rfind('/') << std::endl;
    std::cout << path.rfind('\\') << std::endl;
    int a = path.rfind('/');
    int b = path.rfind('.');
    std::string c;
    c.assign(path, a+1, b-a-1);
    std::cout << c << std::endl;
    std::string d = "1";
    d = (d == "") ? c : d;
    std::cout << d << std::endl;
}

void test18()
{
    KMP kmp;
    String a = "aba";
    String b = "ssdfgasdbababa";
    int next[a.length()];
    kmp.getNext(a, next);
    bool res = kmp.match(b, a, next);
    std::cout << res << std::endl;
}

void test19()
{
    main_();
}

void test20()
{
    AC_Tree ac;
//    ac.insert(L"say");
//    ac.insert(L"she");
//    ac.insert(L"shr");
//    ac.insert(L"he");
//    ac.insert(L"her");
//    ac.build_ac_automation();
//    std::vector<std::wstring> res = ac.parse_text(L"yasherhs");
    std::vector<std::wstring> words = {L"好的", L"哈哈", L"小心", L"good", L"千万别翻车了"};
    std::wstring text = L"Very Good! 哈哈，好的，小心点，千万别再翻车了。";
    for (size_t i = 0; i < words.size(); i++)
        ac.insert(words[i]);
    ac.build_ac_automation();
    std::vector<std::wstring> res = ac.parse_text(text);
    for (size_t i = 0; i < res.size(); i++)
//        std::wcout << res[i].c_str() << std::endl; // 中文乱码
        std::cout << wstring_2_string(res[i]) << std::endl;
}

void test21()
{
    std::wstring w = L"";
    std::wstring a = L"好的";
    w += a[1];
    std::wcout << w << std::endl;
    std::wcout << a << std::endl;
}

int main()
{
    //    test12_multi_thread();
    test20();
    return 0;
}
