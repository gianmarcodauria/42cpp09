#include "RPN.hpp"

RPN::RPN()
{

}

RPN::~RPN()
{

}

bool RPN::checkOperator(const std::string & oper) const
{
    return oper == "+" || oper == "-" || oper == "*" || oper == "/";
}

bool RPN::checkNum(const std::string & num) const
{
    return num.size() && isdigit(num[0]);
}

void RPN::execOperator(const std::string & oper)
{
    if (stack.size() < 2)
    {
        std::cerr << "ERROR: not enough values" << std::endl;
        std::exit(1);
    }

    int b = stack.top(); 
    stack.pop();
    int a = stack.top();
    stack.pop();
    int res = 0;

    if (oper == "+")
        res = a + b;

    else if (oper == "-")
        res = a - b;
    else if (oper == "*")
        res = a * b;
    else if (oper == "/")
    {
        if (b == 0)
        {
            throw std::runtime_error("Error");
        }
        res = a / b;
    }
    stack.push(res);
}


void RPN::eval(const std::string & express)
{

    while (!stack.empty())
        stack.pop();

    std::istringstream iss(express);
    std::string opInStack;

    while (iss >> opInStack)
    {
        if (checkNum(opInStack))
        {
            stack.push(std::atoi(opInStack.c_str()));
        }
        else if (checkOperator(opInStack))
        {
            execOperator(opInStack);
        }
        else
        {
            throw std::runtime_error("Error");
        }
    }

    if (stack.size() != 1)
    {
        std::runtime_error("Error");
    }
    std::cout << stack.top() << std::endl;
}