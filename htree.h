#include<string>
#include<unordered_map>
#define pb push_back

#ifndef WORK3_HTREE_H
#define WORK3_HTREE_H
struct treenode{
    char ch;
    int weight{};
    treenode* lson{};
    treenode* rson{};
    treenode* par{};
    treenode* addr{};
    treenode(){
        ch = 0;
        lson = nullptr;
        rson = nullptr;
    }
    treenode(char c) {
        ch = c;
        lson = nullptr;
        rson = nullptr;
    }
    bool operator<(const treenode& a) const{
        if(weight == a.weight) return ch > a.ch;
        return weight > a.weight;
    }
};


class h_tree{
private:
    int frequency[300]{};
    int n;
    treenode* root;
    treenode* body;
public:
    h_tree(){
        root = NULL;
        body = NULL;
        n = 0;
        memset(frequency, sizeof(frequency), 0);
    }

    int size(){ return n; }
    treenode* find_root() { return root; }
    treenode* find_node(int i) { return body + i; }


    void build();
    std::string decode(const std::string& s);
    void statistic(const std::string& s);
};

class h_code{
private:
    //std::unordered_map<char, std::string> dic;
public:
    std::unordered_map<char, std::string> dic;
    static void find(h_tree h, int s, std::string& aws);
    void build(h_tree h);
};
#endif //WORK3_HTREE_H