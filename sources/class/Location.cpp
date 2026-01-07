/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:34:20 by nlederge          #+#    #+#             */
/*   Updated: 2024/11/05 18:00:28 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Location.hpp"

Location::Location(void) :
	_route(""),
	_root(""),
	_allowedMethods(),
	_autoindex(false),
	_cgi(),
	_uploadsDirectory(""),
	_index("")
{
}

Location::~Location(void)
{
}

// Setters
void	Location::setAutoindex(bool autoindex) { this->_autoindex = autoindex; }
void	Location::setUploadsDirectory(std::string const &uploadsDirectory) { this->_uploadsDirectory = uploadsDirectory; }
void	Location::setAllowedMethods(unsigned int methods) { this->_allowedMethods = methods; }
void	Location::setIndex(std::string const &index) { this->_index = index; }
void	Location::setRoute(std::string const &route) { this->_route = route; }
void	Location::setRoot(std::string const &root) { this->_root = root; }

// Adders
void	Location::addRedirection(int code, std::string const &url) { this->_redirection[code] = url; }
void	Location::addCGI(CGI const &cgi) { this->_cgi.push_back(cgi); }

// Getters
unsigned int const					&Location::getAllowedMethods(void) const { return (this->_allowedMethods); }
std::map<int, std::string> const	&Location::getRedirection(void) const { return (this->_redirection); }
bool								Location::getAutoindex(void) const { return (this->_autoindex); }
std::vector<CGI> const				&Location::getCgi(void) const { return (this->_cgi); }
std::string const					&Location::getUploadsDirectory(void) const { return (this->_uploadsDirectory); }
std::string const					&Location::getIndex(void) const { return (this->_index); }
std::string const					&Location::getRoute(void) const { return this->_route; }
std::string const					&Location::getRoot(void) const { return this->_root; }

// Functions for parsing
bool	Location::isComplete(void)
{
	if (this->_route.empty() || this->_root.empty())
		return (false);
	if (this->_allowedMethods == 0 || this->_uploadsDirectory.length() == 0)
		return (false);
	if (this->_index.empty() && this->_autoindex == false)
		this->setAutoindex(true);
	if (this->_redirection.size() > 1)
		return (false);
	return (true);
}

// Functions
CGI	*Location::selectCGI(std::string const &target)
{
	std::string target_extension;
	size_t dot_pos = target.find_last_of('.');
	if (dot_pos == std::string::npos)
		return (NULL);
	else
		target_extension = target.substr(dot_pos);
	for (std::vector<CGI>::iterator it = this->_cgi.begin(); it != this->_cgi.end(); it++)
	{
		if (it->getExtension() == target_extension)
			return (&(*it));
	}
	return (NULL);
}

std::string	Location::getActualFilePath(std::string const &target)
{
	//remove the common charcaters between the route and the target
	std::string target_without_query_string = target.substr(0, target.find('?'));
	size_t	dcp = 0;
	for (size_t i = 0; i < this->_route.length() && i < target_without_query_string.length(); i++)
	{
		if (this->_route[i] == target_without_query_string[i])
			dcp++;
		else
			break;
	}
	std::string actualFilePath = this->_root + target_without_query_string.substr(dcp);
	return (actualFilePath);
}

bool	Location::isMainDirectory(std::string const &header_content_target)
{
	std::string target_without_query_string = header_content_target.substr(0, header_content_target.find('?'));
	return (target_without_query_string.length() == this->_route.length());
}

bool	Location::isInsideUploadsDirectory(std::string const &target)
{
	std::string location_uploads_directory = this->_route + this->_uploadsDirectory;
	if (target.substr(0, location_uploads_directory.length()) != location_uploads_directory || target == location_uploads_directory)
		return (false);
	return (true);
}

// Debug
void	Location::displayLocationConfig(void) const
{
	std::cout << "	* Route: " << this->_route << std::endl;
	std::cout << "	* Root: " << this->_root << std::endl;
	std::cout << "	* Allowed methods: ";
	if (this->_allowedMethods & GET)
		std::cout << "GET ";
	if (this->_allowedMethods & POST)
		std::cout << "POST ";
	if (this->_allowedMethods & DELETE)
		std::cout << "DELETE ";
	std::cout << std::endl;
	std::cout << "	* Redirections: ";
	for (std::map<int, std::string>::const_iterator it = this->_redirection.begin(); it != this->_redirection.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	std::cout << "	* Autoindex: " << this->_autoindex << std::endl;
	std::cout << "	* CGI: " << std::endl;
	for (std::vector<CGI>::const_iterator it = this->_cgi.begin(); it != this->_cgi.end(); it++)
		it->displayCGIConfig();
	std::cout << "	* Uploads directory: " << this->_uploadsDirectory << std::endl;
	std::cout << "	* Index: " << this->_index << std::endl; // Added index display
}
