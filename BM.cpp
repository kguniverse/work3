//
// Created by 王乾凱 on 2020/11/19.
//
#include "BM.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back

void BM::generate(std::string s){
    for(int i = 0; i <= 255; i++) bad_char.pb(-1);
    for(int i = 0; i < s.length(); i++){
        bad_char[s[i]] = i;
    }
}