#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <limits>

class BitcoinExchange
{
    private:
        std::map<std::string, double> Database;

    public:
        BitcoinExchange();
        ~BitcoinExchange();

        void openDatabase(const std::string & filename);
        void handleInputFile(const std::string & filename);
        int isValidDate(const std::string & date);
        int isValidValue(const std::string & valueStr);

};





#endif