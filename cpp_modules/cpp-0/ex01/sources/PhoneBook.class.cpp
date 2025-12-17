/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:58:27 by slaye             #+#    #+#             */
/*   Updated: 2024/05/15 11:27:11 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"
#include "PhoneBook.class.hpp"

PhoneBook::PhoneBook(void)
{
	std::cout << "╭───────────────────────────────╮" << std::endl;
	std::cout << "│         [+] Phonebook         │" << std::endl;
	std::cout << "╰───────────────────────────────╯" << std::endl;
	std::cout << std::endl;
}

PhoneBook::~PhoneBook(void)
{
	std::cout << std::endl;
	std::cout << "╭───────────────────────────────╮" << std::endl;
	std::cout << "│         [-] Phonebook         │" << std::endl;
	std::cout << "╰───────────────────────────────╯" << std::endl;
}

void	PhoneBook::set_size(int value)
{
	this->size = value;
}

int	PhoneBook::get_size(void) const {
	return (this->size);
}