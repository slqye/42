/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:44:02 by slaye             #+#    #+#             */
/*   Updated: 2024/06/05 15:15:47 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>

class Brain {
	public:
		Brain(void); // canonical
		Brain(Brain const &ref); // canonical
		virtual ~Brain(void); // canonical

		Brain	&operator=(Brain const &ref); // canonical

		std::string	*getIdeas(void);
	private:
		std::string	_ideas[100];
};

#endif
