/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:58:56 by slaye             #+#    #+#             */
/*   Updated: 2024/07/02 16:10:45 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class ShrubberyCreationForm : public AForm {
	public:
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(ShrubberyCreationForm const &ref); // canonical
		virtual ~ShrubberyCreationForm(void); // canonical

		ShrubberyCreationForm	&operator=(ShrubberyCreationForm const &ref); // canonical
		std::string				getTarget(void) const;
		void					execute(Bureaucrat const & executor) const;
	private:
		ShrubberyCreationForm(void); // canonical
		std::string	_target;
};
