#include<bits/stdc++.h>
#include"htree.h"
using namespace std;
#define pb push_back

string read(){
    string ret;
    ifstream txtin("a.txt");
    if(!txtin.is_open()) cout << "未能打开文件" << endl;
    getline(txtin, ret, '\n');
    while(!txtin.eof()){
        string cd;
        getline(txtin, cd);
        ret += '\n' + cd;
    }
    return ret;
}
//TODO: prepare search function


int main(){
    string readin = read();
    int n;
    cin >> n;
    h_tree h;
    h.stistic(readin);
    h.build();
    h_code H_table;
    H_table.build(h);
}