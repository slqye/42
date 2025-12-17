/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:08:09 by slaye             #+#    #+#             */
/*   Updated: 2024/05/31 14:52:33 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
	public:
		FragTrap(void); // canonical
		FragTrap(std::string name);
		FragTrap(FragTrap const &ref); // canonical
		~FragTrap(void); // canonical

		FragTrap	&operator=(FragTrap const &ref); // canonical

		void		highFivesGuys(void) const;
};

#endif
