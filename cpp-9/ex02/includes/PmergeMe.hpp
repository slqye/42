/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:10:52 by slaye             #+#    #+#             */
/*   Updated: 2024/08/19 14:35:56 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class PmergeMe {
	public:
		static void	vector_sort(std::vector<unsigned int> numbers);
		static std::vector<unsigned int>	vector_merge(std::vector<unsigned int> *doubles, unsigned int start, unsigned int end);
		static void	list_sort(std::vector<unsigned int> numbers);
		static std::list<unsigned int>	list_merge(std::list<unsigned int> *doubles, unsigned int start, unsigned int end);

	private:
		PmergeMe(void);
		PmergeMe(const PmergeMe &reference);
		virtual ~PmergeMe(void);

		PmergeMe	&operator=(const PmergeMe &reference);

};