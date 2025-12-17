/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:09:48 by slaye             #+#    #+#             */
/*   Updated: 2024/07/04 15:36:38 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

int	main(void)
{
	{
		Intern	intern;
		AForm *form = intern.makeForm("ShrubberyCreationForm", "TEST");
		Bureaucrat ceo("Ceo", 1);
		Bureaucrat random("Random", 136);

		std::cout << form << std::endl;
		std::cout << ceo << std::endl;
		std::cout << random << std::endl;
		try
		{
			ceo.signForm(*form);
			ceo.executeForm(*form);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		delete form;
	}
	return (0);
}