#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "ERROR: could not open file" << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    btc.openDatabase("data.csv");
    btc.handleInputFile(argv[1]);
    return 0;
}