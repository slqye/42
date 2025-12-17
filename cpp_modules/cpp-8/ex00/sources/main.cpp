/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:12:13 by slaye             #+#    #+#             */
/*   Updated: 2024/08/08 15:41:27 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main( void ) {
	std::vector<int> t_vector;

	t_vector.push_back(1);	// index 0
	t_vector.push_back(-6);	// index 1
	t_vector.push_back(9);	// index 2
	t_vector.push_back(-4);	// index 3
	t_vector.push_back(2);	// index 4
	easyfind(t_vector, 0);
	easyfind(t_vector, 1);
	easyfind(t_vector, 2);
	easyfind(t_vector, -4);
	return (0);
}