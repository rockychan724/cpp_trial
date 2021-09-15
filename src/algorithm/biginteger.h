#ifndef BIGINTEGER_H
#define BIGINTEGER_H


#include "bits/stdc++.h"

using namespace std;

class BigInteger {
public:
    string n;

    BigInteger() {
        this->n = "0";
    }

    BigInteger(string n) {
        this->n = n;
    }

    BigInteger(int n) {
        this->n = to_string(n);
    }

    ~BigInteger() {

    }

    BigInteger operator+(BigInteger num2) {
        string res = this->addition(this->n, num2.n);
        return BigInteger(res);
    }

    BigInteger operator-(BigInteger num2) {
        string res = this->substract(this->n, num2.n);
        return BigInteger(res);
    }

    BigInteger operator*(BigInteger num2) {
        string res = this->multiply(this->n, num2.n);
        return BigInteger(res);
    }

    // 整除
    BigInteger operator/(BigInteger num2) {
        string res = this->divide(this->n, num2.n);
        return BigInteger(res);
    }

    // 幂运算
    BigInteger operator^(BigInteger num2) {
        string res = "1";
        for (string i = "0"; this->compare(i, num2.n) < 0; i = this->addition(i, "1")) {
            res = this->multiply(res, this->n);
        }
        return BigInteger(res);
    }

    // 取余
    BigInteger operator%(BigInteger num2) {
        int i = 0;
        string num1 = this->n;
        if (this->compare(num1, num2.n) < 0) {
            return num1;
        }
//            num1 = this->substract(num1, this->multiply(num2.n, (*this / num2)));
        string f = this->divide(num1, num2.n);
        num1 = this->substract(num1, this->multiply(num2.n, f));
        if (num1 == "")
            return BigInteger("0");
        return BigInteger(num1);
    }

//    // 赋值
//    BigInteger operator=(BigInteger num2) {
//        this->n = num2.n;
//        return *this;
//    }

    // 等于
    bool operator==(BigInteger num2) {
        if (this->compare(this->n, num2.n) == 0) return true;
        else return false;
    }

    bool operator!=(BigInteger num2) {
        return !(*this == num2);
    }

    bool operator>(BigInteger num2) {
        if (this->compare(this->n, num2.n) > 0) return true;
        else return false;
    }

    bool operator<(BigInteger num2) {
        if (this->compare(this->n, num2.n) < 0) return true;
        else return false;
    }

    // 输出
    friend ostream &operator<<(ostream &os, BigInteger num2) {
        os << num2.n;
        return os;
    }

    // 输入
    friend istream &operator>>(istream &is, BigInteger &num2) {
        is >> num2.n;
        return is;
    }

    string addition(string nums1, string nums2) //两数相加
    {
        int n1 = nums1.size();
        int n2 = nums2.size();
        //便于操作，统一转换为长数加短数
        if (n1 < n2)
            return addition(nums2, nums1);

        int maxlen = n1;
        int minlen = n2;
        string result;
        int carry = 0;
        for (int i = 0; i < minlen; i++) {
            int sum = nums1[--n1] - '0' + nums2[--n2] - '0' + carry;
            carry = sum / 10;
            int a = sum % 10;
            result.push_back(a + '0');
        }
        for (int i = minlen; i < maxlen; i++) {
            int sum = nums1[--n1] - '0' + carry;
            carry = sum / 10;
            int a = sum % 10;
            result.push_back(a + '0');
        }

        if (carry != 0)
            result.push_back(carry + '0');

        reverse(result.begin(), result.end());
        return result;
    }

    string substract(string nums1, string nums2) {
        string result;
        int n1 = nums1.size();
        int n2 = nums2.size();

        //判断符号为正负
        char sign = '+';
        if (n1 < n2) {
            sign = '-';
            nums1.swap(nums2);

        } else if (n1 == n2) {
            for (int i = 0; i < n1; i++) {
                if (nums1[i] > nums2[i]) {
                    break;
                } else if (nums1[i] < nums2[i]) {
                    sign = '-';
                    nums1.swap(nums2);
                    break;
                }
            }
        }
        int borrow = 0;
        reverse(nums1.begin(), nums1.end());
        reverse(nums2.begin(), nums2.end());

        n1 = nums1.size();
        n2 = nums2.size();

        for (int i = 0; i < n2; i++) {
            int temp = nums1[i] - nums2[i] - borrow;
            borrow = 0;
            if (temp < 0) {
                temp = temp + 10;
                borrow = 1;
            }
            result.push_back(temp + '0');
        }

        for (int i = n2; i < n1; i++) {
            int r = nums1[i] - '0' - borrow;
            borrow = 0;
            if (r < 0) {
                r = r + 10;
                borrow = 1;
            }
            result.push_back(r + '0');
        }

        for (int i = n1 - 1; i >= 0; i--) {
            if (result[i] == '0')
                result.erase(result.begin() + i);
            else
                break;
        }
        reverse(result.begin(), result.end());
        if (sign == '-') {
            result.insert(result.begin(), '-');
        }
        /* if(result=="")
             result="0";*/
        return result;
    }

    string multiply(string nums1, string nums2) {
        string result = "0";
        if (nums1 == "0" || nums2 == "0")
            return result;

        vector<string> tmpResult;
        int n1 = nums1.size();
        int n2 = nums2.size();

        int carry = 0;
        reverse(nums1.begin(), nums1.end());
        reverse(nums2.begin(), nums2.end());

        for (int i = 0; i < n1; i++) {
            string str;
            for (int j = 0; j < n2; j++) {
                int sum = (nums1[i] - '0') * (nums2[j] - '0') + carry;
                carry = sum / 10;
                int a = sum - carry * 10;
                str.push_back(a + '0');
            }
            if (carry != 0)
                str.push_back(carry + '0');
            carry = 0;
            reverse(str.begin(), str.end());
            for (int k = 0; k < i; k++) {
                str.push_back('0');
            }
            tmpResult.push_back(str);
        }

        int size = tmpResult.size();

        for (int i = 0; i < size; i++) {
            result = addition(result, tmpResult[i]);
        }
        return result;
    }

    string divide(string nums1, string nums2) {
        string result;
        result = substract(nums1, nums2);
        if (result[0] == '-') {
            result = "0";
            return result;
        }
        result = "";
        int n1 = nums1.size();

        //stringstream stream;
        string dividend;

        for (int j = 0; j < n1; j++) {
            dividend.push_back(nums1[j]); //被除数
            //从9到0，试探性的找商，当余数不为负数时，为当前位的值
            for (int i = 9; i >= 0; i--) {
                //stream.str(""); //清空stream
                //stream << i;
                string s = to_string(i);
                string ss = multiply(nums2, s);
                string remain = substract(dividend, ss);

                if (remain[0] != '-') {
                    result.push_back(i + '0');
                    dividend = remain;
                    break;
                }
            }
        }
        //去掉商前面的零位
        int size = result.size();
        for (int i = 0; i < size; i++) {
            if (result[0] == '0') {
                result.erase(result.begin());
            } else {
                break;
            }
        }
        //四舍五入
        // cout<<dividend<<endl;
        /*
         string s = substract(multiply(dividend,"2"),nums2);
         if(s[0] != '-')
             {
                 result=addition(result,"1");
                 //printf("1\n");
             }
         //printf("%s\n",dividend);
         */

        return result;
    }

    int compare(string str1, string str2, int pos) {
        int len1 = str1.length();
        int len2 = str2.length();
        if (len2 > len1 + pos) return 0;
        if (len2 < len1 + pos) return 1;
        int i;
        for (i = 0; i < len2; i++) {
            if (str1[i] > str2[i]) return 1;
            if (str1[i] < str2[i]) return 0;
        }
        return 0;
    }

    string sqrtlarge(string str)        //大数开方
    {
        int len = str.length();
        string str1 = "";
        string strresult = "";
        int i, j;

        if (len % 2 == 0) {
            for (i = 0; i < len / 2; i++)
                for (j = 0; j < 10; j++) {
                    str1 = strresult;
                    str1 += (j + '0');
                    if (compare(multiply(str1, str1), str, 2 * (len / 2 - i - 1)) == 1) {
                        strresult += (j - 1 + '0');
                        break;
                    }
                    if (j == 9) strresult += '9';
                }
        } else {
            for (i = 0; i < len / 2 + 1; i++)
                for (j = 0; j < 10; j++) {
                    str1 = strresult;
                    str1 += (j + '0');
                    if (compare(multiply(str1, str1), str, 2 * (len / 2 - i)) == 1) {
                        strresult += (j - 1 + '0');
                        break;
                    }
                    if (j == 9) strresult += '9';
                }
        }
        return strresult;
    }

    // a < b return -1; a > b return 1; a == b return 0
    int compare(string a, string b) {
        assert(a.length() > 0 && b.length() > 0);
        while (a[0] == '0' && a.length() > 1) {
            a.erase(a.begin());
        }
        while (b[0] == '0' && b.length() > 1) {
            b.erase(b.begin());
        }
        if (a.length() < b.length()) {
            return -1;
        } else if (a.length() > b.length()) {
            return 1;
        } else {
            for (int i = 0; i < a.length(); i++) {
                if (a[i] < b[i]) {
                    return -1;
                } else if (a[i] > b[i]) {
                    return 1;
                }
            }
            return 0;
        }
    }


};

#define ll BigInteger

ll zero("0");
ll one("1");
ll two("2");
ll three("3");

// 快速乘法
ll mul(ll a, ll b, ll m)
//求a*b%m
{
    ll ans = zero;
    a = a % m;
    while (b > zero) {
        if ((b % two) == one) // 判断奇偶性
            ans = (ans + a) % m;
        b = b / two;
        a = (a + a) % m;
    }
    return ans;
}

// 快速幂运算
ll pow(ll a, ll b, ll m)
//求a^b % m
{
    ll ans = one;
    a = a % m;
    while (b > zero) {
        if ((b % two) == one)
            ans = mul(a, ans, m);
        b = b / two;
        a = mul(a, a, m);
    }
    ans = ans % m;
    return ans;
}

bool Miller_Rabin(ll n, int repeat)//n是测试的大数，repeat是测试重复次数
{
    if (n < two) return false;
    if (n == two || n == three)return true;//特判
    if (n % two == zero || n % three == zero)return false;//偶数和1

    //将n-1分解成d*2^s
    ll d = n - one;
    ll s = zero;
    while ((d % two) == zero) s = s + one, d = d / two;
    srand((unsigned) time(NULL));
    for (int i = 0; i < repeat; i++)//重复repeat次
    {
        BigInteger r(rand());
        ll a = r % (n - three) + two;//取一个随机数,[2,n-1)
        ll x = pow(a, d, n);
        ll y = 0;
        for (ll j = 0; j < s; j = j + 1) {
            y = mul(x, x, n);
            if (y == one && x != one && x != (n - one)) return false;
            x = y;
        }
        if (y != 1) return false;//费马小定理
    }
    return true;
}

void test() {
    BigInteger a("11111111111111111111111111111111");
    BigInteger b("2");
    cout << (a * b) << endl;
    BigInteger c("22222222222222222222222222222222");
    BigInteger d("4");
    cout << (c / d) << endl;

    string str[] = {"2", "3", "5", "9", "13"};
    for (int i = 0; i < 5; i++) {
        if (Miller_Rabin(BigInteger(str[i]), 5)) {
            cout << str[i] << " is prime." << endl;
        } else {
            cout << str[i] << " is not prime." << endl;
        }
    }
    BigInteger n;
    while (true) {
        cin >> n;
        if (Miller_Rabin(n, 10)) {
            cout << n << " is prime." << endl;
        } else {
            cout << n << " is not prime." << endl;
        }
    }
}

#endif // BIGINTEGER_H
