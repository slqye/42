/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:48:08 by uwywijas          #+#    #+#             */
/*   Updated: 2024/06/05 15:21:02 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal {
	public:
		Dog(void); // canonical
		Dog(Dog const &ref); // canonical
		~Dog(void); // canonical

		Dog	&operator=(Dog const &ref); // canonical

		void	makeSound(void) const;
	private:
		Brain	*_brain;
};

#endif
