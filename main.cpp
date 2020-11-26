#include<bits/stdc++.h>
#include"htree.h"
#include"BM.h"
#include"AC_Automaton.h"
using namespace std;
#define pb push_back

string read(){
    string ret, path;
    ifstream txtin;
    cout << "please write the input path\n";
    cin >> path;
    txtin.open(path, ios::in);
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
void write(const string& s){
    ofstream txtout;
    string path, s1;
    int t = 0;
    while(t <= s.size()){
        int i = 0, temp = 0;
        while(i < 8){
            temp += s[t] - '0';
            i++;
            t++;
        }
        s1.pb((char)temp);
    }
    cout << "please write the output path\n";
    cin >> path;
    txtout.open("a1.dat", ios::out|ios::binary);
    if(!txtout.is_open()) {
        cout << "未能打开文件2" << endl;
        return;
    }
    //for(auto i : s) txtout << i - '0';
    txtout.write((char*)&s1[0], s.size());
}
//TODO: prepare search function
void search(h_code table, const string& txt){

    printf("which mode do you want to choose?[s(single word)/m(multiple words)]\n");
    char op;
    cin >> op;
    if(op == 's'){
        string s;
        cin >> s;
        s = table.encode(s);
        BM ser;
        ser.generate(s);
        vector<int> aws = ser.search(s, txt);
        for(auto i : aws) cout << i << endl;
    } else if(op == 'm'){
        printf("how many strings do you want to search ?");
        int n;
        cin >> n;
        if(n > 10000){
            printf("sorry, too many words\n");
            return;
        }
        printf("please input the strings\n");
        AC ser;
        for(int i = 0; i <= n; i++){
            string s;
            cin >> s;
            s = table.encode(s);
            ser.insert(s, i);
        }
        ser.build();
        vector<vector<int>> aws = ser.query(txt);
    }
}
void encode(){
    h_tree h;
    h_code H_table;
    string readin = read();
    cout << readin << endl;
    h.statistic(readin);
    h.build();
    H_table.build(h);
    //for(int i = 1; i <= 255; i++) cout << (char)i << ":::" << H_table.dic[i] << endl;
    string writeout = H_table.encode(readin);
    cout << writeout << endl;
    write(writeout);
    while(true){
        printf("do you want to search for something?[y / n]\n");
        char op;
        cin >> op;
        if(op == 'y') {
            search(H_table, writeout);
            return;
        }
        else if(op == 'n') return;
        else printf("please input again");
    }

}
void decode(){
    string readin = read();
   // string aws = h.decode(readin);
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