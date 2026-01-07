/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:29 by slaye             #+#    #+#             */
/*   Updated: 2024/05/21 17:45:22 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

Weapon::Weapon(std::string type) : type(type) {
	return ;
}

Weapon::~Weapon(void) {
	return ;
}

const std::string	&Weapon::getType(void) const {
	return (this->type);
}

void	Weapon::setType(std::string value) {
	this->type = value;
}