/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:03:01 by uwywijas          #+#    #+#             */
/*   Updated: 2024/09/30 15:12:46 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Server.hpp"

// Constructors / Destructors / Operators

Server::Server(void) : _server_fd(0),
						_backlog(1000),
						_host(""),
						_port(0),
						_mtu(0)
{
}

Server::~Server(void)
{
}

Server	&Server::operator=(const Server &reference)
{
	this->_server_fd = reference.getServerFd();
	this->_backlog = reference.getBacklog();
	this->_host = reference.getHost();
	this->_port = reference.getPort();
	this->_server_names = reference.getServerNames();
	this->_error_pages = reference.getErrorPages();
	this->_mtu = reference.getMtu();
	this->_locations = reference.getLocations();
	return (*this);
}

// Setters
void	Server::setServerFd(int serverFd) { this->_server_fd = serverFd; }
void	Server::setBacklog(unsigned int backlog) { this->_backlog = backlog; }

// Setters for server config variables
void	Server::setHost(std::string host) { this->_host = host; }
void	Server::setPort(unsigned int port) { this->_port = port; }
void	Server::setMtu(unsigned int mtu) { this->_mtu = mtu; };
void	Server::addServerName(std::string server_name) { this->_server_names.push_back(server_name); }
void	Server::addErrorPage(int status_code, std::string error_page) { this->_error_pages.insert(std::make_pair(status_code, error_page)); }
void	Server::addLocation(std::string location_path, Location location) { this->_locations.insert(std::make_pair(location_path, location)); }

// Getters
unsigned int	Server::getBacklog(void) const { return (this->_backlog); }
int				Server::getServerFd(void) const { return (this->_server_fd); }
unsigned int	Server::getMtu(void) const { return (this->_mtu); }

// Getters for server config variables
std::string	const						&Server::getHost(void) const { return (this->_host); }
unsigned int							Server::getPort(void) const { return (this->_port); }
std::vector<std::string> const			&Server::getServerNames(void) const { return (this->_server_names); }
std::map<std::string, Location> const	&Server::getLocations(void) const { return (this->_locations); }
std::map<int, std::string> const		&Server::getErrorPages(void) const { return (this->_error_pages); }

// Functions for parsing
bool	Server::isComplete(void) const
{
	if (this->_host.length() == 0 || this->_port == 0)
		return (false);
	else if (this->_mtu == 0)
		return (false);
	else if (this->_locations.size() == 0)
		return (false);
	return (true);
}

static std::vector<size_t>	getSlashesPosition(std::string str)
{
	std::vector<size_t>	slash_positions;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '/')
			slash_positions.push_back(i);
	}
	return (slash_positions);
}

// Functions
Location	*Server::getLocation(std::string const &target)
{
	std::string	only_target = target.substr(0, target.find_first_of('?'));
	std::vector<size_t>	slash_positions = getSlashesPosition(only_target);
	for (std::map<std::string, Location>::iterator it = this->_locations.begin(); it != this->_locations.end(); it++)
	{
		for (size_t i = 0; i < slash_positions.size(); i++)
		{
			if (it->first == only_target.substr(0, slash_positions[i] + 1))
				return (&it->second);
		}
	}
	return (NULL);
}

// Debug
void	Server::displayServerConfig(void) const
{
	std::cout << "- Host: " << this->_host << std::endl;
	std::cout << "- Port: " << this->_port << std::endl;
	std::cout << "- Server names: ";
	for (std::vector<std::string>::const_iterator it = this->_server_names.begin(); it != this->_server_names.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "- Error pages: ";
	for (std::map<int, std::string>::const_iterator it = this->_error_pages.begin(); it != this->_error_pages.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	std::cout << "- Mtu: " << this->_mtu << std::endl;
	std::cout << "- Locations: " << std::endl;
	for (std::map<std::string, Location>::const_iterator it = this->_locations.begin(); it != this->_locations.end(); it++)
	{
		std::cout << "	* Location: " << it->first << std::endl;
		it->second.displayLocationConfig();
	}
}
