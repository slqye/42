/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:09:48 by slaye             #+#    #+#             */
/*   Updated: 2024/07/05 16:36:28 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

Base	*generate(void)
{
	srand(time(0));
	int	rd = rand() % 3;
	if (rd % 3 == 0)
		return (new A());
	else if (rd % 3 == 1)
		return (new B());
	else
		return (new C());
}

void	identify(Base* p)
{
	A *a = dynamic_cast<A *>(p);
	if (a != NULL)
	{
		std::cout << "A" << std::endl;
		return ;
	}
	B *b = dynamic_cast<B *>(p);
	if (b != NULL)
	{
		std::cout << "B" << std::endl;
		return ;
	}
	C *c = dynamic_cast<C *>(p);
	if (c != NULL)
	{
		std::cout << "C" << std::endl;
		return ;
	}
}

void	identify(Base& p)
{
	try
	{
		A& a = dynamic_cast< A& >( p );
		(void) a;
		std::cout << "A" << std::endl;
	}
	catch(const std::exception& e) {}
	try
	{
		B& b = dynamic_cast< B& >( p );
		(void) b;
		std::cout << "B" << std::endl;
	}
	catch( const std::exception& e ) {}
	try
	{
		C& c = dynamic_cast< C& >( p );
		(void) c;
		std::cout << "C" << std::endl;
	}
	catch( const std::exception& e ) {}
}

int	main(void)
{
	Base *random = generate();

	identify(random);
	identify(*random);
	delete random;
	return (0);
}