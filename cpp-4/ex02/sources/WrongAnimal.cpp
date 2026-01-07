/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:30:41 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/31 18:34:46 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : _type("WrongAnimal") {
	std::cout << "WrongAnimal default constructor called." << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &ref) {
	std::cout << "WrongAnimal copy constructor called." << std::endl;
	*this = ref;
}

WrongAnimal::~WrongAnimal(void) {
	std::cout << "WrongAnimal default destructor called." << std::endl;
}

WrongAnimal	&WrongAnimal::operator=(WrongAnimal const &ref) {
	std::cout << "WrongAnimal equal operator called." << std::endl;
	this->_type = ref._type;
	return (*this);
}

std::string	WrongAnimal::getType(void) const {
	return (this->_type);
}

void	WrongAnimal::makeSound(void) const {
	std::cout << "A random WrongAnimal sound." << std::endl;
}