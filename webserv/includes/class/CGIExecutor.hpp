/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIExecutor.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:47:45 by nlederge          #+#    #+#             */
/*   Updated: 2024/11/05 17:43:24 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIEXECUTOR_HPP
# define CGIEXECUTOR_HPP

# include "CGI.hpp"
# include "Webserv.hpp"
# include "Server.hpp"
# include "Network.hpp"

struct client;
struct CGIProcess;

class CGI;
class Webserv;
class Server;

class CGIExecutor
{
	private:
		CGI							*_cgi;
		char						**_env;
		char						**_argv;
		Webserv						*_webserv;
		Server						*_server;
		client						*_client;
		std::vector<std::string>	_env_vec;
		std::vector<std::string>	_argv_vec;
		std::string					_chdir_to;
		bool						_isPOST;

		char	**recreateEnv(void);
		void	storeEnv(void);
		char	**recreateArgv(void);
		void	storeArgv(std::string const &target);

	public:
		CGIExecutor(CGI *cgi, Webserv *webserv, Server *server, client *client, std::string const &file_path, bool isPOST);
		~CGIExecutor(void);

		// Functions
		CGIProcess		execute(const std::string &data);
};

#endif // CGIEXECUTOR_HPP
