/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:18:42 by slaye             #+#    #+#             */
/*   Updated: 2024/05/31 16:57:35 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

#define SCAVTRAP_HITPOINT 100
#define SCAVTRAP_ENERGYPOINT 50
#define SCAVTRAP_ATTACKDAMAGE 20

ScavTrap::ScavTrap(void) : ClapTrap() {
	this->_hit_points = SCAVTRAP_HITPOINT;
	this->_energy_points = SCAVTRAP_ENERGYPOINT;
	this->_attack_damage = SCAVTRAP_ATTACKDAMAGE;
	std::cout << "Default ScavTrap constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	this->_hit_points = SCAVTRAP_HITPOINT;
	this->_energy_points = SCAVTRAP_ENERGYPOINT;
	this->_attack_damage = SCAVTRAP_ATTACKDAMAGE;
	std::cout << "Name ScavTrap constructor called" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const &ref) : ClapTrap(ref) {
	std::cout << "Copy ScavTrap constructor called" << std::endl;
	*this = ref;
}

ScavTrap::~ScavTrap() {
	std::cout << "Default ScavTrap destructor called" << std::endl;
}

ScavTrap	&ScavTrap::operator=(ScavTrap const &ref) {
	this->_name = ref.get_name();
	this->_hit_points = ref.get_hit_points();
	this->_energy_points = ref.get_energy_points();
	this->_attack_damage = ref.get_attack_damage();
	return (*this);
}


void	ScavTrap::attack(const std::string &target) {
	if (this->_energy_points <= 0 || this->_hit_points <= 0)
		return ;
	this->_energy_points -= 1;
	std::cout << "ScavTrap " << this->_name << " attacks " << target << ", causing " << this->_attack_damage << " points of damage!" << std::endl;
}

void	ScavTrap::guardGate(void) const {
	if (this->_hit_points <= 0)
		return ;
	std::cout << "ScavTrap " << this->_name << " is now in Gatekeeper mode." << std::endl;
}