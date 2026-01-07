/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:05:41 by slaye             #+#    #+#             */
/*   Updated: 2024/07/04 15:45:40 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class Intern {
	public:
		Intern(void); // canonical
		Intern(Intern const &ref); // canonical
		virtual ~Intern(void); // canonical

		Intern	&operator=(Intern const &ref); // canonical
		AForm	*makeForm(std::string name, std::string target);
};
