/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:32:05 by uwywijas          #+#    #+#             */
/*   Updated: 2024/11/04 11:16:07 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Log.hpp"

std::string	_default(void)
{
	time_t		current_time;
	struct tm	*local_time;
	char 		buffer[1024];
	std::string	result;

	std::memset(buffer, 0, 1024);
	current_time = time(0);
	local_time = localtime(&current_time);
	strftime(buffer, sizeof(buffer), "[%Y-%m-%d] [%H:%M:%S]\t", local_time);
	result = buffer;
	return (result);
}

void	Log::info(std::string value)
{
	std::cout << WHITE << _default() << "[INFO]\t\t" << value << RESET << std::endl;
}

void	Log::warning(std::string value)
{
	std::cout << YELLOW << _default() << "[WARNING]\t" << value << RESET << std::endl;
}

void	Log::error(std::string value)
{
	std::cerr << RED << _default() << "[ERROR]\t\t" << value << RESET << std::endl;
}

void	Log::debug(std::string value)
{
	std::cout << CYAN << _default() << "[DEBUG]\t\t" << value << RESET << std::endl;
}