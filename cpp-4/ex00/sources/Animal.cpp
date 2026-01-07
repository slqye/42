/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:30:41 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/31 18:08:24 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void) : _type("Animal") {
	std::cout << "Animal default constructor called." << std::endl;
}

Animal::Animal(Animal const &ref) {
	std::cout << "Animal copy constructor called." << std::endl;
	*this = ref;
}

Animal::~Animal(void) {
	std::cout << "Animal default destructor called." << std::endl;
}

Animal	&Animal::operator=(Animal const &ref) {
	std::cout << "Animal equal operator called." << std::endl;
	this->_type = ref._type;
	return (*this);
}

std::string	Animal::getType(void) const {
	return (this->_type);
}

void	Animal::makeSound(void) const {
	std::cout << "A random animal sound." << std::endl;
}