/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:14:27 by uwywijas          #+#    #+#             */
/*   Updated: 2024/08/08 15:41:00 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template <typename T>
bool	easyfind(T value, int n) {
	typename T::iterator	i_begin	= value.begin();
	typename T::iterator	i_end	= value.end();
	typename T::iterator	itr		= std::find(i_begin, i_end, n);
	unsigned int			index	= std::distance(i_begin, itr);

	if (itr != i_end) {
		std::cout << "First occurrence found at index " << index << std::endl;
		return (true);
	}
	std::cout << "No occurence found" << std::endl;
	return (false);
}