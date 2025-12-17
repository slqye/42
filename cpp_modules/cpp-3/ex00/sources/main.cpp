/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:48:24 by slaye             #+#    #+#             */
/*   Updated: 2024/05/31 17:10:44 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void) {
	ClapTrap a;
	ClapTrap b("Robot 2");
	int		holder;

	a.beRepaired(0);
	holder = a.get_energy_points();
	std::cout << a.get_hit_points() << std::endl;
	for (int i = 0; i < holder; i++)
		a.attack(b.get_name());
	std::cout << a.get_name() << " has no more energy!" << std::endl;
	a.attack(b.get_name());
	a.beRepaired(1);
	a.takeDamage(101);
	std::cout << a.get_hit_points() << std::endl;
	return (0);
}