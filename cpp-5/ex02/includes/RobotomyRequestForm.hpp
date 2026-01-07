/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:58:56 by slaye             #+#    #+#             */
/*   Updated: 2024/07/02 16:50:12 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class RobotomyRequestForm : public AForm {
	public:
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(RobotomyRequestForm const &ref); // canonical
		virtual ~RobotomyRequestForm(void); // canonical

		RobotomyRequestForm	&operator=(RobotomyRequestForm const &ref); // canonical
		std::string				getTarget(void) const;
		void					execute(Bureaucrat const & executor) const;
	private:
		RobotomyRequestForm(void); // canonical
		std::string	_target;
};
