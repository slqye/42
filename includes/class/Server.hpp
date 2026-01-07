/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:37:08 by uwywijas          #+#    #+#             */
/*   Updated: 2024/09/30 15:11:27 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "commons.hpp"
#include "Location.hpp"

class Location;
class Response;

class Server {
	public:
		// Constructors / Destructors / Operators
		Server(void);
		virtual ~Server(void);
		Server &operator=(const Server &reference);

		// Setters
		void	setServerFd(int serverFd);
		void	setBacklog(unsigned int backlog);

		// Setters for server config variables
		void	setHost(std::string host);
		void	setPort(unsigned int port);
		void	setMtu(unsigned int mtu);
		void	addServerName(std::string serverName);
		void	addErrorPage(int statusCode, std::string path);
		void	addLocation(std::string path, Location location);

		// Getters
		unsigned int	getBacklog(void) const;
		int				getServerFd(void) const;

		// Getters for server config variables
		std::map<std::string, Location>	const &getLocations(void) const;
		std::map<int, std::string>		const &getErrorPages(void) const;
		std::vector<std::string>		const &getServerNames(void) const;
		unsigned int					getPort(void) const;
		unsigned int					getMtu(void) const;
		std::string	const				&getHost(void) const;

		// Functions
		Location	*getLocation(std::string const &target);

		// Functions for parsing
		bool	isComplete(void) const;

		// Debug
		void	displayServerConfig(void) const;

	private:
		// Variables
 		int													_server_fd;
		unsigned int										_backlog;
		// Server config variables
		std::string 										_host;
		unsigned int										_port;
		std::vector<std::string> 							_server_names;
		std::map<int, std::string> 							_error_pages;
		unsigned int 										_mtu;
		std::map<std::string, Location> 					_locations;
};

#endif // SERVER_HPP