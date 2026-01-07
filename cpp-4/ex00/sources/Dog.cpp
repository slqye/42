/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:50:41 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/31 18:23:54 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void) : Animal() {
	std::cout << "Dog default constructor called." << std::endl;
	this->_type = "Dog";
}

Dog::Dog(Dog const &ref) : Animal(ref) {
	std::cout << "Dog copy constructor called." << std::endl;
	*this = ref;
}

Dog::~Dog(void) {
	std::cout << "Dog default destructor called." << std::endl;
}

Dog	&Dog::operator=(Dog const &ref) {
	std::cout << "Dog equal operator called." << std::endl;
	this->_type = ref._type;
	return (*this);
}

void	Dog::makeSound(void) const {
	std::cout << "Wouaf wouaf." << std::endl;
}