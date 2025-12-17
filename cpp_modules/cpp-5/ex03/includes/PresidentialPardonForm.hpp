/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:58:56 by slaye             #+#    #+#             */
/*   Updated: 2024/07/02 16:49:40 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class PresidentialPardonForm : public AForm {
	public:
		PresidentialPardonForm(std::string target);
		PresidentialPardonForm(PresidentialPardonForm const &ref); // canonical
		virtual ~PresidentialPardonForm(void); // canonical

		PresidentialPardonForm	&operator=(PresidentialPardonForm const &ref); // canonical
		std::string				getTarget(void) const;
		void					execute(Bureaucrat const & executor) const;
	private:
		PresidentialPardonForm(void); // canonical
		std::string	_target;
};
