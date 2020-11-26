//
// Created by 王乾凱 on 2020/11/24.
//
#include <string>
#include <vector>
#ifndef WORK3_AC_AUTOMATON_H
#define WORK3_AC_AUTOMATON_H
#define maxn 1000000
class AC{
private:
    int tot{}; // 计数器
    int tr[maxn][2]{}; // trie主体
    int fail[maxn]{}, e[maxn]{}, idx[maxn]{}; //失配指针，访问标记，串的编号
    std::string book[maxn]; //trie中串的索引。
    std::vector<int> dic[maxn]; //每个节点所对应的串的编号。
public:
    AC() = default;
    void insert(std::string w, int t);
    void build();
    std::vector<std::vector<int>> query(std::string t);

};
#endif //WORK3_AC_AUTOMATON_H
