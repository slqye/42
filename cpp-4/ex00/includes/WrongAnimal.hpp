/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:33:25 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/31 18:39:40 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>

class WrongAnimal {
	public:
		WrongAnimal(void); // canonical
		WrongAnimal(WrongAnimal const &ref); // canonical
		virtual		~WrongAnimal(void); // canonical

		WrongAnimal	&operator=(WrongAnimal const &ref); // canonical

		std::string		getType(void) const;
		void	makeSound(void) const;

	protected:
		std::string	_type;
};

#endif
