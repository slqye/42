/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:34:16 by nlederge          #+#    #+#             */
/*   Updated: 2024/11/05 17:40:53 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "commons.hpp"
# include "Network.hpp"
# include "Webserv.hpp"
# include "CGIExecutor.hpp"

struct client;

class Webserv;
class Server;
class CGIExecutor;

struct CGIProcess
{
	pid_t	pid;
	int		fdout;
	int		state;
};

class CGI
{
	private:
		std::string _extension;
		std::string _pass;

	public:
		CGI(void);
		~CGI(void);

		// Getters
		std::string const &getExtension(void) const;
		std::string const &getPass(void) const;

		// Setters
		void setExtension(std::string const &extension);
		void setPass(std::string const &pass);

		// Functions

		CGIProcess	execute(Webserv *webserv, Server *server, client *client, std::string const &file_path, std::string const &data, bool isPOST);
		
		// Functions for parsing
		bool isComplete(void) const;

		// Debug
		void displayCGIConfig(void) const;
};

#endif // CGI_HPP
