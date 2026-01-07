/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:12:25 by uwywijas          #+#    #+#             */
/*   Updated: 2024/06/05 15:21:05 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Cat : public Animal {
	public:
		Cat(void); // canonical
		Cat(Cat const &ref); // canonical
		~Cat(void); // canonical

		Cat	&operator=(Cat const &ref); // canonical

		virtual void	makeSound(void) const;
	private:
		Brain	*_brain;
};

#endif
