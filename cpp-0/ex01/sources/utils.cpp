/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:22:18 by slaye             #+#    #+#             */
/*   Updated: 2024/05/15 12:25:30 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

std::string	prompt(std::string value)
{
	std::string	input;
	std::string	result;

	if (std::cin.eof())
		return (NULL);
	std::cout << value;
	getline(std::cin, input);
	for (int i = 0; i < (int) input.length(); i++) {
		if (input[i] == '\t')
			result += "    ";
		else if (!(input[i] >= 32 && input[i] <= 126))
			continue ;
		else
			result += input[i];
	}
	return (result);
}

void	truncate(std::string value)
{
	for (int i = 0; i < 9; i++)
		std::cout << value[i];
	std::cout << ".";
}

void	add_mspaces(std::string value)
{
	for (int i = 0; i < 10 - (int) value.length(); i++)
		std::cout << " ";
	std::cout << value;
}