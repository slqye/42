/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:26:50 by nlederge          #+#    #+#             */
/*   Updated: 2024/10/25 15:39:31 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"
#include "class/Webserv.hpp"
#include "class/Network.hpp"

Webserv webserv;

void	handle_sigint(int param)
{
	(void)param;
	webserv.set_stop();
}

int	main(int argc, char **argv)
{

	try
	{
		if (argc < 2)
			webserv.configure("config/webserv.conf");
		else
			webserv.configure(argv[1]);
		signal(SIGINT, handle_sigint);
		webserv.start();
	}
	catch (const std::exception& e)
	{
		Log::error(e.what());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}