/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:50:41 by uwywijas          #+#    #+#             */
/*   Updated: 2024/06/05 14:37:36 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void) : WrongAnimal() {
	std::cout << "WrongCat default constructor called." << std::endl;
	this->_type = "WrongCat";
}

WrongCat::WrongCat(WrongCat const &ref) : WrongAnimal(ref) {
	std::cout << "WrongCat copy constructor called." << std::endl;
	*this = ref;
}

WrongCat::~WrongCat(void) {
	std::cout << "WrongCat default destructor called." << std::endl;
}

WrongCat	&WrongCat::operator=(WrongCat const &ref) {
	std::cout << "WrongCat equal operator called." << std::endl;
	this->_type = ref._type;
	return (*this);
}

void	WrongCat::makeSound(void) const {
	std::cout << "Wrong miaou." << std::endl;
}