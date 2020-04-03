#include "ac_tree.h"

// init one node
void AC_Tree::init_node(std::shared_ptr<Node> node)
{
    node->wstr = L"";
    node->count = 0;
    node->next.clear();
    node->fail = nullptr;
}

std::wstring AC_Tree::case_transform(std::wstring src)
{
    std::wstring dest = src;
    for (size_t i = 0; i < dest.length(); i++)
    {
        if (int(dest[i]) >= 'A' && int(dest[i]) <= 'Z')
            dest[i] += 32;
    }
    return dest;
}

AC_Tree::AC_Tree()
{
    this->root.reset(new Node());
    this->init_node(this->root);
    this->case_sensitive = true;
}

void AC_Tree::case_insensitive()
{
    this->case_sensitive = false;
}

// insert a word into this tree
void AC_Tree::insert(std::wstring word)
{
    if (!this->case_sensitive)
        word = this->case_transform(word);
    std::shared_ptr<Node> temp = this->root;
    std::shared_ptr<Node> new_node;
    for (size_t i = 0; i < word.length(); i++)
    {
        if (temp->next.find(word[i]) == temp->next.end())
        {
            new_node.reset(new Node());
            this->init_node(new_node);
            temp->next[word[i]] = new_node;
            temp->next[word[i]]->wstr = temp->wstr + word[i];
        }
        temp = temp->next[word[i]];
    }
    temp->count++;
}

// use BFS algorithm to build all fail pointers in this tree
void AC_Tree::build_ac_automation()
{
    this->nodes_queue.push(this->root);
    while (!this->nodes_queue.empty())
    {
        std::shared_ptr<Node> temp = this->nodes_queue.front(); // 获取队头结点
        this->nodes_queue.pop();
        for (auto iter = temp->next.begin(); iter != temp->next.end(); iter++) // 遍历当前节点的所有子节点
        {
            wchar_t key = iter->first;
            std::shared_ptr<Node> value = iter->second;
            if (temp == this->root)
                value->fail = this->root; // 若是第一层中的节点，则把节点的失配指针指向root
            else
            {
                std::shared_ptr<Node> p = temp->fail;
                while (p != nullptr)
                {
                    if (p->next.find(key) != p->next.end())
                    {
                        value->fail = p->next[key];
                        break;
                    }
                    p = p->fail;
                }
                if (p == nullptr)
                    value->fail = this->root;
            }
            this->nodes_queue.push(iter->second); // 将当前节点temp的各个子节点加入队列
        }
    }
}

std::vector<std::wstring> AC_Tree::parse_text(std::wstring text)
{
    if (!this->case_sensitive)
        text = this->case_transform(text);
//    int total = 0;
    std::vector<std::wstring> result;
    std::shared_ptr<Node> p = this->root;
    for (size_t i = 0; i < text.length(); i++)
    {
        wchar_t key = text[i];
        while (p->next.find(key)==p->next.end() && p!=this->root)
            p = p->fail;
        if (p->next.find(key) == p->next.end())
            p = this->root;
        else
            p = p->next[key];
        std::shared_ptr<Node> temp = p;
        while (temp != this->root)
        {
            if (temp->count > 0)
            {
//                total += temp->count;
//                if (temp->count > 0)
                result.push_back(temp->wstr);
//                temp->count = -1;
            }
            else break;
            temp = temp->fail;
        }
    }
    return result;
}
