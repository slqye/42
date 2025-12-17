/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:02:08 by slaye             #+#    #+#             */
/*   Updated: 2024/06/05 15:20:41 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(void) {
	std::cout << "Brain default constructor called." << std::endl;
}

Brain::Brain(Brain const &ref) {
	std::cout << "Brain copy constructor called." << std::endl;
	*this = ref;
}

Brain::~Brain(void) {
	std::cout << "Brain default destructor called." << std::endl;
}

Brain	&Brain::operator=(Brain const &ref) {
	std::cout << "Brain equal operator called." << std::endl;
	for (int i = 0; i < 100; i++) {
		this->_ideas[i] = ref._ideas[i];
	}
	return (*this);
}