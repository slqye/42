/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:08:21 by slaye             #+#    #+#             */
/*   Updated: 2024/07/02 16:48:41 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

Intern::Intern(void)
{
}

Intern::Intern(Intern const &ref)
{
	*this = ref;
}

Intern	&Intern::operator=(Intern const &ref)
{
	(void) ref;
	return (*this);
}

AForm	*makeShrubberyCreationForm(std::string target)
{
	return (new ShrubberyCreationForm(target));
}

AForm	*makeRobotomyRequestForm(std::string target)
{
	return (new RobotomyRequestForm(target));
}

AForm	*makePresidentialPardonForm(std::string target)
{
	return (new PresidentialPardonForm(target));
}

AForm	*Intern::makeForm(std::string name, std::string target)
{
	AForm	*(*forms[3])(std::string target) = {&makeShrubberyCreationForm, &makeRobotomyRequestForm, &makePresidentialPardonForm};
	std::string	names[3] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};

	for (size_t i = 0; i < 3; i++)
	{
		if (name == names[i])
		{
			std::cout << "Intern creates " << name << std::endl;
			return (forms[i](target));
		}
	}
	std::cerr << "Form name don't exist" << std::endl;
	return (NULL);
}

Intern::~Intern(void)
{
}