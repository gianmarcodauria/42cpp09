#include "RPN.hpp"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./RPN \"expression\"" << std::endl;
        return 1;
    }

    std::string expression = argv[1];

    try 
    {
        RPN calculator;
        calculator.eval(expression);
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}