/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:34:05 by nlederge          #+#    #+#             */
/*   Updated: 2024/11/05 17:40:25 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/CGI.hpp"

CGI::CGI(void) :
	_extension(""),
	_pass("")
{
}

CGI::~CGI(void)
{
}

// Getters
std::string const	&CGI::getExtension(void) const { return (this->_extension); }
std::string const	&CGI::getPass(void) const { return (this->_pass); }

// Setters
void	CGI::setExtension(std::string const &extension) { this->_extension = extension; }
void	CGI::setPass(std::string const &pass) { this->_pass = pass; }

// Functions for parsing
bool	CGI::isComplete(void) const
{
	if (this->_extension.length() == 0) // extension is mandatory
		return (false);
	else if (this->_pass.length() == 0) // pass is mandatory
		return (false);
	return (true);
}

// Functions
CGIProcess	CGI::execute(Webserv *webserv, Server *server, client *client, std::string const &file_path, std::string const &data, bool isPOST)
{
	try
	{
		CGIExecutor cgi_executor(this, webserv, server, client, file_path, isPOST);
		return (cgi_executor.execute(isPOST ? data : ""));
	}
	catch (std::exception &e)
	{
		CGIProcess	cgi_process;
		cgi_process.pid = -1;
		cgi_process.fdout = -1;
		return (cgi_process);
	}
}

// Debug
void	CGI::displayCGIConfig(void) const
{
	std::cout << "		+ Extension: " << this->_extension << std::endl;
	std::cout << "		+ Pass: " << this->_pass << std::endl;
}