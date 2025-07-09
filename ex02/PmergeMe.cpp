/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gianmarco.dauria@libero.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:05:29 by gd-auria          #+#    #+#             */
/*   Updated: 2025/07/09 16:07:05 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <algorithm>

PmergeMe::PmergeMe()
{
    
}

PmergeMe::~PmergeMe()
{
    
}

void PmergeMe::sortAndPrint(int argc, char** argv)
{
    std::vector<int> data = parseArguments(argc, argv);

    std::vector<int> vecInput = data;
    std::deque<int> deqInput(data.begin(), data.end());

    std::cout << "Before: ";
    for (size_t i = 0; i < data.size(); ++i)
        std::cout << data[i] << " ";
    std::cout << std::endl;

    double vecTime = process(vecInput, "std::vector");
    double deqTime = process(deqInput, "std::deque");

    (void)vecTime;
    (void)deqTime;
}

std::vector<int> PmergeMe::parseArguments(int argc, char** argv)
{
    std::vector<int> result;
    for (int i = 1; i < argc; ++i) 
    {
        std::string arg(argv[i]);
        for (size_t j = 0; j < arg.length(); ++j)
        {
            if (!std::isdigit(arg[j]))
                throw std::invalid_argument("Error");
        }
        long num = std::strtol(argv[i], NULL, 10);
        if (num < 0 || num > INT_MAX)
            throw std::invalid_argument("Error");
        result.push_back(static_cast<int>(num));
    }
    return result;
}

template <typename Container>
Container PmergeMe::mergeInsertSort(const Container& input)
{
    if (input.size() <= 1)
        return input;

    Container mainChain;
    Container pending;

    typename Container::const_iterator it = input.begin();
    while (it != input.end())
    {
        int first = *it;
        ++it;
        if (it != input.end())
        {
            int second = *it;
            if (first < second)
            {
                pending.push_back(first);
                mainChain.push_back(second);
            } 
            else 
            {
                pending.push_back(second);
                mainChain.push_back(first);
            }
            ++it;
        } 
        else
            pending.push_back(first);
    }

    mainChain = mergeInsertSort(mainChain);

    for (typename Container::iterator p = pending.begin(); p != pending.end(); ++p)
    {
        typename Container::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), *p);
        mainChain.insert(pos, *p);
    }
    return mainChain;
}

template <typename Container>
double PmergeMe::process(Container& container, const std::string& name)
{
    std::clock_t start = std::clock();
    Container sorted = mergeInsertSort(container);
    std::clock_t end = std::clock();

    double elapsed = 1e6 * (end - start) / (double)CLOCKS_PER_SEC;

    std::cout << "After: ";
    for (size_t i = 0; i < sorted.size(); ++i)
        std::cout << sorted[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << sorted.size() << " elements with "
              << name << " : " << elapsed << " us" << std::endl;

    return elapsed;
}

template std::vector<int> PmergeMe::mergeInsertSort(const std::vector<int>&);
template std::deque<int> PmergeMe::mergeInsertSort(const std::deque<int>&);
template double PmergeMe::process(std::vector<int>&, const std::string&);
template double PmergeMe::process(std::deque<int>&, const std::string&);