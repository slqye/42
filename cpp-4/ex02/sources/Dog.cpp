/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:50:41 by uwywijas          #+#    #+#             */
/*   Updated: 2024/06/05 15:40:05 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void) : Animal() {
	std::cout << "Dog default constructor called." << std::endl;
	this->_type = "Dog";
	this->_brain = new Brain();
}

Dog::Dog(Dog const &ref) : Animal(ref) {
	std::cout << "Dog copy constructor called." << std::endl;
	*this = ref;
}

Dog::~Dog(void) {
	delete this->_brain;
	std::cout << "Dog default destructor called." << std::endl;
}

Dog	&Dog::operator=(Dog const &ref) {
	this->_type = ref.getType();
	this->_brain = new Brain(*ref._brain);
	std::cout << "Dog equal operator called." << std::endl;
	return (*this);
}

void	Dog::makeSound(void) const {
	std::cout << "Wouaf wouaf." << std::endl;
}