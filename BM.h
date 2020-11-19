//
// Created by 王乾凱 on 2020/11/19.
//
#include<vector>
#include<string>
#ifndef WORK3_BM_H
#define WORK3_BM_H
class BM{
private:
    int n;
    std::vector<int> bad_char;
    std::vector<int> good_char;
public:
    void generate(std::string s);
    //TODO: generate the good mode
};
#endif //WORK3_BM_H
