/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:55:35 by nlederge          #+#    #+#             */
/*   Updated: 2024/11/07 11:52:14 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include "commons.hpp"
#include "Server.hpp"
#include "Response.hpp"
#include "ConfigParser.hpp"
#include "Network.hpp"
#include "CGI.hpp"

#define CGI_ERROR -1
#define CGI_LOAD 0
#define CGI_DONE 1

class Response;
class Server;
class ConfigParser;
class Network;
class CGI;

struct client;
struct CGIProcess;

class Webserv {
	public:
		// Constructors / Destructors
		Webserv(void);
		virtual ~Webserv(void);

		// Functions
		void		configure(std::string config_file);
		void		start(void);
		void		listeners(void);
		void		unblock(unsigned int fd);
		void		connect(unsigned int fd);
		void		disconnect(unsigned int index);
		void		set_stop(void);
		void		removeCgi(int fd);
		bool		read_cgi(Server *server, int fd);
		bool		isServerFd(unsigned int fd);
		int			handle_errors(int index);
		bool		handle_pollin(int index, Network *network);
		bool		handle_pollin_error_client(int index, int code);
		int			handle_pollout(int index, Network *network);
		int			handle_pollout_cgi(int index);
		int			handle_pollout_new_client_response(int index, Network *network);
		int			handle_pollout_client_response(int index);
		int			handle_pollout_client_response_empty(int index, Network *network);
		std::string	remoteIp(const struct sockaddr_in& addr) const;
		Response	*process(Server *server, client *client);
		Response	*handle_get(Server *server, client *client, Location *location, bool override);
		Response	*handle_post(Server *server, client *client, Location *location);
		Response	*handle_delete(Server *server, client *client);
		Response	*handle_multipart_form_data(Server *server, client *client, Location *location);
		Response	*buildAutoIndexResponse(Server *server, std::string const &path);
		Response	*start_cgi(Server *server, client *client, CGI *cgi, std::string &file_path, bool isPOST);
		Response	*check_access_rights_get(Server *server, std::string file_path, bool &is_directory);
		Response	*check_access_rights_post(Server *server, std::string file_path);
		Response	*handle_directory_request(Server *server, client *client, Location *location, std::string &file_path);
		void		disconnect_cliend_with_cgi_fd(int cgi_fd);
		void		check_timeout(Network &network);

		// Setters
		void	set_cgi_state(CGIProcess *cgi);

		// Adders

		// Getters
		std::string	getRemoteIp(unsigned int fd);

		// Debug
		void	displayWebservConfig(void) const;

	private:
		// Variables
		std::vector<Server *>						_servers;
		std::vector<pollfd>							_server_fds;
		std::vector<pollfd>							_poll_fds;
		std::vector<int>							_cgi_done;
		std::map<int, int>							_client_to_cgi;
		std::map<int, int>							_cgi_to_client;
		std::map<int, Server *>						_client_to_server;
		std::map<int, Response *>					_client_response;
		std::map<int, std::string>					_client_ip;
		std::map<int, std::string>					_cgi_content;
		std::map<int, CGIProcess>					_cgis_process;
		std::map<int, std::time_t>					_client_timeout;
		Network										*_network;
		bool										_stop;

		// Functions
		std::string	getAutoIndex(std::string const &path, int &error_code) const;
};

#endif // WEBSERV_HPP