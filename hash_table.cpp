#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_set>
class Item;
using ItemPtr = std::shared_ptr<Item>;
using ConstItemPtr = std::shared_ptr<const Item>;

class Item {
   public:
    Item(const std::string& d = "null") : data(d) {}
    std::string data;
};

struct Hash {
    size_t operator()(const ConstItemPtr& x) const {
        return std::hash<std::string>()(x->data);
    }
};

struct Equal {
    bool operator()(const ConstItemPtr& x, const ConstItemPtr& y) const {
        return x->data == y->data;
    }
};
// 不管是unordered_set还是unordered_map内部的数据结构都是hashtable
// hashtable适用于查找效率要求比较高的场景
// 在使用时，我们需要定义两个关键的函数对象
// 1. hash函数，它帮助我们确定hashtable中桶的位置
// 2. equal函数，hashtable中可能存在冲突的情况，
// 比如一个桶中对应多个值，那么就需要使用equal来确定
using ItemMap = std::unordered_set<ConstItemPtr, Hash, Equal>;

int main(int argc, char const* argv[]) {
    ItemPtr it1(new Item("hello"));
    ItemPtr it2(new Item("world"));
    ItemPtr it3(new Item("aoeiuv"));
    ItemMap items;
    items.insert(it1);
    items.insert(it2);
    items.insert(it3);
    for (auto& it : items) {
        std::cout << it->data << std::endl;
    }
    return 0;
}

/*  测试
PS E:\4 Code\demo_cpp\common> g++ -std=c++11 .\hash_table.cpp -o .\hash_table
PS E:\4 Code\demo_cpp\common> .\hash_table.exe
aoeiuv
hello
world
*/