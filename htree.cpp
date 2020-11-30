//
// Created by 王乾凱 on 2020/11/19.
//
#include<bits/stdc++.h>
#include"htree.h"
using namespace std;
#define pb push_back

void h_tree::build(){
    priority_queue<treenode> q;
    for(int i = 1; i <= n; i++){q.push(*(body + i));}
    while(true){
        treenode s1, s2;
        if(!q.empty()){
            s1 = q.top();
            q.pop();
        }
        if(!q.empty()){
            s2 = q.top();
            q.pop();
        } else{
            root = s1.addr;
            break;
        }
        //cout << (int)s1.ch << "  " << s1.weight << endl << (int)s2 . ch << "  " << s2.weight << endl << endl;
        auto* s0 = (treenode*)malloc(sizeof(treenode));
        s0 -> ch = 0;
        s0 -> lson = s1.addr;
        s0 -> rson = s2.addr;
        s0 -> lson -> par = s0;
        s0 -> rson -> par = s0;
        s0 -> weight = s1.weight + s2.weight;
        s0 -> addr = s0;
        q.push(*s0);
    }
}
string h_tree::decode(const string& s){
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
void h_tree::statistic(const string& s){
    int t = 0;
    for(auto i : s){
        if(!frequency[i]) t++;
        frequency[i]++;
    }
    n = 255;
    body = (treenode*)malloc(sizeof(treenode) * (n + 1));
    for(int i = 1; i <= n; i++){
        (body + i) -> ch = (char)i;
        // (body + i) -> weight = frequency[i];
        (body + i) -> lson = nullptr;
        (body + i) -> rson = nullptr;
        (body + i) -> par = nullptr;
        (body + i) -> addr = (body + i);
        body[i].weight = frequency[i];
    }
}
void h_code::find(h_tree h, int s, string& aws){
    treenode* rec = h.find_node(s);
    treenode* root = h.find_root();
    while(rec != root){
        treenode* p = rec -> par;
        if(p -> lson == rec){
            aws.pb('0');
        } else {
            aws.pb('1');
        }
        rec = p;
    }
}
void h_code::build(h_tree h){
    for(int i = 1; i <= h.size(); i++){
        std::string aws;
        find(h, i, aws);
        aws.reserve();
        dic[h.find_node(i) -> ch] = aws;
    }
}
std::string h_code::encode(const std::string& s){
    string aws;
    for(auto i : s){
        aws += dic[i];
    }
    return aws;
}