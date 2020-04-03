#ifndef AC_TREE_H
#define AC_TREE_H

#include <iostream>
#include <memory>
#include <map>
#include <queue>
#include <vector>

class AC_Tree
{
private:
    struct Node
    {
        std::wstring wstr; // 记录从根节点到当前节点的路径构成的字符序列
        int count; // 记录当前节点是否构成一个词语
        std::map<wchar_t, std::shared_ptr<Node>> next;
        std::shared_ptr<Node> fail; // 失配指针
    };
    std::queue<std::shared_ptr<Node>> nodes_queue; // 节点队列，用于构造各个节点的失配指针
    std::shared_ptr<Node> root; // 头结点

    void init_node(std::shared_ptr<Node> node);
public:
    AC_Tree();

    void insert(std::wstring word);

    void build_ac_automation();

    std::vector<std::wstring> parse_text(std::wstring text);
};

#endif // AC_TREE_H
