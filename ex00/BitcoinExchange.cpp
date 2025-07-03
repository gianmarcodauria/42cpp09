#include "BitcoinExchange.hpp"
#include <iomanip>
#include <sstream>
#include <cstdio>
 
BitcoinExchange::BitcoinExchange()
{
}
 
BitcoinExchange::~BitcoinExchange()
{
}
 
void BitcoinExchange::openDatabase(const std::string & filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "ERROR: could not open the file" << std::endl;
        return;
    }
 
    std::string line;
    std::getline(file, line); // skip header
 
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date, rateStr;
 
        std::getline(iss, date, ',');
        std::getline(iss, rateStr);
 
        if (date.empty() || rateStr.empty())
        {
            std::cerr << "Warning: error in DB line " << line << std::endl;
            continue;
        }
 
        double rate;
        std::istringstream rateStream(rateStr);
        rateStream >> rate;
 
        if (rateStream.fail())
        {
            std::cerr << "Warning: invalid rate: " << rateStr << std::endl;
            continue;
        }
        Database[date] = rate;
    }
    file.close();
}
 
static std::string trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t");
    if (start == std::string::npos)
        return "";
 
    size_t end = str.find_last_not_of(" \t");
    return str.substr(start, end - start + 1);
}
 
void BitcoinExchange::handleInputFile(const std::string & filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "ERROR: could not open file" << std::endl;
        return;
    }
 
    std::string line;
    std::getline(file, line); // skip header
 
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
 
        std::istringstream iss(line);
        std::string section_date, section_value;
 
        std::getline(iss, section_date, '|');
        std::getline(iss, section_value);
 
        section_date = trim(section_date);
        section_value = trim(section_value);
 
        if (!isValidDate(section_date))
        {
            std::cerr << "Error: bad input => " << section_date << std::endl;
            continue;
        }
 
        if (!isValidValue(section_value))
            continue;
 
        double value = std::atof(section_value.c_str());
 
        std::map<std::string, double>::const_iterator it = Database.lower_bound(section_date);
        if (it == Database.end() || it->first != section_date)
        {
            if (it == Database.begin())
            {
                std::cerr << "ERROR: no exchange rate before this date: " << section_date << std::endl;
                continue;
            }
            --it;
        }
 
        double rate = it->second;
        double result = value * rate;
 
        std::ostringstream oss_value, oss_result;
        oss_value << std::fixed << std::setprecision(2) << value;
        oss_result << std::fixed << std::setprecision(2) << result;

        std::string str_value = oss_value.str();
        std::string str_result = oss_result.str();

        // Rimuovi zeri finali da str_value
        while (!str_value.empty() && str_value[str_value.size() - 1] == '0')
            str_value.erase(str_value.size() - 1, 1);
        if (!str_value.empty() && str_value[str_value.size() - 1] == '.')
            str_value.erase(str_value.size() - 1, 1);

        // Rimuovi zeri finali da str_result
        while (!str_result.empty() && str_result[str_result.size() - 1] == '0')
            str_result.erase(str_result.size() - 1, 1);
        if (!str_result.empty() && str_result[str_result.size() - 1] == '.')
            str_result.erase(str_result.size() - 1, 1);

        std::cout << section_date << " => " << str_value << " = " << str_result << std::endl;
    }
    file.close();
}
 
int BitcoinExchange::isValidDate(const std::string& date)
{
    if (date.length() != 10)
        return 0;
 
    if (date[4] != '-' || date[7] != '-')
        return 0;
 
    int year, month, day;
    if (sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
        return 0;
 
    if (year < 2009)
        return 0;
 
    if (month < 1 || month > 12)
        return 0;
 
    int days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
 
    int leap_year = 0;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        leap_year = 1;
 
    if (leap_year && month == 2)
        days_in_month[1] = 29;
 
    if (day < 1 || day > days_in_month[month - 1])
        return 0;
 
    return 1;
}
 
int BitcoinExchange::isValidValue(const std::string& valueStr)
{
    std::istringstream iss(valueStr);
    double value;
 
    iss >> value;
    if (iss.fail() || !iss.eof())
    {
        std::cerr << "Error: bad value => " << valueStr << std::endl;
        return 0;
    }
 
    if (value < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return 0;
    }
 
    if (value > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return 0;
    }
 
    return 1;
}
 