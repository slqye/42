/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:23:20 by nlederge          #+#    #+#             */
/*   Updated: 2024/10/25 16:13:41 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

# include "commons.hpp"
# include "Webserv.hpp"
# include "Server.hpp"
# include "Location.hpp"

class Webserv;
class Server;
class Location;

class ConfigParser {

	private:
		std::string _config_content;
		std::vector<Server *> _servers;

		void parseServerBlock(const std::string& server_block);
		void parseLocationBlock(const std::string& location_block, Server& server);
		void parseCGIBlock(const std::string& cgi_block, Location& location);

	public:
		ConfigParser(const std::string& config_file);
		~ConfigParser(void);

		// Functions
		void parse(void);

		// Getters
		std::vector<Server *> getServers(void) const;
};

#endif // CONFIGPARSER_HPP
