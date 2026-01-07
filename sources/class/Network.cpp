/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:12:55 by uwywijas          #+#    #+#             */
/*   Updated: 2024/11/07 14:03:55 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Network.hpp"

// Constructors / Destructors
Network::Network() : _backlog(10), _mtu(1024)
{
}

Network::~Network(void)
{
}

// extract content from tmp_content and appends it to content
void extract_and_erase(client *current_client, size_t begin, size_t end)
{
	try
	{
		// Ensure 'end' is not less than 'begin' to prevent negative length
		if (end < begin)
		{
			Log::error("extract_and_erase: Invalid range");
			current_client->parsing_state = INTERNAL_SERVER_ERROR;
			return;
		}

		// Check if 'begin' and 'end' are within bounds
		if (begin > current_client->tmp_content.size() || end > current_client->tmp_content.size())
		{
			Log::error("extract_and_erase: Out of bounds");
			current_client->parsing_state = INTERNAL_SERVER_ERROR;
			return;
		}

		std::string tmp_string = current_client->tmp_content.substr(begin, end - begin);
		current_client->content.append(tmp_string);
		current_client->tmp_content.erase(begin, end - begin);
	}
	catch (const std::out_of_range &e)
	{
		Log::error("extract_and_erase: std::out_of_range exception");
		current_client->parsing_state = INTERNAL_SERVER_ERROR;
	}
}

// reads size_to_read and appends it directly to tmp_content
// returns -1 on read error, -2 from unrecoverable errors and 0 on empty read
// sets parsing state to DONE when an unrecoverable error happens or 0 bytes are read
ssize_t Network::read_and_append_tmp_content(unsigned int index, client *current_client, size_t size_to_read, std::vector<pollfd> &_poll_fds)
{
	char buffer[size_to_read + 1];
	ssize_t bytes_read = 0;

	std::memset(buffer, 0, size_to_read + 1);
	bytes_read = read(_poll_fds[index].fd, buffer, size_to_read);

	if (bytes_read == -1)
	{
		Log::error("read() function failed");
		current_client->parsing_state = ERROR;
		return (bytes_read);
	}
	else if (bytes_read == 0)
	{
		Log::info("client closed connection");
		current_client->parsing_state = ERROR;
		return (bytes_read);
	}

	try
	{
		current_client->tmp_content.append(buffer, bytes_read);
	}
	catch (const std::length_error &e)
	{
		Log::error("tmp_content append failed: length_error");
		current_client->parsing_state = INTERNAL_SERVER_ERROR;
		return (-2);
	}
	catch (const std::exception &e)
	{
		Log::error("tmp_content append failed: exception");
		current_client->parsing_state = INTERNAL_SERVER_ERROR;
		return (-2);
	}
	return (bytes_read);
}

void	parse_request_line(client *current_client, std::string request_line)
{
	std::stringstream			ss(request_line);
	std::vector<std::string>	parts;
	std::string					part;

	while (ss >> part)
		parts.push_back(part);
	if (parts.size() >= 1)
		current_client->header_content["method"] = parts[0];
	if (parts.size() == 2)
	{
		current_client->header_content["http_version"] = parts[1];
	}
	else if (parts.size() == 3)
	{
		current_client->header_content["target"] = parts[1];
		current_client->header_content["http_version"] = parts[2];
	}
}

// Extract each line of the header and store it into a map
bool	Network::parse_header(client *current_client)
{
	std::stringstream ss(current_client->tmp_content);
	std::string line;

	if (std::getline(ss, line) && line != "\r")
	{
		current_client->header_content["request_line"] = line;
		parse_request_line(current_client, current_client->header_content["request_line"]);
	}

	while (std::getline(ss, line) && line != "\r")
	{
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
				current_client->header_content[_key] = _value;
			}
			catch (const std::out_of_range &e)
			{
				Log::error("substr out_of_range exception");
				current_client->parsing_state = INTERNAL_SERVER_ERROR;
				return (true);
			}
		}
	}

	// Check if header end is found
	size_t header_end_pos = current_client->tmp_content.find("\r\n\r\n");
	if (header_end_pos != std::string::npos)
	{
		current_client->tmp_content.erase(0, header_end_pos + 4); // remove
	}
	else
	{
		Log::error("header end not found");
		current_client->parsing_state = BAD_REQUEST;
		return (true);
	}
	if (current_client->header_content.find("Content-Length") != current_client->header_content.end())
	{
		std::istringstream iss(current_client->header_content["Content-Length"]);
		if (!isNumber(current_client->header_content["Content-Length"]) || !(iss >> current_client->bytes_to_read))
		{
			Log::warning("invalid Content-Length");
			current_client->parsing_state = BAD_REQUEST;
			return (true);
		}
		current_client->parsing_state = GET_CONTENT_LENGTH;
	}
	else if (current_client->header_content.find("Transfer-Encoding") != current_client->header_content.end())
	{
		if (current_client->header_content["Transfer-Encoding"].find("chunked") != std::string::npos)
		{
			current_client->parsing_state = GET_CHUNKED;
			current_client->chunk_parsing_state = GET_CHUNK_SIZE;
		}
		else
		{
			Log::warning("unsupported Transfer-Encoding");
			current_client->parsing_state = BAD_REQUEST;
			return (true);
		}
	}
	else
	{
		if (current_client->header_content["method"] == "GET" || current_client->header_content["method"] == "DELETE")
		{
			current_client->parsing_state = DONE;
			return (true);
		}
		Log::warning("require Content-Length or Transfer-Encoding");
		current_client->parsing_state = BAD_REQUEST;
		return (true);
	}
	current_client->process = true;
	return (false);
}

// read the stream until the end of the header is found
bool Network::get_header(unsigned int index, client *current_client, std::vector<pollfd> &_poll_fds)
{
	ssize_t bytes_read = read_and_append_tmp_content(index, current_client, this->getMtu(), _poll_fds);
	if (bytes_read == -2 || bytes_read == 0)
		return (true);
	else if (bytes_read == -1)
		return (false);

	if (current_client->tmp_content.empty()) // Je sais plus ce que je check ici
	{
		Log::error("no content");
		return (false);
	}

	if (current_client->tmp_content.find("\r\n\r\n") != std::string::npos)
		return (parse_header(current_client));

	return (false);
}

bool Network::get_chunk_size(unsigned int index, client *current_client)
{
	(void)index;
	if (current_client->tmp_content.find("\r\n") == std::string::npos) // reads to get the chunk size in tmp_content
	{
		current_client->process = false; // request a read
		return (false);
	}
	std::stringstream ss(current_client->tmp_content);
	std::string line;

	if (std::getline(ss, line)) // extract the first line (which should be the line with the chunk size)
	{
		std::istringstream iss(line);
		iss >> std::hex >> current_client->bytes_to_read; // converts the hex size to decimal
		if (iss.fail())
		{
			Log::error("invalid chunk size");
			current_client->parsing_state = BAD_REQUEST;
			return (true);
		}
	}
	try
	{
		current_client->tmp_content.erase(0, line.size() + 1);
	}
	catch (const std::out_of_range &e)
	{
		Log::error("get_chunk_size: erase out_of_range exception");
		current_client->parsing_state = INTERNAL_SERVER_ERROR;
		return (true);
	}
	if (current_client->bytes_to_read == 0)
	{
		current_client->parsing_state = DONE;
		return (true);
	}

	current_client->chunk_parsing_state = GET_CHUNK_DATA;
	return (false);
}

bool Network::get_chunk_data(unsigned int index, client *current_client)
{
	(void)index;
	size_t end_of_chunk = current_client->tmp_content.find("\r\n");
	size_t tmp_content_size = current_client->tmp_content.size();

	if (end_of_chunk != std::string::npos && end_of_chunk != current_client->bytes_to_read) // chunk is not of the specified size
	{
		Log::error("invalid chunk size");
		current_client->parsing_state = BAD_REQUEST;
		return (true);
	}
	else if (end_of_chunk == std::string::npos && tmp_content_size > current_client->bytes_to_read) // chunk is incomplete but bigger than the specified size
	{
		Log::error("invalid chunk size");
		current_client->parsing_state = BAD_REQUEST;
		return (true);
	}
	else if (end_of_chunk == std::string::npos && tmp_content_size < current_client->bytes_to_read) // chunk is incomplete but smaller than the specified size, reads the data needed to complete the chunk
	{
		current_client->process = false; // request a read
	}
	else if (end_of_chunk != std::string::npos) // the chunk is complete and of the correct size, extracts the chunk and erase "\r\n"
	{
		extract_and_erase(current_client, 0, end_of_chunk);
		try
		{
			current_client->tmp_content.erase(0, 2);
		}
		catch (const std::out_of_range &e)
		{
			Log::error("get_chunk_data: erase out_of_range exception");
			current_client->parsing_state = INTERNAL_SERVER_ERROR;
			return (true);
		}
		current_client->chunk_parsing_state = GET_CHUNK_SIZE;
	}
	else // in case of unknown data size, reads until we have something (Might not be needed)
	{
		current_client->process = false;
	}
	return (false);
}

bool	Network::get_chunked(unsigned int index, client *current_client, std::vector<pollfd> &_poll_fds)
{
	if (current_client->process == false)
	{
		ssize_t bytes_read = read_and_append_tmp_content(index, current_client, this->getMtu(), _poll_fds);
		if (bytes_read == -2 || bytes_read == 0)
			return (true); // disconnected
		else if (bytes_read == -1)
			return (true);
	}

	current_client->process = true;
	while (current_client->process == true)
	{
		if (current_client->chunk_parsing_state == GET_CHUNK_SIZE)
		{
			// Log::warning("get_chunk_size()");
			if (get_chunk_size(index, current_client))
				return (true);
		}
		if (current_client->chunk_parsing_state == GET_CHUNK_DATA)
		{
			// Log::warning("get_chunk_data()");
			if (get_chunk_data(index, current_client))
				return (true);
		}
	}
	return (false);
}

// reads until there is the correct amount of data in tmp_content then extracts it to content
bool Network::get_content_length(unsigned int index, client *current_client, std::vector<pollfd> &_poll_fds)
{
	size_t tmp_content_size = current_client->tmp_content.size();

	if (tmp_content_size > current_client->bytes_to_read)
	{
		Log::error("received more data than Content-Length"); // explicit
		current_client->parsing_state = BAD_REQUEST;
		return (true);
	}
	else if (tmp_content_size < current_client->bytes_to_read && current_client->process == false) // If there is still data left to read
	{
		size_t read_size = current_client->bytes_to_read - tmp_content_size;
		ssize_t bytes_read = read_and_append_tmp_content(index, current_client, read_size, _poll_fds);
		if (bytes_read == -2 || bytes_read == 0)
			return (false); // disconnected
		else if (bytes_read == -1)
			return (false);
		tmp_content_size = current_client->tmp_content.size();
		current_client->process = true;
	}
	if (tmp_content_size == current_client->bytes_to_read) // when there is the required amount of data, extract it to content
	{
		extract_and_erase(current_client, 0, tmp_content_size);
		current_client->parsing_state = DONE;
		return (true);
	}
	current_client->process = false;
	return (false);
}

void	Network::config_client(unsigned int index, std::vector<pollfd> &_poll_fds)
{
	client *new_client = new client();

	new_client->parsing_state = GET_HEADER;
	new_client->fd = _poll_fds[index].fd;
	new_client->connection_close = false;
	this->_client_infos.insert(std::make_pair(_poll_fds[index].fd, new_client));
}

int	Network::retrieve_block(unsigned int index, std::vector<pollfd> &_poll_fds, Server *server)
{
	// sets up new client struct if it does not exist in the map yet
	this->_mtu = server->getMtu();
	if (this->_client_infos.find(_poll_fds[index].fd) == this->_client_infos.end())
	{
		try
		{
			config_client(index, _poll_fds);
		}
		catch (const std::bad_alloc &e)
		{
			Log::error("retrieve_block() failed");
			return (1);
		}
	}
	
	client *current_client = this->_client_infos[_poll_fds[index].fd];

	if (current_client->parsing_state == GET_HEADER)
	{
		get_header(index, current_client, _poll_fds);
	}
	if (current_client->parsing_state == GET_CHUNKED)
	{
		get_chunked(index, current_client, _poll_fds);
	}
	if (current_client->parsing_state == GET_CONTENT_LENGTH) // Does not return length, it's simply named after the setting
	{
		get_content_length(index, current_client, _poll_fds);
	}
	if (current_client->parsing_state == ERROR)
	{
		this->erase_client(index, _poll_fds);
		return (ERROR);
	}
	if (current_client->parsing_state == BAD_REQUEST
		|| current_client->parsing_state == INTERNAL_SERVER_ERROR)
	{
		current_client->content_size = current_client->content.size();
		return (copy_client_to_parsed_request(index, current_client, _poll_fds));
	}
	if (current_client->parsing_state == DONE) // traiter la requete rajouter ERROR state
	{
		// add client_info to new client map
		if (current_client->header_content["Connection"] == "close")
			current_client->connection_close = true;
		current_client->content_size = current_client->content.size();
		return (copy_client_to_parsed_request(index, current_client, _poll_fds));
	}
	return (DONE);
}

int	Network::copy_client_to_parsed_request(unsigned int index, client *current_client, std::vector<pollfd> &_poll_fds)
{
	client *new_client;
	unsigned int	fd = _poll_fds[index].fd;
	try
	{
		new_client = new client;
	}
	catch (const std::bad_alloc &e)
	{
		current_client->parsing_state = INTERNAL_SERVER_ERROR;
		this->erase_client(index, _poll_fds);
		return (ERROR);
	}
	new_client->parsing_state = current_client->parsing_state;
	new_client->header_content = current_client->header_content;
	new_client->content = current_client->content;
	new_client->content_size = current_client->content_size;
	new_client->fd = current_client->fd;
	new_client->connection_close = current_client->connection_close;
	this->_parsed_request.insert(std::make_pair(fd, new_client));
	this->erase_client(index, _poll_fds);
	return (new_client->parsing_state);
}

void	Network::remove_parsed_request(unsigned int fd)
{
	if (this->_parsed_request.find(fd) != this->_parsed_request.end())
	{
		delete this->_parsed_request[fd];
		this->_parsed_request.erase(fd);
	}
}

void	Network::erase_client(unsigned int index, std::vector<pollfd> &_poll_fds)
{
	if (this->_client_infos.find(_poll_fds[index].fd) != this->_client_infos.end())
	{
		client *tmp = this->_client_infos[_poll_fds[index].fd];
		this->_client_infos.erase(_poll_fds[index].fd);
		delete tmp;
	}
}

void	Network::clear_uncompleted_request(int fd)
{
	if (this->_client_infos.find(fd) != this->_client_infos.end())
	{
		client *tmp = this->_client_infos[fd];
		this->_client_infos.erase(fd);
		delete tmp;
	}
}

// Setters


// Getters
client			*Network::get_parsed_request(unsigned int fd)
{
	if (this->_parsed_request.find(fd) == this->_parsed_request.end())
		return (NULL);
	return (this->_parsed_request.find(fd)->second);
}
unsigned int	Network::getBacklog(void) const { return (this->_backlog); }
unsigned int	Network::getMtu(void) const { return (this->_mtu); }
