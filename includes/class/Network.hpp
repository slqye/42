/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:11:16 by uwywijas          #+#    #+#             */
/*   Updated: 2024/11/07 12:30:41 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_HPP
# define NETWORK_HPP

# include "commons.hpp"
# include "Webserv.hpp"
# include "Server.hpp"

// TODO: get smallest MTU from servers
// TODO: handle request in chunk format
	// parse header to see if its chunked
	// if header not found in first read, of size MTU, return error code 431
	// if yes, set a bool to true on that fd in a vector
	// next iteration, see if the bool is true on that fd
	// if yes, parse correctly the value (\r\n\r\n) etc...
// TODO: parse header to know to wich server is the request
// TODO: send request to the server with the correct server_name
// TODO: retrieve result of the server and send it back to client in a chunked format

class Server;

enum ParsingState {
	GET_HEADER,
	GET_CONTENT_LENGTH,
	GET_CHUNKED,
	ERROR,
	BAD_REQUEST,
	INTERNAL_SERVER_ERROR,
	DONE
};

enum ChunkParsingState {
	GET_CHUNK_SIZE,
	GET_CHUNK_DATA,
};

struct client {
	int									fd;
	int									status;
	std::map<std::string, std::string>	header_content;
	std::string 						content;
	std::string							tmp_content;
	enum ParsingState					parsing_state;
	enum ChunkParsingState				chunk_parsing_state;
	bool								process; // reads when false else process chunks
	unsigned long						bytes_to_read;
	size_t								content_size;
	bool								connection_close;
};

class Network {
	public:
		// Constructors / Destructors
		Network();
		virtual ~Network(void);

		// Functions
		void	clear_uncompleted_request(int fd);
		int		retrieve_block(unsigned int index, std::vector<pollfd>	&_poll_fds, Server *server);
		void	remove_parsed_request(unsigned int fd);

		// Setters

		// Getters
		unsigned int	getBacklog(void) const;
		unsigned int	getMtu(void) const;
		client			*get_parsed_request(unsigned int fd);

	private:
		// Variables
		std::map<unsigned int, client *>		_parsed_request;
		std::map<unsigned int, client *>		_client_infos;
		std::map<unsigned int, unsigned int>	_chunked_fds;
		unsigned int							_backlog;
		unsigned int							_mtu;

		// Functions
		// void	connect(void);
		bool	get_header(unsigned int index, client *current_client, std::vector<pollfd> &_poll_fds);
		bool	get_chunk_data(unsigned int index, client *current_client);
		bool	get_chunk_size(unsigned int index, client *current_client);
		bool	get_chunked(unsigned int index, client *current_client, std::vector<pollfd> &_poll_fds);
		bool	get_content_length(unsigned int index, client *current_client, std::vector<pollfd> &_poll_fds);
		int		copy_client_to_parsed_request(unsigned int index, client *current_client, std::vector<pollfd> &_poll_fds);
		void	erase_client(unsigned int index, std::vector<pollfd> &_poll_fds);
		void	config_client(unsigned int index, std::vector<pollfd> &_poll_fds);
		ssize_t	read_and_append_tmp_content(unsigned int index, client *current_client, size_t size_to_read, std::vector<pollfd> &_poll_fds);
		bool	parse_header(client *current_client);
};

#endif