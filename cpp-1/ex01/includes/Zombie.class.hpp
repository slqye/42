/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:00:23 by slaye             #+#    #+#             */
/*   Updated: 2024/05/15 16:46:06 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_CLASS_H
# define ZOMBIE_CLASS_H

# include "commons.hpp"

class Zombie {
	public:
		Zombie(void);
		~Zombie(void);
		void	announce(void) const;
		void	set_name(std::string name);
	private:
		std::string	name;
};

#endif