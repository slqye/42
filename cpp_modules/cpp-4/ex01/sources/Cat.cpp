/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:50:41 by uwywijas          #+#    #+#             */
/*   Updated: 2024/06/05 15:34:34 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void) : Animal() {
	std::cout << "Cat default constructor called." << std::endl;
	this->_type = "Cat";
	this->_brain = new Brain();
}

Cat::Cat(Cat const &ref) : Animal(ref) {
	std::cout << "Cat copy constructor called." << std::endl;
	*this = ref;
}

Cat::~Cat(void) {
	delete this->_brain;
	std::cout << "Cat default destructor called." << std::endl;
}

Cat	&Cat::operator=(Cat const &ref) {
	this->_type = ref.getType();
	this->_brain = new Brain(*ref._brain);
	std::cout << "Cat equal operator called." << std::endl;
	return (*this);
}

void	Cat::makeSound(void) const {
	std::cout << "Miaou." << std::endl;
}