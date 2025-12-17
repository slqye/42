/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:58:27 by slaye             #+#    #+#             */
/*   Updated: 2024/05/15 11:58:31 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"
#include "Contact.class.hpp"

Contact::Contact(void) {
	return ;
}

Contact::~Contact(void) {
	return ;
}

int	Contact::setup(void) {
	std::string	input;

	input = prompt("First name: ");
	if (std::cin.eof())
		return (std::cout << std::endl << OPE_CANCELED << std::endl, 1);
	if (input.compare("") == 0 || is_empty(input))
		return (std::cout << OPE_CANCELED << std::endl, 2);
	this->fname = input;
	input = prompt("Last name: ");
	if (std::cin.eof())
		return (std::cout << std::endl << OPE_CANCELED << std::endl, 1);
	if (input.compare("") == 0 || is_empty(input))
		return (std::cout << OPE_CANCELED << std::endl, 2);
	this->lname = input;
	input = prompt("Nickname: ");
	if (std::cin.eof())
		return (std::cout << std::endl << OPE_CANCELED << std::endl, 1);
	if (input.compare("") == 0 || is_empty(input))
		return (std::cout << OPE_CANCELED << std::endl, 2);
	this->nickname = input;
	input = prompt("Phone number: ");
	if (std::cin.eof())
		return (std::cout << std::endl << OPE_CANCELED << std::endl, 1);
	if (input.compare("") == 0 || is_empty(input))
		return (std::cout << OPE_CANCELED << std::endl, 2);
	else if (!(input.length() == 10 && is_strnum(input)))
		return (std::cout << ERR_FORMAT << std::endl, 2);
	this->number = input;
	input = prompt("Darkest secret: ");
	if (std::cin.eof())
		return (std::cout << std::endl << OPE_CANCELED << std::endl, 1);
	if (input.compare("") == 0 || is_empty(input))
		return (std::cout << OPE_CANCELED << std::endl, 2);
	this->secret = input;
	return (0);
}

void Contact::print(void) const {
	std::cout << "First name: " << this->fname << std::endl;
	std::cout << "Last name: " << this->lname << std::endl;
	std::cout << "Nickname: " << this->nickname << std::endl;
	std::cout << "Phone number: " << this->number << std::endl;
	std::cout << "Darkest secret: " << this->secret << std::endl;
}

std::string Contact::get_fname(void) const {
	return (this->fname);
}

std::string Contact::get_lname(void) const {
	return (this->lname);
}

std::string Contact::get_nickname(void) const {
	return (this->nickname);
}

std::string Contact::get_number(void) const {
	return (this->number);
}

std::string Contact::get_secret(void) const {
	return (this->secret);
}

bool	Contact::is_strnum(std::string value) const {
	for (int i = 0; i < (int) value.length(); i++) {
		if (!std::isdigit(value[i]))
			return (false);
	}
	return (true);
}

bool	Contact::is_empty(std::string value) const {
	int	count = 0;

	for (int i = 0; i < (int) value.length(); i++) {
		if (value[i] == ' ')
			count++;
	}
	if (count == (int) value.length())
		return (true);
	return (false);
}