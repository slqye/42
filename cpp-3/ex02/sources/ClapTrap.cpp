/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:52:44 by slaye             #+#    #+#             */
/*   Updated: 2024/05/31 17:00:36 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : _name("Default"), _hit_points(10), _energy_points(10), _attack_damage(0) {
	std::cout << "Default ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hit_points(10), _energy_points(10), _attack_damage(0) {
	std::cout << "Name ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &ref) {
	std::cout << "Copy ClapTrap constructor called" << std::endl;
	*this = ref;
}

ClapTrap::~ClapTrap() {
	std::cout << "Default ClapTrap destructor called" << std::endl;
}

ClapTrap	&ClapTrap::operator=(ClapTrap const &ref) {
	this->_name = ref.get_name();
	this->_hit_points = ref.get_hit_points();
	this->_energy_points = ref.get_energy_points();
	this->_attack_damage = ref.get_attack_damage();
	return (*this);
}

std::string	ClapTrap::get_name(void) const {
	return (this->_name);
}

unsigned int	ClapTrap::get_hit_points(void) const {
	return (this->_hit_points);
}

unsigned int	ClapTrap::get_energy_points(void) const {
	return (this->_energy_points);
}

unsigned int	ClapTrap::get_attack_damage(void) const {
	return (this->_attack_damage);
}

void	ClapTrap::attack(const std::string &target) {
	if (this->_energy_points <= 0 || this->_hit_points <= 0)
		return ;
	this->_energy_points -= 1;
	std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing " << this->_attack_damage << " points of damage!" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	amount <= this->_hit_points ? this->_hit_points -= amount : this->_hit_points = 0;
	std::cout << "ClapTrap " << this->_name << " has been damaged by " << amount << " points!" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (this->_energy_points <= 0)
		return ;
	this->_energy_points -= 1;
	if (this->_hit_points + amount < this->_hit_points)
		this->_hit_points = 4294967295;
	else
		this->_hit_points += amount;
	std::cout << "ClapTrap " << this->_name << " repaired himself of " << amount << " points!" << std::endl;
}