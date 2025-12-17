/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:36:12 by uwywijas          #+#    #+#             */
/*   Updated: 2024/11/07 14:03:15 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Webserv.hpp"

// Constructors / Destructors
Webserv::Webserv(void) : _stop(false)
{
}

Webserv::~Webserv(void)
{
	for (std::vector<Server *>::iterator it = this->_servers.begin(); it != this->_servers.end(); it++)
		delete *it;
}

// Functions
void	Webserv::configure(std::string config_file)
{
	ConfigParser	parser(config_file);

	parser.parse();
	this->_servers = parser.getServers();
}

void	Webserv::check_timeout(Network &network)
{
	static long	max_duration = 10;
	std::time_t	current_time = std::time(NULL);
	std::map<int, std::time_t> holder = this->_client_timeout;

	for (std::map<int, std::time_t>::iterator i = holder.begin(); i != holder.end(); i++)
	{
		if (current_time - i->second >= max_duration)
		{
			// client timeout
			Log::warning("client timeout");
			int index = 0;
			for (std::vector<pollfd>::iterator j = this->_poll_fds.begin(); j != this->_poll_fds.end(); j++)
			{
				if (j->fd == i->first)
					break;
				index++;
			}
			network.clear_uncompleted_request(i->first);
			this->disconnect(index);
		}
	}
}

void	Webserv::start(void)
{
	Network	network;
	pollfd	current;
	int		rpoll;
	int		events;

	Log::info("starting servers");
	this->listeners();
	Log::info("servers started");
	this->_network = &network;
	while (true && !this->_stop)
	{
		this->check_timeout(network);
		rpoll = poll(this->_poll_fds.data(), this->_poll_fds.size(), -1);
		if (rpoll == -1)
		{
			Log::error("poll() function failed");
			continue;
		}
		events = 0;
		for (unsigned int index = 0; index < this->_poll_fds.size() && events < rpoll; index++)
		{
			current = this->_poll_fds[index];
			if (current.revents & (POLLERR | POLLHUP | POLLNVAL))
			{
				// socket error
				switch (this->handle_errors(index))
				{
					case (0): break;
					case (1): index--;
					case (2): index--; index--;
				}
				events++;
			}
			else if (current.revents & POLLIN)
			{
				if (this->handle_pollin(index, &network) == false)
					index--;
				events++;
			}
			else if (current.revents & POLLOUT)
			{
				switch (this->handle_pollout(index, &network))
				{
					case (0): break;
					case (1): index--; break;
					case (2): break;
					case (3): this->disconnect(index); index--; index--; break;
					case (4): this->disconnect(index); index--; break;
					case (5): this->disconnect(index); index--; break;
					case (6): this->disconnect(index); index--; break;
				}
				events++;
			}
		}
	}
	for (std::vector<pollfd>::iterator it = this->_poll_fds.begin(); it != this->_poll_fds.end(); it++)
	{
		close(it->fd);
	}
	Log::info("servers stopped");
}

void	Webserv::set_stop() {this->_stop = true;}

void	Webserv::disconnect_cliend_with_cgi_fd(int cgi_fd)
{
	for (unsigned int i = 0; i < this->_poll_fds.size(); i++)
	{
		if (this->_poll_fds[i].fd == this->_cgi_to_client[cgi_fd])
		{
			this->disconnect(i);
			break;
		}
	}
}

int	Webserv::handle_errors(int index)
{
	pollfd		current;
	std::string	chunk;
	Server		*server;
	int			client_fd;

	current = this->_poll_fds[index];
	if (this->_cgi_content.find(current.fd) != this->_cgi_content.end())
	{
		// cgi error
		client_fd = this->_cgi_to_client[current.fd];
		if (this->_cgis_process[client_fd].state != CGI_DONE)
			this->set_cgi_state(&this->_cgis_process[client_fd]);
		if (this->_cgis_process[client_fd].state == CGI_ERROR)
		{
			Log::error("cgi failed");
			server = this->_client_to_server.find(this->_cgi_to_client[current.fd])->second;
			this->_client_response.insert(std::make_pair(client_fd, new Response(server, 500, "text/html", "")));
			chunk = this->_client_response[client_fd]->generate_header();
			int r_send = send(client_fd, chunk.c_str(), chunk.length(), MSG_NOSIGNAL);
			if (r_send == -1)
			{
				Log::error("send() function failed");
				this->disconnect_cliend_with_cgi_fd(current.fd);
				this->removeCgi(current.fd);
				return (2);
			}
			else if (r_send == 0)
			{
				Log::info("connection closed by client");
				this->disconnect_cliend_with_cgi_fd(current.fd);
				this->removeCgi(current.fd);
				return (2);
			}
			this->removeCgi(current.fd);
			return (1);
		}
	}
	else
	{
		Log::error("socket error flag detected");
		this->disconnect(index);
		return (1);
	}
	return (0);
}

bool	Webserv::handle_pollin(int index, Network *network)
{
	pollfd	current;
	Server	*server;

	current = this->_poll_fds[index];
	if (this->isServerFd(current.fd))
	{
		// new client connection
		this->connect(current.fd);
	}
	else if (this->_cgi_content.find(current.fd) != this->_cgi_content.end())
	{
		// handling cgi POLLIN
		server = this->_client_to_server[this->_cgi_to_client[current.fd]];
		if (this->read_cgi(server, current.fd) == false)
		{
			// read error
			this->disconnect_cliend_with_cgi_fd(current.fd);
			this->removeCgi(current.fd);
			return (false);
		}
	}
	else
	{
		// handling client request
		std::time_t current_time = std::time(NULL);
		if (this->_client_timeout.find(current.fd) == this->_client_timeout.end())
			this->_client_timeout.insert(std::make_pair(current.fd, current_time));
		server = this->_client_to_server[current.fd];
		int holder = network->retrieve_block(index, this->_poll_fds, server);
		if (holder == INTERNAL_SERVER_ERROR)
			return (this->handle_pollin_error_client(index, 500));
		else if (holder == BAD_REQUEST)
			return (this->handle_pollin_error_client(index, 400));
		else if (holder == ERROR)
		{
			this->disconnect(index);
			return (false);
		}
	}
	return (true);
}

bool	Webserv::handle_pollin_error_client(int index, int code)
{
	std::string	chunk;
	pollfd		current;
	Server		*server;
	int			r_send;

	current = this->_poll_fds[index];
	server = this->_client_to_server[current.fd];
	try
	{
		this->_client_response.insert(std::make_pair(current.fd, new Response(server, code, "text/html", "")));
		chunk = this->_client_response[current.fd]->generate_header();
		r_send = send(current.fd, chunk.c_str(), chunk.length(), MSG_NOSIGNAL);
		if (r_send == -1)
		{
			Log::error("send() function failed");
			this->disconnect(index);
			return (false);
		}
		else if (r_send == 0)
		{
			Log::info("connection closed by client");
			this->disconnect(index);
			return (false);
		}
	}
	catch(const std::bad_alloc &e)
	{
		Log::error(e.what());
		this->disconnect(index);
		return (false);
	}
	return (true);
}

int	Webserv::handle_pollout(int index, Network *network)
{
	pollfd	current;

	current = this->_poll_fds[index];
	if (this->_client_to_cgi.find(current.fd) != this->_client_to_cgi.end())
	{
		// handling cgi result to client
		switch (this->handle_pollout_cgi(index))
		{
			case (0): break;
			case (1): return (1);
			case (2): return (2);
			case (3): return (3);
		}
	}
	else if (this->_client_response.find(current.fd) == this->_client_response.end())
	{
		// processing client request
		switch (this->handle_pollout_new_client_response(index, network))
		{
			case (0): break;
			case (1): return (4);
		}
	}
	else if (!this->_client_response[current.fd]->getState())
	{
		// sending response to client
		switch (handle_pollout_client_response(index))
		{
			case (0): break;
			case (1): return (5);
		}
	}
	else
	{
		// reponse sent, removing client
		switch (this->handle_pollout_client_response_empty(index, network))
		{
			case (0): break;
			case (1): return (6);
		}
	}
	return (0);
}

int	Webserv::handle_pollout_cgi(int index)
{
	std::string	chunk;
	pollfd		current;
	Server		*server;
	int			cgi_fd;

	current = this->_poll_fds[index];
	server = this->_client_to_server[current.fd];
	if (this->_cgis_process[current.fd].state != CGI_DONE)
		this->set_cgi_state(&this->_cgis_process[current.fd]);
	cgi_fd = this->_client_to_cgi[current.fd];
	if (this->_cgis_process[current.fd].state == CGI_ERROR)
	{
		Log::error("cgi failed");
		this->_client_response.insert(std::make_pair(current.fd, new Response(server, 500, "text/html", "")));
		chunk = this->_client_response[current.fd]->generate_header();
		this->removeCgi(cgi_fd);
		int r_send = send(current.fd, chunk.c_str(), chunk.length(), MSG_NOSIGNAL);
		if (r_send == -1)
		{
			Log::error("send() function failed");
			return (3);
		}
		else if (r_send == 0)
		{
			Log::info("connection closed by client");
			return (3);
		}
		return (1);
	}
	else if (this->_cgis_process[current.fd].state == CGI_LOAD)
		return (2);
	else if (this->_cgis_process[current.fd].state == CGI_DONE)
	{
		//Log::info("cgi successfully executed");
		if (std::find(this->_cgi_done.begin(), this->_cgi_done.end(), cgi_fd) != this->_cgi_done.end())
		{
			this->_client_response.insert(std::make_pair(current.fd, new Response(server, 200, "text/html", this->_cgi_content[cgi_fd])));
			chunk = this->_client_response[current.fd]->generate_header();
			this->removeCgi(cgi_fd);
			int r_send = send(current.fd, chunk.c_str(), chunk.length(), MSG_NOSIGNAL);
			if (r_send == -1)
			{
				Log::error("send() function failed");
				return (3);
			}
			else if (r_send == 0)
			{
				Log::info("connection closed by client");
				return (3);
			}
			return (1);
		}
	}
	return (0);
}

int	Webserv::handle_pollout_new_client_response(int index, Network *network)
{
	std::string	chunk;
	Response	*response;
	Server		*server;
	client		*client;
	pollfd		current;

	current = this->_poll_fds[index];
	server = this->_client_to_server.find(current.fd)->second;
	client = network->get_parsed_request(current.fd);
	if (client != NULL)
	{
		try
		{
			response = this->process(server, client);
		}
		catch (const std::bad_alloc &e)
		{
			// bad_alloc
			Log::error(e.what());
			return (1);
		}
		if (response == NULL)
		{
			// This is a cgi
			return (0);
		}
		this->_client_response.insert(std::make_pair(current.fd, response));
		chunk = this->_client_response[current.fd]->generate_header();
		int r_send = send(current.fd, chunk.c_str(), chunk.length(), MSG_NOSIGNAL);
		if (r_send == -1)
		{
			Log::error("send() function failed");
			return (1);
		}
		else if (r_send == 0)
		{
			Log::info("connection closed by client");
			return (1);
		}
	}
	return (0);
}

int	Webserv::handle_pollout_client_response(int index)
{
	std::string	chunk;
	pollfd		current;

	current = this->_poll_fds[index];
	chunk = this->_client_response[current.fd]->generate_chunk();
	int r_send = send(current.fd, chunk.c_str(), chunk.length(), MSG_NOSIGNAL);
	if (r_send == -1)
	{
		Log::error("send() function failed");
		return (1);
	}
	else if (r_send == 0)
	{
		Log::info("connection closed by client");
		return (1);
	}
	return (0);
}

int	Webserv::handle_pollout_client_response_empty(int index, Network *network)
{
	pollfd	current;
	client	*current_client;
	int		res = 0;

	current = this->_poll_fds[index];
	current_client = network->get_parsed_request(current.fd);
	if (current_client && current_client->connection_close)
		res = 1;
	delete this->_client_response[current.fd];
	this->_client_response[current.fd] = NULL;
	this->_client_response.erase(current.fd);
	network->remove_parsed_request(current.fd);
	return (res);
}

void	Webserv::listeners(void)
{
	std::vector<unsigned int>	ports;
	pollfd						pollfd;
	addrinfo					info, *res;
	Server						*server;
	int							fd;
	int							status;
	static int					optval = 1;

	for (unsigned int i = 0; i < this->_servers.size(); i++)
	{
		server = this->_servers[i];
		if (std::find(ports.begin(), ports.end(), server->getPort()) != ports.end())
		{
			Log::error("port already used by a server");
			continue;
		}
		ports.push_back(server->getPort());
		std::memset(&info, 0, sizeof(info));
		info.ai_family = AF_INET;
		info.ai_socktype = SOCK_STREAM;
		status = getaddrinfo(server->getHost().c_str(), numberToString(server->getPort()).c_str(), &info, &res);
		if (status != 0)
		{
			Log::error("getaddrinfo() function failed");
			continue;
		}
		fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (fd == -1)
		{
			Log::error("socket() function failed");
			continue;
		}
		if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) == -1)
		{
			Log::error("setsockopt() function failed");
			continue;
		}
		if (bind(fd, res->ai_addr, res->ai_addrlen) < 0)
		{
			Log::error("bind() function failed");
			continue;
		}
		freeaddrinfo(res);
		if (listen(fd, this->_servers[i]->getBacklog()) < 0)
		{
			Log::error("listen() function failed");
			continue;
		}
		this->unblock(fd);
		pollfd.fd = fd;
		pollfd.events = POLLIN;
		pollfd.revents = 0;
		this->_server_fds.push_back(pollfd);
		this->_poll_fds.push_back(pollfd);
		Log::info("new server started");
	}
}

void	Webserv::unblock(unsigned int fd)	
{
	int	flags;

	flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void	Webserv::connect(unsigned int fd)
{
	struct sockaddr_in	client_addr;
	socklen_t			client_len;
	pollfd				pollfd;
	int					socket;
	static int			option = 1;
	
	client_len = sizeof(client_addr);
	socket = accept(fd, (struct sockaddr*) &client_addr, &client_len);
	if (socket >= 0)
	{
		this->unblock(socket);
		pollfd.fd = socket;
		pollfd.events = POLLIN | POLLOUT;
		pollfd.revents = 0;
		if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)
		{
			Log::error("setsockopt() failed");
			return ;
		}
		this->_poll_fds.push_back(pollfd);
		for (unsigned int i = 0; i < this->_server_fds.size(); i++)
		{
			if (fd == static_cast<unsigned int>(this->_server_fds[i].fd))
				this->_client_to_server.insert(std::make_pair(pollfd.fd, this->_servers[i]));
		}
		this->_client_ip.insert(std::make_pair(socket, this->remoteIp(client_addr)));
		Log::info("new client connected");
	}
}

void	Webserv::disconnect(unsigned int index)
{
	int	del_fd = this->_poll_fds[index].fd;

	if (this->_client_response.find(del_fd) != this->_client_response.end())
	{
		delete this->_client_response[del_fd];
		this->_client_response[del_fd] = NULL;
		this->_client_response.erase(del_fd);
	}
	if (this->_client_ip.find(del_fd) != this->_client_ip.end())
		this->_client_ip.erase(del_fd);
	if (this->_client_to_server.find(del_fd) != this->_client_to_server.end())
		this->_client_to_server.erase(this->_client_to_server.find(del_fd));
	for (unsigned int i = 0; i < this->_poll_fds.size(); i++)
	{
		if (this->_poll_fds[i].fd == del_fd)
		{
			this->_poll_fds.erase(this->_poll_fds.begin() + i);
			break ;
		}
	}
	if (this->_client_to_cgi.find(del_fd) != this->_client_to_cgi.end())
	{
		this->removeCgi(this->_client_to_cgi[del_fd]);
		this->_client_to_cgi.erase(del_fd);
	}
	this->_network->remove_parsed_request(del_fd);
	this->_client_timeout.erase(del_fd);
	close(del_fd);
	Log::info("client disconnected");
}

bool	Webserv::isServerFd(unsigned int fd)
{
	for (unsigned int i = 0; i < this->_server_fds.size(); i++)
	{
		if (fd == static_cast<unsigned int>(this->_server_fds[i].fd))
			return (true);
	}
	return (false);
}

Response	*Webserv::process(Server *server, client *client)
{
	Location	*location;

	this->_client_timeout.erase(client->fd);
	location = server->getLocation(client->header_content["target"]);
	if (location)
		Log::info("Target: " + client->header_content["target"] + "; Location: " + location->getRoute() + " -> " + location->getRoot());
	if (!location)
		return (new Response(server, 404, "text/html", "")); //TODO: check if this is the correct response
	if (client->header_content["method"] == "GET")
		return (handle_get(server, client, location, false));
	else if (client->header_content["method"] == "POST")
		return (handle_post(server, client, location));
	else if (client->header_content["method"] == "DELETE")
		return (handle_delete(server, client));
	return (new Response(server, 400, "text/html", ""));
}

Response	*Webserv::start_cgi(Server *server, client *client, CGI *cgi, std::string &file_path, bool isPOST)
{
	CGIProcess	cgi_process;
	pollfd		pollfd;

	cgi_process = cgi->execute(this, server, client, file_path, client->content, isPOST);
	if (cgi_process.fdout == -1)
	{
		Log::error("CGI execution failed");
		return (new Response(server, 500, "text/html", ""));
	}
	this->unblock(cgi_process.fdout);
	pollfd.fd = cgi_process.fdout;
	pollfd.events = POLLIN | POLLOUT;
	pollfd.revents = 0;
	this->_client_to_cgi.insert(std::make_pair(client->fd, cgi_process.fdout));
	this->_cgi_to_client.insert(std::make_pair(cgi_process.fdout, client->fd));
	this->_cgi_content.insert(std::make_pair(cgi_process.fdout, ""));
	this->_poll_fds.push_back(pollfd);
	this->_cgis_process.insert(std::make_pair(client->fd, cgi_process));
	return (NULL);
}

Response	*Webserv::check_access_rights_get(Server *server, std::string file_path, bool &is_directory)
{
	struct stat	file_info;

	if (access(file_path.c_str(), F_OK) == -1)
		return (new Response(server, 404, "text/html", ""));
	else if (access(file_path.c_str(), R_OK) == -1)
		return (new Response(server, 403, "text/html", ""));
	else if (stat(file_path.c_str(), &file_info) == -1)
		return (new Response(server, 500, "text/html", ""));
	if (file_info.st_mode & S_IFDIR)
		is_directory = true;
	return (NULL);
}

Response	*Webserv::check_access_rights_post(Server *server, std::string file_path)
{
	if (access(file_path.c_str(), F_OK) == 0 && access(file_path.c_str(), W_OK) == -1)
		return (new Response(server, 403, "text/html", ""));
	return (NULL);
}

Response	*Webserv::handle_directory_request(Server *server, client *client, Location *location, std::string &file_path)
{
	bool isMainDirectory = location->isMainDirectory(client->header_content["target"]);
	if (isMainDirectory && location->getIndex().length() > 0)
	{
		if (!file_path.length() || file_path[file_path.length() - 1] != '/')
			file_path += '/';
		file_path += location->getIndex();
	}
	else if (isMainDirectory && location->getAutoindex())
		return (this->buildAutoIndexResponse(server, file_path));
	else if (!isMainDirectory && location->getAutoindex())
		return (this->buildAutoIndexResponse(server, file_path));
	else if (!isMainDirectory && !location->getAutoindex())
		return (new Response(server, 400, "text/html", ""));
	else
		return (new Response(server, 500, "text/html", ""));
	return (NULL);
}

Response	*Webserv::handle_get(Server *server, client *client, Location *location, bool override)
{
	Response					*temp_response;
	bool						is_directory = false;
	std::map<int, std::string>	redirections;
	CGI							*cgi;
	std::ifstream				file;
	std::string					file_path;
	std::string					holder;
	std::string					data;
	std::ifstream				file_stream;

	if (!override)
	{
		if (!(location->getAllowedMethods() & GET))
			return (new Response(server, 405, "text/html", ""));
		redirections = location->getRedirection();
		if (redirections.begin() != redirections.end())
			return (new Response(server, redirections.begin()->first, "text/html", redirections.begin()->second));
	}
	file_path = location->getActualFilePath(client->header_content["target"]);
	temp_response = this->check_access_rights_get(server, file_path, is_directory);
	if (temp_response)
		return (temp_response);
	if (is_directory)
	{
		temp_response = this->handle_directory_request(server, client, location, file_path);
		if (temp_response)
			return (temp_response);
	}
	Log::info("File_path: " + file_path);

	cgi = location->selectCGI(file_path);
	if (cgi)
		return (this->start_cgi(server, client, cgi, file_path, override));

	file.open(file_path.c_str());
	if (!file.good())
	{
		Log::warning("Requested file cannot be open");
		return (new Response(server, 404, "text/html", ""));
	}
	holder = "";
	while (getline(file, holder))
		data += holder + "\n";
	file.close();
	return (new Response(server, 200, Response::getMimeType(file_path), data));
}

void	parse_content_disposition(std::map<std::string, std::string> &content, std::string val)
{
	size_t	semi_colon_pos;
	size_t	equal_pos;

	semi_colon_pos = val.find(";");
	val.erase(0, semi_colon_pos + 2);
	while (semi_colon_pos != std::string::npos)
	{
		std::string	key;
		std::string	value;

		equal_pos = val.find("=");
		key = val.substr(0, equal_pos);
		val.erase(0, equal_pos + 1);
		semi_colon_pos = val.find(";");
		if (semi_colon_pos == std::string::npos)
			value = val.substr(1, val.size() - 2);
		else
		{
			value = val.substr(1, semi_colon_pos - 2);
			val.erase(0, semi_colon_pos + 2);
		}
		content[key] = value;
	}
}

Response	*Webserv::handle_multipart_form_data(Server *server, client *client, Location *location)
{
	std::string							boundary;
	size_t								pos = 0;
	size_t								boundary_start;
	size_t								boundary_end;
	size_t								boundary_size;
	std::string							line;

	boundary_start = client->header_content["Content-Type"].find("=");
	if (boundary_start == std::string::npos)
		return (new Response(server, 500, "text/html", ""));
	boundary = "--" + client->header_content["Content-Type"].substr(boundary_start + 1);
	boundary_size = boundary.size();
	pos = boundary_size + 1;
	while (true)
	{
		std::map<std::string, std::string>	content;
		std::stringstream	ss(client->content);
		getline(ss, line);
		while (getline(ss, line))
		{
			if (line == "\r")
			{
				pos = client->content.find("\r\n\r\n");
				client->content.erase(0, pos + 3);
				break;
			}
			size_t colon_pos = line.find(":");
			if (colon_pos != std::string::npos)
			{
				try
				{
					std::string _key = line.substr(0, colon_pos);
					std::string _value = line.substr(colon_pos + 2);
					std::size_t pos = _value.find_first_of('\r');
					if (pos != std::string::npos)
						_value.erase(pos, pos + 1);
					content[_key] = _value;
					if (_key.find("Content-Disposition") != std::string::npos)
						parse_content_disposition(content, _value);
				}
				catch (const std::out_of_range &e)
				{
					Log::error("substr out_of_range exception");
					return (new Response(server, 500, "text/html", ""));
				}
			}
		}
		boundary_end = client->content.find(boundary);
		if (boundary_end == std::string::npos)
			return (new Response(server, 200, "text/html", ""));
		content["body"] = client->content.substr(1, boundary_end - 3);
		if (content["name"] == "file")
		{
			for (size_t i = 0; i < content["filename"].size(); i++)
				if (content["filename"][i] == ' ')
					content["filename"][i] = '_';
			std::string		file_path = location->getActualFilePath(location->getUploadsDirectory() + content["filename"]);
			std::ifstream	rout_file(file_path.c_str());
			// opens the file to write data to it, overwrites any existing data
			std::ofstream	out_file;
			out_file.open(file_path.c_str(), std::ios::binary);
			if (!out_file)
			{
				Log::warning("Requested file cannot be open");
				return (new Response(server, 500, "text/html", ""));
			}
			out_file << content["body"];
			out_file.close();
		}
		else
			return (new Response(server, 400, "text/html", "Bad request, expected \"file\", got : " + content["name"]));
		if (boundary_end == client->content.find(boundary + "--"))
			return (new Response(server, 200, "text/html", "\"" + content["filename"] + "\" succesfully uploaded."));
	}
	return (new Response(server, 500, "text/html", ""));
}

Response	*Webserv::handle_post(Server *server, client *client, Location *location)
{
	Response	*temp_response;
	std::string	file_path;

	if (!(location->getAllowedMethods() & POST))
		return (new Response(server, 405, "text/html", ""));

	bool is_inside_uploads_directory = location->isInsideUploadsDirectory(client->header_content["target"]);

	if (!is_inside_uploads_directory) //If the target is not inside the uploads directory, whatever the file, handle_get will handle it properly
		return (this->handle_get(server, client, location, true));

	for (size_t i = 0; i < std::min(client->header_content["target"].find_first_of('?'), client->header_content["target"].size()); i++)
	{
		if (client->header_content["target"][i] == ' ')
			client->header_content["target"][i] = '_';
	}
	file_path = location->getActualFilePath(client->header_content["target"]);

	temp_response = this->check_access_rights_post(server, file_path);
	if (temp_response)
		return (temp_response);

	Log::info("Upload file path: " + file_path);
	try
	{
		std::string content_type = client->header_content["Content-Type"];

		// if (client->content_size > 10000) // max content size of 10mb
		// 	return (Response(server, 413, "text/html", "Request Size Too Large").getChunks());
		if (content_type.find("multipart/form-data") != std::string::npos)
			return (handle_multipart_form_data(server, client, location));
		else if (content_type == "text/plain" ||
					content_type == "text/html" ||
					content_type == "application/octet-stream" ||
					content_type == "application/pdf" ||
					content_type == "application/zip" ||
					content_type.substr(0, 6) == "image/" ||
					content_type == "application/problem+json" ||
					content_type == "application/problem+xml")
		{
			// checks if the file already exist to determine the correct response code
			bool file_exist;
			std::ifstream	rout_file(file_path.c_str());
			file_exist = rout_file.good();
			if (file_exist) rout_file.close();
			// opens the file to write data to it, overwrites any existing data
			std::ofstream	out_file;
			out_file.open(file_path.c_str(), std::ios::binary);
			if (!out_file)
			{
				Log::warning("Requested file cannot be open: " + file_path);
				return (new Response(server, 500, "text/html", ""));
			}
			out_file << client->content;
			out_file.close();
			// returns 200 OK 201 FILE CREATED
			return (new Response(server, file_exist ? 200 : 201, "text/html", ""));
		}
		else
		{
			Log::error("Unknown Content-Type: " + content_type);
			return (new Response(server, 400, "text/html", ""));
		}
	}
	catch (std::exception& e)
	{
		std::string error_message = "Error processing POST content: " + std::string(e.what());
		Log::error(error_message);
	}
	return (new Response(server, 500, "text/html", ""));
}

Response	*Webserv::handle_delete(Server *server, client *client)
{
	std::vector<std::string>	result;
	std::string					file_path;
	Location					*location;

	location = server->getLocation(client->header_content["target"]);
	if (!(location->getAllowedMethods() & DELETE))
		return (new Response(server, 405, "text/html", ""));
	file_path = location->getActualFilePath(client->header_content["target"]);
	if (access(file_path.c_str(), F_OK) == -1)
	{
		Log::warning("file does't exist, could not delete " + file_path);
		return (new Response(server, 404, "text/html", ""));
	}
	if (std::remove(file_path.c_str()) != 0)
	{
		Log::warning("permissions forbidden, could not delete " + file_path);
		return (new Response(server, 403, "text/html", ""));
	}
	else
	{
		Log::info("successfully deleted " + file_path);
		return (new Response(server, 204, "text/html", ""));
	}
} 

std::string			Webserv::remoteIp(const struct sockaddr_in& addr) const
{
	std::stringstream stream;
	uint32_t ip = ntohl(addr.sin_addr.s_addr);
	
	stream << ((ip >> 24) & 0xFF) << ".";
	stream << ((ip >> 16) & 0xFF) << ".";
	stream << ((ip >> 8) & 0xFF) << ".";
	stream << (ip & 0xFF);
	
	return (stream.str());
}

bool				Webserv::read_cgi(Server *server, int fd)
{
	char	buffer[server->getMtu() + 1];
	int		reads;

	std::memset(buffer, 0, server->getMtu() + 1);
	reads = read(fd, buffer, server->getMtu());
	if (reads == -1)
	{
		Log::error("cgi read() failed");
		return (false);
	}
	else if (reads == 0)
		this->_cgi_done.push_back(fd);
	else if (reads < static_cast<int>(server->getMtu()))
	{
		this->_cgi_content[fd].append(buffer, reads);
		this->_cgi_done.push_back(fd);
	}
	else
		this->_cgi_content[fd].append(buffer, reads);
	return (true);
}

void				Webserv::set_cgi_state(CGIProcess *cgi)
{
	int		status;
	int		r_waitpid;

	r_waitpid = waitpid(cgi->pid, &status, WNOHANG);
	if (r_waitpid > 0 && WIFEXITED(status) == 1 && WEXITSTATUS(status) == 0)
		cgi->state = CGI_DONE;
	else if (r_waitpid == 0)
		cgi->state = CGI_LOAD;
	else if (r_waitpid == -1)
		cgi->state = CGI_ERROR;
	else if (WIFEXITED(status) == 1 && WEXITSTATUS(status) != 0)
		cgi->state = CGI_ERROR;
	else
		cgi->state = CGI_DONE;
}

void				Webserv::removeCgi(int fd)
{
	if (this->_cgi_to_client.find(fd) == this->_cgi_to_client.end())
		return ;
	Log::info("removing cgi");
	if (std::find(this->_cgi_done.begin(), this->_cgi_done.end(), fd) != this->_cgi_done.end())
		this->_cgi_done.erase(std::find(this->_cgi_done.begin(), this->_cgi_done.end(), fd));
	this->_cgi_content.erase(fd);
	this->_client_to_cgi.erase(this->_cgi_to_client[fd]);
	this->_cgis_process.erase(this->_cgi_to_client[fd]);
	this->_cgi_to_client.erase(fd);
	for (unsigned int i = 0; i < this->_poll_fds.size(); i++)
	{
		if (this->_poll_fds[i].fd == fd)
		{
			this->_poll_fds.erase(this->_poll_fds.begin() + i);
			return ;
		}
	}
	close(fd);
}

std::string			Webserv::getAutoIndex(std::string const &path, int &error_code) const
{
	struct dirent*	entry;
	std::string		header;
	std::string		result;
	std::string		holder;
	DIR*			dir;

	dir = opendir(path.c_str());
	if (dir == NULL && !access(path.c_str(), F_OK))
	{
		error_code = 403;
		Log::error("Forbidden access to directory " + path);
		return ("");
	}
	else if (dir == NULL)
	{
		error_code = 404;
		Log::error("Directory not found " + path);
		return ("");
	}
	header = "<html><head><title>autoindex</title></head><body><ul>";
	std::string prefix = path.length() > 1 && path[path.length() - 1] != '/' ? path.substr(path.find_last_of('/') + 1) + "/" : "./";
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type != DT_DIR)
		{
			holder = entry->d_name;
			result += "<li><a href='" + prefix + holder + "'>" + holder + "</a></li>";
		}
	}
	closedir(dir);
	if (result.empty())
		result = "<li>No files found</li>";
	result += "</ul></html>";
	return (header + result);
}

Response	*Webserv::buildAutoIndexResponse(Server *server, std::string const &path)
{
	std::string	content;
	int			error_code = 200;

	content = this->getAutoIndex(path, error_code);
	if (error_code != 200)
		return (new Response(server, error_code, "text/html", ""));
	return (new Response(server, 200, "text/html", content));
}

// Adders

// Getters

std::string			Webserv::getRemoteIp(unsigned int fd)
{
	if (this->_client_ip.find(fd) == this->_client_ip.end())
		return ("127.0.0.1");
	return (this->_client_ip[fd]);
}

// Debug
void	Webserv::displayWebservConfig(void) const
{
	std::vector<Server *>::const_iterator	it;
	int	i = 0;

	Log::debug("webserv configuration:");
	it = this->_servers.begin();
	while (it != this->_servers.end())
	{
		std::cout << "Server " << i << " configuration:" << std::endl;
		(*it)->displayServerConfig();
		it++;
		i++;
	}
}