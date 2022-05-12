#include <map>
#include <set>
#include <mutex>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <typeinfo>
#include <algorithm>

using namespace std;

/*
* 以下宏用来定义需要反射的类成员
*/
#define reflect_attr(type, name)    \
type name;                            \
const ReflectHelper __##name = ReflectHelper(this, &this->name, #type, #name)

#define reflect_int(name) reflect_attr(int, name)
#define reflect_bool(name) reflect_attr(bool, name)
#define reflect_float(name) reflect_attr(float, name)
#define reflect_double(name) reflect_attr(double, name)
#define reflect_string(name) reflect_attr(string, name)

/*
* 反射Object基类
* 所有需要反射的类建议继承Object类
* 提供getClassName方法用于在运行时获取对象的真实类名称
*/
class Object {
public:
    virtual ~Object() {
    }

    virtual string toString() const {
        char buffer[16];

        sprintf(buffer, "%p", this);

        return buffer;
    }

public:
    //用于在运行时获取对象的真实类名称
    virtual string getClassName() const {
#ifdef _MSC_VER
        return typeid(*this).name() + 6;
#else
        const char *name = typeid(*this).name();

        while (*name >= '0' && *name <= '9') name++;

        return name;
#endif
    }
};

/*
* 反射属性操作类
* set方法用于修改属性
* get方法用于获取属性
*/
class ReflectItem {
protected:
    int offset;
    string name;
    const char *type;


public:
    ReflectItem() : offset(0), type(NULL) {
    }

    ReflectItem(int _offset, const char *_type, const string &_name) : offset(_offset), type(_type), name(_name) {
    }

public:
    bool canUse() const {
        return type ? true : false;
    }

    bool operator<(const ReflectItem &obj) const {
        return name < obj.name;
    }

    bool operator==(const ReflectItem &obj) const {
        return name == obj.name;
    }

public:
    //获取成员的偏移地址
    int getOffset() const {
        return offset;
    }

    //获取成员名称
    string getName() const {
        return type ? name : "";
    }

    //获取成员类型
    string getType() const {
        return type ? type : "";
    }

    //获取成员的值
    string get(const void *obj) const {
        char *dest = (char *) (obj) + offset;

        if (type == NULL || type == "object") "";

        if (type == "int") return to_string(*(int *) (dest));

        if (type == "bool") return *(bool *) (dest) ? "true" : "false";

        if (type == "float") return to_string(*(float *) (dest));

        if (type == "double") return to_string(*(double *) (dest));

        return *(string *) (dest);
    }

    //修改成员的值
    bool set(void *obj, int val) const {
        char *dest = (char *) (obj) + offset;

        if (type == NULL || type == "object") return false;

        if (type == "int") {
            *(int *) (dest) = val;
        } else if (type == "bool") {
            *(bool *) (dest) = (val ? true : false);
        } else if (type == "float") {
            *(float *) (dest) = val;
        } else if (type == "double") {
            *(double *) (dest) = val;
        } else {
            *(string *) (dest) = to_string(val);
        }

        return true;
    }

    //修改成员的值
    bool set(void *obj, bool val) const {
        return set(obj, val ? 1 : 0);
    }

    //修改成员的值
    bool set(void *obj, float val) const {
        return set(obj, (double) (val));
    }

    //修改成员的值
    bool set(void *obj, double val) const {
        char *dest = (char *) (obj) + offset;

        if (type == NULL || type == "object") return false;

        if (type == "int") {
            *(int *) (dest) = val;
        } else if (type == "bool") {
            *(bool *) (dest) = val < -0.000001 || val > 0.000001;
        } else if (type == "float") {
            *(float *) (dest) = val;
        } else if (type == "double") {
            *(double *) (dest) = val;
        } else {
            *(string *) (dest) = to_string(val);
        }

        return true;
    }

    //修改成员的值
    bool set(void *obj, const char *val) const {
        char *dest = (char *) (obj) + offset;

        if (val == NULL || type == NULL || type == "object") return false;

        if (type == "string") {
            *(string *) (dest) = val;
        } else {
            if (*val == 0) return true;

            if (type == "int") {
                *(int *) (dest) = atoi(val);
            } else if (type == "bool") {
                string tmp = val;

                *(bool *) (dest) = (tmp == "true");
            } else if (type == "float") {
                *(float *) (dest) = atof(val);
            } else {
                *(double *) (dest) = atof(val);
            }
        }

        return true;
    }

    //修改成员的值
    bool set(void *obj, const string &val) const {
        return set(obj, val.c_str());
    }
};

/*
* 反射属性管理类
* 以map方式存储相关类成员变量的类型、偏移地址等信息
*/
class ReflectHelper {
protected:
    static mutex &GetMutex() {
        static mutex mtx;
        return mtx;
    }

    static map<string, set<ReflectItem>> &GetMap() {
        static map<string, set<ReflectItem>> map;
        return map;
    }

public:
    //通过构造函数将相关类成员的信息记录在反射信息map中
    ReflectHelper(Object *self, void *data, const char *type, const char *name) {
        static map<string, set<ReflectItem>> &attrmap = GetMap();

        lock_guard<mutex> lk(GetMutex());
        string key = self->getClassName();

        if (type == "int" || type == "bool" || type == "float" || type == "double" || type == "string") {
            attrmap[key].insert(ReflectItem((char *) (data) - (char *) (self), type, name));
        } else {
            attrmap[key].insert(ReflectItem((char *) (data) - (char *) (self), "object", name));
        }
    }

public:
    //根据类名称获取成员变量反射信息列表
    static vector<ReflectItem> GetList(const string &key) {
        static map<string, set<ReflectItem>> &attrmap = GetMap();

        vector<ReflectItem> vec;
        lock_guard<mutex> lk(GetMutex());

        auto it = attrmap.find(key);

        if (it == attrmap.end()) return {};

        for (auto &item : it->second) vec.push_back(item);

        std::sort(vec.begin(), vec.end(), [](const ReflectItem &a, const ReflectItem &b) {
            return a.getOffset() < b.getOffset();
        });

        return std::move(vec);
    }

    //获取指定类成员变量的反射信息
    static ReflectItem GetItem(const string &key, const string &name) {
        static map<string, set<ReflectItem>> &attrmap = GetMap();

        ReflectItem item(0, NULL, name);
        lock_guard<mutex> lk(GetMutex());

        auto it = attrmap.find(key);

        if (it == attrmap.end()) return item;

        auto tmp = it->second.find(item);

        if (tmp == it->second.end()) return item;

        return *tmp;
    }
};

class Json : public Object {
private:
    reflect_int(intval);
    reflect_bool(boolval);
    reflect_string(stringval);

public:
    //序列化为JSON串
    string toString() const {
        string msg;
        vector<ReflectItem> vec = ReflectHelper::GetList(this->getClassName());

        for (auto &item : vec) {
            if (item.getType() == "string") {
                msg += ",\"" + item.getName() + "\":\"" + item.get(this) + "\"";
            } else {
                msg += ",\"" + item.getName() + "\":" + item.get(this);
            }
        }

        if (msg.empty()) return "{}";

        return "{" + msg.substr(1) + "}";
    }
};

int main(int argc, char **argv) {
    Object *obj = new Json();

    vector<ReflectItem> vec = ReflectHelper::GetList(obj->getClassName());

    puts(" 类成员变量定义");
    puts("------------------------------------------------------");
    for (auto &item : vec) {
        cout << " " << item.getType() << " " << item.getName() << ";" << endl;
    }

    //设置成员变量的值
    ReflectHelper::GetItem("Json", "intval").set(obj, 100);
    ReflectHelper::GetItem("Json", "boolval").set(obj, true);
    ReflectHelper::GetItem("Json", "stringval").set(obj, "xungen");

    puts("");
    puts(" 成员变量的值");
    puts("------------------------------------------------------");
    for (auto &item : vec) {
        cout << " " << item.getName() << " = " << item.get(obj) << ";" << endl;
    }

    puts("");
    puts(" 序列化为JSON串");
    puts("------------------------------------------------------");
    cout << " " << obj->toString() << endl;

    delete obj;

    return 0;
}
