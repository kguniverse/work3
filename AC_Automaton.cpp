//
// Created by 王乾凱 on 2020/11/24.
//

#include "AC_Automaton.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; i++)

void AC::insert(string w, int t){
    int u = 0;
    for(int i = 0; w[i]; i++){
        if(!tr[u][w[i] - 'a']) tr[u][w[i] - 'a'] = ++tot;
        u = tr[u][w[i] - 'a'];
    }
//    e[u]++;
    idx[t] = u;
    dic[u].push_back(t);
}
void AC::build(){
    queue<int> q;
    rep(i, 0, 25) if(tr[0][i]) q.push(tr[0][i]);
    while(!q.empty()){
        int u = q.front(); q.pop();
        rep(i, 0, 25){
            if(tr[u][i]){
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            } else{
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}
vector<vector<int>> AC::query(string t){
    int u = 0;
    vector<vector<int>> res(tot + 10);
    for(int i = 0; t[i]; i++){
        u = tr[u][t[i] - 'a'];
        for(int j = u; j && e[j] != -1; j = fail[j]){
            //res += e[j]; e[j] = -1;
            e[j] = -1;
            for(auto w : dic[j]) res[w].push_back(j); //记录答案
        }
    }
    return res; //答案为每个匹配串的尾节点
}
