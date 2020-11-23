//
// Created by 王乾凱 on 2020/11/19.
//
#include "BM.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back

void BM::generate(std::string s){
    n = s.size();
    for(int i = 0; i <= 255; i++) bad_char.pb(n);
    for(int i = 0; i < s.length(); i++){
        bad_char[s[i]] = n - i - 1;
    }
    suffix.resize(n);
    good_char.resize(n);
    suffix[n - 1] = n;
    for(int i = n - 2; i >= 0; i--){
        int q = i;
        while(q > 0 && s[q] == s[n - 1 - i + q]) q--;
        suffix[i] = i - q;
    }
    for(int i = 0; i < n; i++) good_char[i] = n;
    int j = 0;
    for(int i = n - 1; i >= 0; i--){
        if(suffix[i] == i + 1)
            for(; j < n - 1 - i; j++){
                if(good_char[j] == n) good_char[j] = n - 1 - i;
            }
    }
    for(int i = 0; i < n; i++) good_char[n - 1 - suffix[i]] = n - 1 - i;
}

vector<int> BM::search(std::string s, std::string t) {
    int m = t.size();
    int j = 0, i;
    vector<int> ret;
    while(j <= m - n){
        for(i = n - 1; i >= 0 && s[i] == t[j + i]; i--);
        if(i < 0){
            ret.push_back(j);
            j += good_char[0];
        }
        else j += max(good_char[i], bad_char[t[i + j]] - n + 1 + i);
    }
    return ret;
}