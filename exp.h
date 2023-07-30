#ifndef EXP_H
#define EXP_H
#include "stack.h"
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>

class EXP{
private :
    std :: string inexp;
    std :: string postexp;
    std :: string preexp;
    double  postans, preans;
public :
    EXP();
    EXP(std :: string s);
    ~EXP();
    std :: string get_inexp();
    //判断字符串是否合法。
    bool is_exp();
    //判断是否为操作符
    bool is_operator(char c);
    // 获取操作符的优先级
    int get_priority(char c);
    //中缀转前缀表达式
    std :: string get_preexp();
    //前缀表达式求值
    long double  evaluate_preexp();
    // 中缀表达式转后缀表达式
    std :: string get_postexp();
    // 后缀表达式求值
    long double evaluate_postexp();

};

#endif // EXP_H
