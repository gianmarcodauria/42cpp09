#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <sstream>
#include <iostream>
#include <cstdlib>

class RPN
{
    public:
        RPN();
        ~RPN();

        void eval(const std::string & express);

    private:
        std::stack<int> stack;

        void execOperator(const std::string & oper);
        bool checkOperator(const std::string & oper) const;
        bool checkNum(const std::string & num) const;
};

#endif