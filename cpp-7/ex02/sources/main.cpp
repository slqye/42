/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:12:13 by slaye             #+#    #+#             */
/*   Updated: 2024/08/08 15:08:02 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main( void )
{
	unsigned int size = 10;
	Array<int> list(size);
	Array<int> holder(list);
	Array<int> copy = list;
	Array<int> tester;

	list[0] = 10;
	std::cout << "list: [";
	for (unsigned int i = 0; i < size - 1; i++)
		std::cout << list[i] << ", ";
	std::cout << list[size - 1];
	std::cout << "]" << std::endl;

	std::cout << "holder: [";
	for (unsigned int i = 0; i < size - 1; i++)
		std::cout << holder[i] << ", ";
	std::cout << holder[size - 1];
	std::cout << "]" << std::endl;

	std::cout << "copy: [";
	for (unsigned int i = 0; i < size - 1; i++)
		std::cout << copy[i] << ", ";
	std::cout << copy[size - 1];
	std::cout << "]" << std::endl;

	try
	{
		std::cout << holder[9] << std::endl;
		std::cout << tester[10] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	// String test
	Array<std::string> strs(2);

	strs[0] = "hello";
	strs[1] = "world";
	std::cout << strs[0] << " " << strs[1] << std::endl;
	return (0);
}