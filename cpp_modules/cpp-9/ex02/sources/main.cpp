/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:12:13 by slaye             #+#    #+#             */
/*   Updated: 2024/08/19 15:05:30 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

bool	is_format(std::vector<std::string> strs)
{
	std::vector<std::string>::iterator	it;

	it = strs.begin() + 1;
	while (it != strs.end()) {
		for (unsigned int i = 0; i < it->length(); i++) {
			if (!isdigit((*it)[i]))
				return (false);
		}
		it++;
	}
	return (true);
}

std::vector<unsigned int>	get_v_numbers(std::vector<std::string> strs)
{
	std::vector<std::string>::iterator	it;
	std::vector<unsigned int> 					result;

	it = strs.begin() + 1;
	while (it != strs.end()) {
		result.push_back(std::atoi((*it).c_str()));
		it++;
	}
	return (result);
}

int	main(int argc, char **argv) {
	std::vector<std::string> 	strs(argv, argv + argc);
	std::vector<unsigned int> 			v_numbers;

	if (argc < 2) {
		std::cerr << DEBUG_NAME << ERR_ARG <<std::endl;
		return (1);
	}
	if (!is_format(strs)) {
		std::cerr << DEBUG_NAME << ERR_FORMAT <<std::endl;
		return (2);
	}
	v_numbers = get_v_numbers(strs);
	std::vector<unsigned int>::iterator	it = v_numbers.begin();
	std::cout << "before: ";
	while (it != v_numbers.end()) {
		std::cout << *it;
		if (it + 1 != v_numbers.end())
			std::cout << ", ";
		it++;
	}
	std::cout << std::endl << "after: ";
	std::clock_t	clock_0 = std::clock();
	PmergeMe::vector_sort(v_numbers);
	std::clock_t	clock_1 = std::clock();
	PmergeMe::list_sort(v_numbers);
	std::clock_t	clock_2 = std::clock();
	std::cout << "Time to process a range of " << v_numbers.size() << " with std::vector: " << ((clock_1 - clock_0) * 1000) / CLOCKS_PER_SEC << "ms" << std::endl;
	std::cout << "Time to process a range of " << v_numbers.size() << " with std::list: " << ((clock_2 - clock_1) * 1000) / CLOCKS_PER_SEC << "ms" << std::endl;
	return (0);
}