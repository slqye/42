/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:48:08 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/31 18:31:03 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"

class Dog : public Animal {
	public:
		Dog(void); // canonical
		Dog(Dog const &ref); // canonical
		~Dog(void); // canonical

		Dog	&operator=(Dog const &ref); // canonical

		void	makeSound(void) const;
};

#endif
