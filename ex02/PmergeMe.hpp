/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gianmarco.dauria@libero.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:03:18 by gd-auria          #+#    #+#             */
/*   Updated: 2025/07/09 16:05:44 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <stdexcept>

class PmergeMe
{
    public:
        PmergeMe();
        ~PmergeMe();

        void sortAndPrint(int argc, char** argv);

    private:
        std::vector<int> parseArguments(int argc, char** argv);

        template <typename Container>
        Container mergeInsertSort(const Container& input);

        template <typename Container>
        double process(Container& container, const std::string& name);
};

#endif