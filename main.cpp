#include<bits/stdc++.h>
#include"htree.h"
#include"BM.h"
using namespace std;
#define pb push_back

string read(){
    string ret;
    ifstream txtin;
    txtin.open("a.txt", ios::in);
    if(!txtin.is_open()) {
        cout << "未能打开文件" << endl;
        return ret;
    }
    getline(txtin, ret);
    //cout << ret << endl;
    while(!txtin.eof()){
        string cd;
        getline(txtin, cd);
        ret += '\n' + cd;
    }
    return ret;
}
//TODO: prepare search function
void encode(){
    string readin = read();
    cout << readin << endl;
    h_tree h;
    h.statistic(readin);
    h.build();
    h_code H_table;
    H_table.build(h);
    for(int i = 1; i <= 255; i++) cout << i << ":::" << H_table.dic[i] << endl;

}
void decode(){
    string readin = read();

}
void start(){
    int t;
    printf("what do you want to do with your text?\n");
    printf("1. I want to encode this\n");
    printf("2. I want to decode this\n");
    printf("3. quit\n");
    printf("please select:");

    cin >> t;
    if(t == 1){
        encode();
    } else if(t == 2){
        decode();
    } else if(t == 3){
        printf("thank you for using this system");
        exit(0);
    }
    else{
        printf("no such option, please select again!");
        return;
    }
}
int main(){
    while(true) start();
}