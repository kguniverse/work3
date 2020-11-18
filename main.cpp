#include<bits/stdc++.h>
using namespace std;
#define pb push_back

struct treenode{
    char ch;
    int weight;
    treenode* lson;
    treenode* rson;
    treenode* par;
    treenode(){
        ch = 0;
        lson = NULL;
        rson = NULL;
    }
    treenode(char c, int w){
        ch = c;
        lson = NULL;
        rson = NULL;
    }
    bool operator<(const treenode& a){
        if(weight == a.weight) return ch > a.ch;
        return weight > a.weight;
    }
};
map<char, string> dic;
class h_tree{
    private:
    int frequency[30];
    int n;
    treenode* root;
    treenode* body;
    bool in_tree[130];
    public:
    h_tree(){
        body = (treenode*)malloc(sizeof(treenode) * (n + 1));
        memset(in_tree, sizeof(in_tree), true);
    }
    void build(){
        priority_queue<treenode*> q;
        for(int i = 1; i <= n; i++){
            q.push(body + i);
        }
        while(1){
            treenode *s1, *s2;
            if(!q.empty()){
                s1 = q.top();
                q.pop();
            }
            if(!q.empty()){
                s2 = q.top();
                q.pop();
            } else{
                root = s1;
                break;
            }
            treenode* s0 = (treenode*)malloc(sizeof(treenode));
            s0 -> ch = 0;
            s0 -> lson = s1;
            s0 -> rson = s2;
            s1 -> par = s0;
            s2 -> par = s0;
            s0 -> weight = s1 -> weight + s2 -> weight;
            q.push(s0);
        }
    }
    string decode(string s){
        string ret;
        treenode* rec = root;
        for(auto i : s){
            if(i == '1'){
                rec = rec -> rson;
            } else{
                rec = rec -> lson;
            }
            if(rec -> ch){
                ret.pb(rec->ch);
                rec = root;
            }
        }
        return ret;
    }
    void stistic(string s){
        cout << "please input size:" << endl;
        cin >> n;
        for(auto i : s){
            root[i - 'a' + 1].weight++;
        }
    }
};
class h_code{
    public:
    map<char, string> dic;

};

string read(){
    string ret;
    ifstream txtin("a.txt");
    if(!txtin.is_open()) cout << "未能打开文件" << endl;
    getline(txtin, ret);
    while(!txtin.eof()){
        string cd;
        getline(txtin, cd);
        ret = ret + '\n' + cd;
    }
    return ret;
}
//TODO: prepare search function
int main(){
    string readin = read();
    h_tree h;
    
    h.build();

}
