/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:34:55 by uwywijas          #+#    #+#             */
/*   Updated: 2024/06/05 14:32:52 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
	public:
		WrongCat(void); // canonical
		WrongCat(WrongCat const &ref); // canonical
		~WrongCat(void); // canonical

		WrongCat	&operator=(WrongCat const &ref); // canonical

		void	makeSound(void) const;
};

#endif
