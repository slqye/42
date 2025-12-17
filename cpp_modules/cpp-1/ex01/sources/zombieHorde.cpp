/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:05:30 by slaye             #+#    #+#             */
/*   Updated: 2024/05/20 14:52:53 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

Zombie* zombieHorde(int N, std::string name) {
	if (N <= 0)
		return (NULL);
	Zombie* zombies = new Zombie[N];

	for (int i = 0; i < N; i++)
		zombies[i].set_name(name);
	return (zombies);
}