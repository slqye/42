/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:09:48 by slaye             #+#    #+#             */
/*   Updated: 2024/07/01 17:51:01 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"
#include "Bureaucrat.hpp"

int	main(void)
{
	// Working
	{
		try
		{
			Bureaucrat a("Robot", 1);
			std::cout << a << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
		try
		{
			Bureaucrat b("Robot", 150);
			std::cout << b << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	// Constructor grade exception
	{
		try
		{
			Bureaucrat a("Robot", 0);
			std::cout << a << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
		try
		{
			Bureaucrat b("Robot", 151);
			std::cout << b << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	// Functions grade exception
	{
		try
		{
			Bureaucrat a("Robot", 1);
			a.downgrade();
			a.upgrade();
			a.upgrade();
			std::cout << a << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
		try
		{
			Bureaucrat b("Robot", 150);
			b.upgrade();
			b.downgrade();
			b.downgrade();
			std::cout << b << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}