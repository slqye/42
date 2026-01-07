/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:48:24 by slaye             #+#    #+#             */
/*   Updated: 2024/06/05 15:36:35 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int	main(void) {
	int	size = 10;
	Animal *array[size];

	std::cout << "Creation." << std::endl;
	for (int i = 0; i < size; i++) {
		if (i < size / 2)
			array[i] = new Cat();
		else
			array[i] = new Dog();
		if (i != size - 1)
			std::cout << std::endl;
	}
	
	std::cout << std::endl << "Tests." << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << array[i]->getType() << std::endl;
		array[i]->makeSound();
	}

	std::cout << std::endl << "Destruction." << std::endl;
	for (int i = 0; i < size; i++) {
		delete array[i];
		if (i != size - 1)
			std::cout << std::endl;
	}
	return (0);
}