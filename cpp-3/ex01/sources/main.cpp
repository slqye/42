/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:48:24 by slaye             #+#    #+#             */
/*   Updated: 2024/05/31 17:02:54 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void) {
	int	holder;

	{
		ScavTrap a;
		holder = a.get_energy_points() + 10;
		a.beRepaired(0);
		std::cout << a.get_energy_points() << std::endl;
		while (holder--)
			a.attack("TEST");
		a.guardGate();
		a.takeDamage(20);
		std::cout << a.get_attack_damage() << std::endl;
		std::cout << a.get_energy_points() << std::endl;
		std::cout << a.get_hit_points() << std::endl;
		std::cout << a.get_name() << std::endl;
	}
	std::cout << std::endl;
	{
		ScavTrap b("Robot");
		holder = b.get_energy_points() + 10;
		b.beRepaired(0);
		std::cout << b.get_energy_points() << std::endl;
		while (holder--)
			b.attack("TEST");
		b.guardGate();
		b.takeDamage(20);
		std::cout << b.get_attack_damage() << std::endl;
		std::cout << b.get_energy_points() << std::endl;
		std::cout << b.get_hit_points() << std::endl;
		std::cout << b.get_name() << std::endl;
	}
	return (0);
}