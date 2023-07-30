#include "exp.h"
#include "stack.h"
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
EXP::EXP(){
    inexp = "";
    postexp = "";
    preexp = " ";
}
EXP::EXP(string s){
    inexp = s;
    postexp = "";
    preexp = "";
}
EXP::~EXP(){

}
string EXP::get_inexp(){
    return inexp;
}

bool EXP:: is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}
// 获取操作符的优先级
int EXP:: get_priority(char c) {
    if (c == '^'){
        return 3;
    } else if (c == '*' || c == '/' || c == '%'  ) {
        return 2;
    } else if (c == '+' || c == '-'){
        return 1;
    } else {
        return 0;
    }
}

//判断表达式是否合法
bool EXP:: is_exp(){
    postexp.clear();
    get_postexp();
    for(int i = 0; i < postexp.size(); i++){
        if(postexp[i] != ' ' && !isdigit(postexp[i]) && !is_operator(postexp[i]) && postexp[i] != '.')
            return false;
    }
    Stack<long double> resultstack;
    unsigned int i = 0;
    while (i < postexp.length()) {
        char c = postexp[i];
        if(c == '-' && isdigit(postexp[i + 1])){
           i++;
           long double num = 0;
           while (i < postexp.length() && isdigit(postexp[i])) {
               num = num * 10 + (postexp[i] - '0');
               i++;
           }
           if(i < postexp.length() && postexp[i] == '.'){
               i++;
               long double fraction = 1.0;
               while (i < postexp.length() && isdigit(postexp[i])){
                   fraction /= 10.0;
                   num += (postexp[i] - '0') * fraction;
                   i++;
               }
           }
           num *= (-1);
           resultstack.push(num);
       }
        else if (isdigit(c)){
            long double num = 0;
            while (i < postexp.length() && isdigit(postexp[i])) {
                num = num * 10 + (postexp[i] - '0');
                i++;
            }
            if(i < postexp.length() && postexp[i] == '.'){
                i++;
                long double fraction = 1.0;
                while (i < postexp.length() && isdigit(postexp[i])){
                    fraction /= 10.0;
                    num += (postexp[i] - '0') * fraction;
                    i++;
                }
            }
            resultstack.push(num);
        }
        else if (is_operator(c)){
          if(resultstack.empty()) return false;
          long double num2 = resultstack.peek();
          resultstack.pop();

          if(resultstack.empty()) return false;
          long double num1 = resultstack.peek();
          long double num = abs(num1);
          resultstack.pop();
          double result = 0;
          if (c == '+') {
              result = num1 + num2;
          }
          else if (c == '-'){
              result = num1 - num2;
          }
          else if (c == '*') {
              result = num1 * num2;
          }
          else if (c == '/') {
              if(num2 == 0){
                  return false;
              }
              result = num1 / num2;
          }
          else if (c == '%') {
             if(num1 - int(num1) != 0 || num2 - int(num2) != 0) return false;
             if(int(num1) == num1 && int(num2) == num2)
                result = int(num1) % int(num2);
          }
          else if (c == '^'){
              if(num1 < 0 && num2 < 1) return false;
             result = pow(num, num2);
             if(num1 <  0 &&( int(num2) != num2 || abs(int(num2)) % 2 != 0)) result *= (-1);
          }
          resultstack.push(result);
          i++;
        }
        else{
            i++;
        }
    }
    if(resultstack.size() > 1) return false;
    return true;
}

//中缀转前缀表达式
string EXP :: get_preexp(){
    Stack<char> opstack;
    Stack<char> result;
    int i = inexp.size() - 1;
    while (i >= 0){
        char c = inexp[i];
        if (isdigit(c)){
            // 如果是数字，直接输出到前缀表达式中
            while (i >= 0 && isdigit(inexp[i])) {
                result.push(inexp[i]);
                i--;
            }
            if(i >= 0 && inexp[i] == '.'){
                result.push(inexp[i]);
                i--;
                while (i < inexp.length() && isdigit(inexp[i])){
                    result.push(inexp[i]);
                    i--;
                }
            }
            if(inexp[i] == '-' &&(i == 0 || inexp[i - 1] == '(') ){
                result.push('-');
                if(i != 0) opstack.pop();
                i -= 2;
            }
            result.push(' ');
        }
        else if (is_operator(c)){
            // 如果是操作符，将其与栈顶操作符比较优先级
            while (!opstack.empty() && is_operator(opstack.peek()) && get_priority(c) <= get_priority(opstack.peek())){
                result.push(opstack.peek());
                result.push(' ');
                opstack.pop();
            }
            opstack.push(c);
            i--;
        }
        else if (c == ')') {
            // 如果右括号，直接入栈
            opstack.push(c);
            i--;
        }
        else if (c == '(') {
            // 如果是左括号，将栈顶操作符输出到后缀表达式中，直到遇到右括号
            while (!opstack.empty() && opstack.peek() != ')') {
                result.push(opstack.peek());
                result.push(' ');
                opstack.pop();
            }
            if (!opstack.empty() && opstack.peek() == ')') {
                opstack.pop();
            }
            i--;
        }
        else{
            i--;
        }
    }
    // 将栈中剩余的操作符全部输出到前缀表达式中
    while (!opstack.empty()) {
        result.push(opstack.peek());
        result.push(' ');
        opstack.pop();
    }
    // 前缀表达式
    while (!result.empty()) {
        preexp += result.peek();
        result.pop();
    }
    return preexp;
}
long double EXP:: evaluate_preexp(){
   preexp.clear();
   get_preexp();
   Stack<long double> resultstack;
   int i = preexp.size() - 1;
   while (i >= 0) {
       char c = preexp[i];
       if (isdigit(c)){
           // 如果是数字，将其转换成double类型并入栈
           long double num2 = 0;
           int cnt = 1;
           num2 = (preexp[i] - '0') * 0.1;
           i--;
           while (i >= 0 && isdigit(preexp[i])){
               num2 = num2 * 0.1 + (preexp[i] - '0') * 0.1;
               cnt++;
               i--;
           }
           double num1 = 0;
           if(i >= 0 && preexp[i] == '.'){
               i--;
               long double num1 = (preexp[i] - '0');
               int cnt1 = 10;
               i--;
               while (i >= 0 && isdigit(preexp[i])){
                   num1 = num1  + (preexp[i] - '0') * cnt1;
                   cnt1 *= 10;
                   i--;
               }
                long double num = num1 + num2;
               if(preexp[i] == '-'){
                    num *= (-1);
                   i--;
               }
               resultstack.push(num);
           }
           else{
               long double num = (num2 - int(num2)) * pow(10, cnt);
               if(preexp[i] == '-'){
                   num *= (-1);
                   i--;
               }
               resultstack.push(num);
           }
       }
       else if (is_operator(c)) {
       // 如果是操作符，从栈中弹出两个数并计算结果，再将结果入栈
           long double num1 = resultstack.peek();
          long  double num = abs(num1);
           resultstack.pop();
           long double num2 = resultstack.peek();
           resultstack.pop();
           long double result = 0;
           if (c == '+') {
               result = num1 + num2;
           }
           else if (c == '-'){
               result = num1 - num2;
           }
           else if (c == '*') {
               result = num1 * num2;
           }
           else if (c == '/') {
               result = num1 / num2;
           }
           else if (c == '%') {
               if(int(num1) == num1 && int(num2) == num2)
                  result = int(num1) % int(num2);
           }
           else if (c == '^'){
               result = pow(num1, num2);
              if(num1 <  0 &&( int(num2) != num2 || abs(int(num2)) % 2 != 0)) result *= (-1);
           }
           resultstack.push(result);
           i--;
       }
       else{
           i--;
       }
   }
   // 栈顶元素即为表达式的计算结果
   preans = resultstack.peek();
   return preans;
}

// 中缀表达式转后缀表达式
string EXP::get_postexp(){
    postexp.clear();
    Stack<char> opstack;
    unsigned int i = 0;
    while (i < inexp.length()){
        char c = inexp[i];
        if(c == '-' &&(i == 0 || inexp[i - 1] == '(')){
                postexp += c;
                i++;
                 while (i < inexp.length() && isdigit(inexp[i])) {
                    postexp += inexp[i];
                    i++;
                }
                if(i < inexp.length() && inexp[i] == '.'){
                    postexp += inexp[i];
                    i++;
                    while (i < inexp.length() && isdigit(inexp[i])){
                        postexp += inexp[i];
                        i++;
                    }
                }
                postexp += " ";
         }
        else if (isdigit(c)) {
            // 如果是数字，直接输出到后缀表达式中
            while (i < inexp.length() && isdigit(inexp[i])) {
                postexp += inexp[i];
                i++;
            }
            if(i < inexp.length() && inexp[i] == '.'){
                postexp += inexp[i];
                i++;
                while (i < inexp.length() && isdigit(inexp[i])){
                    postexp += inexp[i];
                    i++;
                }
            }
            postexp += " ";
        }
        else if (is_operator(c)){
            // 如果是操作符，将其与栈顶操作符比较优先级
            while (!opstack.empty() && is_operator(opstack.peek()) && get_priority(c) <= get_priority(opstack.peek())){
                postexp += opstack.peek();
                postexp += " ";
                opstack.pop();
            }
            opstack.push(c);
            i++;
        }
        else if (c == '(') {
            // 如果是左括号，直接入栈
            opstack.push(c);
            i++;
        }
        else if (c == ')') {
            // 如果是右括号，将栈顶操作符输出到后缀表达式中，直到遇到左括号
            while (!opstack.empty() && opstack.peek() != '(') {
                postexp += opstack.peek();
                postexp += " ";
                opstack.pop();
            }
            if (!opstack.empty() && opstack.peek() == '(') {
                opstack.pop();
            }
            i++;
        }
        else{
            i++;
        }
    }
    // 将栈中剩余的操作符全部输出到后缀表达式中
    while (!opstack.empty()) {
        postexp += opstack.peek();
        postexp += " ";
        opstack.pop();
    }
    return postexp;
}
// 后缀表达式求值
long double EXP::evaluate_postexp(){
    postexp.clear();
    get_postexp();
    Stack<long double> resultstack;
    unsigned int i = 0;
    while (i < postexp.length()) {
        char c = postexp[i];
        if(c == '-' && isdigit(postexp[i + 1])){
           i++;
          long double num = 0;
           while (i < postexp.length() && isdigit(postexp[i])) {
               num = num * 10 + (postexp[i] - '0');
               i++;
           }
           if(i < postexp.length() && postexp[i] == '.'){
               i++;
              long double fraction = 1.0;
               while (i < postexp.length() && isdigit(postexp[i])){
                   fraction /= 10.0;
                   num += (postexp[i] - '0') * fraction;
                   i++;
               }
           }
           num *= (-1);
           resultstack.push(num);
       }
        else if (isdigit(c)){
            // 如果是数字，将其转换成double类型并入栈
            long double num = 0;
            while (i < postexp.length() && isdigit(postexp[i])) {
                num = num * 10 + (postexp[i] - '0');
                i++;
            }
            if(i < postexp.length() && postexp[i] == '.'){
                i++;
                long double fraction = 1.0;
                while (i < postexp.length() && isdigit(postexp[i])){
                    fraction /= 10.0;
                    num += (postexp[i] - '0') * fraction;
                    i++;
                }
            }
            resultstack.push(num);
        }
        else if (is_operator(c)) {
           // 如果是操作符，从栈中弹出两个数并计算结果，再将结果入栈
          long double num2 = resultstack.peek();
          resultstack.pop();
         long  double num1 = resultstack.peek();
          long double num = abs(num1);
          resultstack.pop();
          long double result = 0;
          if (c == '+') {
              result = num1 + num2;
          }
          else if (c == '-'){
              result = num1 - num2;
          }
          else if (c == '*') {
              result = num1 * num2;
          }
          else if (c == '/') {
              result = num1 / num2;
          }
          else if (c == '%') {
             if(int(num1) == num1 && int(num2) == num2)
                result = int(num1) % int(num2);
          }
          else if (c == '^'){
             result = pow(num, num2);
             if(num1 <  0 &&( int(num2) != num2 || abs(int(num2)) % 2 != 0)) result *= (-1);
          }
          resultstack.push(result);
          i++;
        }
        else{
            i++;
        }
    }
    // 栈顶元素即为表达式的计算结果
    postans = resultstack.peek();
    return postans;
}
