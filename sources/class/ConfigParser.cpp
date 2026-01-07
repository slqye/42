/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:31:33 by nlederge          #+#    #+#             */
/*   Updated: 2024/11/06 16:28:35 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/ConfigParser.hpp"

ConfigParser::ConfigParser(const std::string& config_file)
{
	std::ifstream file(config_file.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Unable to read config file.");
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	this->_config_content = buffer.str();
	file.close();
}

ConfigParser::~ConfigParser(void)
{
}

static bool trimmedGetline(std::istream& is, std::string& line)
{
	if (!std::getline(is, line))
		return false;

	line.erase(0, line.find_first_not_of(" \t"));
	line.erase(line.find_last_not_of(" \t") + 1);

	return true;
}

static bool check_remaining_content_on_line(std::istringstream& line_stream)
{
	std::string key;
	line_stream >> key;
	if (key.empty())
		return false;
	return true;
}

static bool is_valid_listen_directive(const std::string& listen)
{
	size_t colon_pos = listen.find(':');
	if (colon_pos == std::string::npos)
		return false;
	std::string host = listen.substr(0, colon_pos);
	std::string port_str = listen.substr(colon_pos + 1);

	if (host.empty() || port_str.empty())
		return false;
	if (!isNumber(port_str) || port_str.length() > 5 || stringToNumber<int>(port_str) < 0 || stringToNumber<int>(port_str) > 65535)
		return false;
	return true;
}

void ConfigParser::parseServerBlock(const std::string& server_block)
{
	Server				server;
	std::istringstream	iss(server_block);
	std::string 		line;
	std::string 		location_block;
	int					braces_count = 0;

	while (trimmedGetline(iss, line)) {
		if (line.empty()) {
			continue;
		}

		std::istringstream line_stream(line);
		std::string key;
		line_stream >> key;

		if (key == "listen") {
			std::string listen;
			line_stream >> listen;
			if (server.getHost().length() > 0 || server.getPort() != 0)
				throw std::runtime_error("Duplicate listen directive in server block: " + listen);
			else if (!is_valid_listen_directive(listen))
				throw std::runtime_error("Invalid listen directive: " + listen);
			else if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in server block after listen directive: " + line);
			server.setHost(listen.substr(0, listen.find(':')));
			server.setPort(stringToNumber<int>(listen.substr(listen.find(':') + 1)));
			listen.clear();
		}
		else if (key == "server_names") {
			std::string server_name;
			if (server.getServerNames().size() > 0)
				throw std::runtime_error("Duplicate server_names directive in server block: " + server_name);
			line_stream >> server_name;
			while (server_name.length() > 0)
			{
				server.addServerName(server_name);
				server_name.clear();
				line_stream >> server_name;
			}
			server_name.clear();
		}
		else if (key == "error_page") {
			std::string error_code;
			line_stream >> error_code;
			if (!isNumber(error_code) || error_code.length() > 3 || stringToNumber<int>(error_code) < 0 || stringToNumber<int>(error_code) > 999)
				throw std::runtime_error("Invalid error code: " + error_code);
			std::string error_page;
			line_stream >> error_page;
			if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in server block after error_page directive: " + line);
			server.addErrorPage(stringToNumber<int>(error_code), error_page);
			error_code.clear();
			error_page.clear();
		}
		else if (key == "mtu") {
			std::string mtu_string;
			line_stream >> mtu_string;
			if (!isNumber(mtu_string) || mtu_string.length() > 10 || stringToNumber<int>(mtu_string) < 1024 || stringToNumber<long>(mtu_string) > 1000000)
				throw std::runtime_error("Invalid MTU value: " + mtu_string);
			server.setMtu(stringToNumber<int>(mtu_string));
			if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in server block after mtu directive: " + line);
			mtu_string.clear();
		}
		else if (key == "location")
		{
			if (line != "location")
				throw std::runtime_error("Unexpected content in server block after location keyword: " + line);
			trimmedGetline(iss, line);
			if (line == "{")
				braces_count++;
			else
				throw std::runtime_error("Unexpected content in server block after location keyword: " + line);
			while (trimmedGetline(iss, line))
			{
				if (line == "{")
					braces_count++;
				else if (line == "}")
				{
					braces_count--;
					if (braces_count == 0)
					{
						this->parseLocationBlock(location_block, server);
						location_block.clear();
						break;
					}
				}
				if (braces_count != 0)
					location_block += "\n" + line;
			}
			line.clear();
		}
		else {
			throw std::runtime_error("Unknown directive in server block: \"" + key + "\"");
		}
		key.clear();
	}
	Server	*server_ptr = new Server(server);
	this->_servers.push_back(server_ptr);
}

static int	check_redirection_code(const std::string& redirection_code)
{
	int	int_code = stringToNumber<int>(redirection_code);
	if (!isNumber(redirection_code) || redirection_code.length() > 3 || int_code < 0 || int_code > 999)
		return (-1);
	else if (int_code != 301 && int_code != 302 && int_code != 303 && int_code != 307 && int_code != 308)
		return (-1);
	return (int_code);
}

void ConfigParser::parseLocationBlock(const std::string& location_block, Server& server)
{
	Location location;
	std::istringstream iss(location_block);
	std::string line;
	std::string cgi_block;
	bool autoindex_set = false;
	int braces_count = 0;

	while (trimmedGetline(iss, line)) {
		if (line.empty()) {
			continue;
		}
		std::istringstream line_stream(line);
		std::string key;
		line_stream >> key;

		if (key == "route") {
			std::string route;
			line_stream >> route;
			if (location.getRoute().length() > 0)	
				throw std::runtime_error("Duplicate route directive in location block: " + route);
			if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in location block after route directive: " + line);
			location.setRoute(route);
			route.clear();
		}
		else if (key == "root") {
			std::string root;
			line_stream >> root;
			if (location.getRoot().length() > 0)
				throw std::runtime_error("Duplicate root directive in location block: " + root);
			else if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in location block after root directive: " + line);
			location.setRoot(root);
			root.clear();
		}
		else if (key == "allow") {
			std::string allowed_method;
			line_stream >> allowed_method;
			unsigned int methods = 0;
			if (location.getAllowedMethods() > 0)
				throw std::runtime_error("Duplicate allow directive in location block: " + line);
			else if (allowed_method.length() == 0)
				throw std::runtime_error("Expected method after allow directive in location block: " + line);
			while (allowed_method.length() > 0)
			{
				if (allowed_method != "GET" && allowed_method != "POST" && allowed_method != "DELETE")
					throw std::runtime_error("Invalid method in allow directive in location block: " + allowed_method);
				methods |= (allowed_method == "GET") ? GET : 0;
				methods |= (allowed_method == "POST") ? POST : 0;
				methods |= (allowed_method == "DELETE") ? DELETE : 0;
				allowed_method.clear();
				line_stream >> allowed_method;
			}
			location.setAllowedMethods(methods);
			allowed_method.clear();
		}
		else if (key == "redirection") {
			std::string redirection_code;
			line_stream >> redirection_code;
			int int_redirection_code = check_redirection_code(redirection_code);
			if (int_redirection_code == -1)
				throw std::runtime_error("Invalid redirection code in location block: " + redirection_code);
			std::string redirection_url;
			line_stream >> redirection_url;
			if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in location block after redirection url: " + line);
			location.addRedirection(int_redirection_code, redirection_url);
			int_redirection_code = -1;
			redirection_code.clear();
			redirection_url.clear();
		}
		else if (key == "autoindex") {
			std::string autoindex;
			line_stream >> autoindex;
			if (autoindex_set)
				throw std::runtime_error("Duplicate autoindex directive in location block: " + line);
			else if (autoindex == "on")
				location.setAutoindex(true);
			else if (autoindex == "off")
				location.setAutoindex(false);
			else if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in location block after autoindex directive: " + line);
			else
				throw std::runtime_error("Invalid autoindex value: " + autoindex);
			autoindex_set = true;
			autoindex.clear();
		}
		else if (key == "uploads_directory") {
			std::string uploads_directory;
			line_stream >> uploads_directory;
			if (location.getUploadsDirectory().length() > 0)
				throw std::runtime_error("Duplicate uploads_directory directive in location block: " + line);
			else if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in location block after uploads_directory directive: " + line);
			location.setUploadsDirectory(uploads_directory);
			uploads_directory.clear();
		}
		else if (key == "index") {
			std::string index;
			line_stream >> index;
			if (location.getIndex().length() > 0)
				throw std::runtime_error("Duplicate index directive in location block: " + index);
			else if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in location block after index directive: " + line);
			location.setIndex(index);
			index.clear();
		}
		else if (key == "cgi")
		{
			if (line != "cgi")
				throw std::runtime_error("Unexpected content in location block after cgi keyword: " + line);
			trimmedGetline(iss, line);
			if (line == "{")
				braces_count++;
			else
				throw std::runtime_error("Unexpected content in location block after cgi keyword: " + line);
			while (trimmedGetline(iss, line))
			{	
				if (line == "{")
					braces_count++;
				else if (line == "}")
				{
					braces_count--;
					if (braces_count == 0)
					{
						this->parseCGIBlock(cgi_block, location);
						cgi_block.clear();
						break;
					}
				}
				if (braces_count != 0)
					cgi_block += "\n" + line;
			}
			line.clear();
		}
		else {
			throw std::runtime_error("Unknown directive in location block: \"" + key + "\"");
		}
		key.clear();
	}
	
	if (!location.isComplete() || !autoindex_set)
		throw std::runtime_error("Incomplete location block: " + location_block);
	server.addLocation(location.getRoute(), location);
}

void ConfigParser::parseCGIBlock(const std::string& cgi_block, Location& location)
{
	CGI cgi;
	std::istringstream iss(cgi_block);
	std::string line;

	while (trimmedGetline(iss, line))
	{
		if (line.empty())
			continue;

		std::istringstream line_stream(line);
		std::string key;
		line_stream >> key;

		if (key == "extension")
		{
			std::string extension;
			line_stream >> extension;
			if (cgi.getExtension().length() > 0)
				throw std::runtime_error("Duplicate extension directive in cgi block: " + extension);
			else if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in cgi block after extension directive: " + line);
			else if (extension.find_last_of('.') != 0 || extension.length() < 2 || !(extension == ".py" || extension == ".php")) 
				throw std::runtime_error("Invalid extension directive in cgi block: " + extension);
			cgi.setExtension(extension);
			extension.clear();
		}
		else if (key == "pass")
		{
			std::string pass;
			line_stream >> pass;
			if (cgi.getPass().length() > 0)
				throw std::runtime_error("Duplicate pass directive in cgi block: " + pass);
			else if (check_remaining_content_on_line(line_stream))
				throw std::runtime_error("Unexpected content in cgi block after pass directive: " + line);
			else if (!(pass == "/usr/bin/python3" || pass == "/usr/bin/php"))
				throw std::runtime_error("Invalid pass directive in cgi block: " + pass);
			cgi.setPass(pass);
			pass.clear();
		}
		else
			throw std::runtime_error("Unknown directive in cgi block: \"" + key + "\"");
		key.clear();
	}

	if (!cgi.isComplete())
		throw std::runtime_error("Incomplete cgi block: " + cgi_block);
	location.addCGI(cgi);
}

void ConfigParser::parse(void)
{
	std::istringstream iss(this->_config_content);
	std::string line;
	std::string server_block;
	int braces_count = 0;

	while (trimmedGetline(iss, line))
	{
		if (line.empty())
			continue;
		if (line == "server")
		{
			trimmedGetline(iss, line);
			if (line == "{")
				braces_count++;
			else
				throw std::runtime_error("Unexpected content after server keyword: " + line);
			while (trimmedGetline(iss, line))
			{	
				if (line == "{")
					braces_count++;
				else if (line == "}")
				{
					braces_count--;
					if (braces_count == 0)
					{
						this->parseServerBlock(server_block);
						server_block.clear();
						break;
					}
				}
				if (braces_count != 0)
					server_block += "\n" + line;
			}
			line.clear();
		}
		else
			throw std::runtime_error("Unexpected content in configuration file: " + line);
	}

	if (braces_count != 0 || server_block.length() > 0)
		throw std::runtime_error("Unclosed server block in configuration file.");

	std::string remaining;
	if (std::getline(iss, remaining)) {
		if (!remaining.empty()) {
			throw std::runtime_error("Unexpected content in configuration file.");
		}
	}
}

// Getters
std::vector<Server *> ConfigParser::getServers(void) const { return (this->_servers); }
