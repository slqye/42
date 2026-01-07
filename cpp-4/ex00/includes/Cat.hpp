/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:12:25 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/31 18:28:16 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal {
	public:
		Cat(void); // canonical
		Cat(Cat const &ref); // canonical
		~Cat(void); // canonical

		Cat	&operator=(Cat const &ref); // canonical

		virtual void	makeSound(void) const;
};

#endif
