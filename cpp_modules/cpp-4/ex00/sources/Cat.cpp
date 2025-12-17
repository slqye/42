/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:50:41 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/31 18:17:31 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void) : Animal() {
	std::cout << "Cat default constructor called." << std::endl;
	this->_type = "Cat";
}

Cat::Cat(Cat const &ref) : Animal(ref) {
	std::cout << "Cat copy constructor called." << std::endl;
	*this = ref;
}

Cat::~Cat(void) {
	std::cout << "Cat default destructor called." << std::endl;
}

Cat	&Cat::operator=(Cat const &ref) {
	std::cout << "Cat equal operator called." << std::endl;
	this->_type = ref._type;
	return (*this);
}

void	Cat::makeSound(void) const {
	std::cout << "Miaou." << std::endl;
}