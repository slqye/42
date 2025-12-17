/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIExecutor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:49:41 by nlederge          #+#    #+#             */
/*   Updated: 2024/11/05 18:14:03 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/CGIExecutor.hpp"

CGIExecutor::CGIExecutor(CGI *cgi, Webserv *webserv, Server *server, client *client, std::string const &file_path, bool isPOST)
{
	this->_cgi = cgi;
	this->_webserv = webserv;
	this->_server = server;
	this->_client = client;
	this->_isPOST = isPOST;

	size_t temp_pos = _client->header_content["target"].find_last_of('/');
	size_t temp_pos_2 = _client->header_content["target"].find_first_of('?');
	std::string target_filename;
	if (temp_pos != std::string::npos)
		target_filename = _client->header_content["target"].substr(temp_pos + 1, temp_pos_2 - temp_pos - 1);
	else
		target_filename = _client->header_content["target"].substr(0, temp_pos_2);
	
	temp_pos = file_path.find_last_of('/');
	if (temp_pos != std::string::npos)
		_chdir_to = file_path.substr(0, temp_pos + 1);
	else
		_chdir_to = file_path;

	storeArgv(target_filename);
	storeEnv();

	try
	{
		this->_argv = recreateArgv();
	}
	catch (std::exception &e)
	{
		throw std::runtime_error("Failed to recreate argv or env");
	}
	try
	{
		this->_env = recreateEnv();
	}
	catch (std::exception &e)
	{
		delete [] _argv;
		throw std::runtime_error("Failed to recreate argv or env");
	}
}

CGIExecutor::~CGIExecutor(void)
{
	delete [] _argv;
	delete [] _env;
}

// Added execution methods
void	CGIExecutor::storeEnv(void)
{
	size_t temp_pos;
	std::string temp_str;

	_env_vec.push_back("SERVER_SOFTWARE=Webserv/1.0");
	_env_vec.push_back("GATEWAY_INTERFACE=CGI/1.1");
	temp_pos = _client->header_content["target"].find("?");
	_env_vec.push_back("PATH_INFO=" + _client->header_content["target"]);
	temp_str = this->_isPOST ? "POST" : "GET";
	_env_vec.push_back("REQUEST_METHOD=" + temp_str);
	_env_vec.push_back("SCRIPT_NAME=" + _cgi->getPass());
	if (temp_pos != std::string::npos)
		_env_vec.push_back("QUERY_STRING=" + _client->header_content["target"].substr(temp_pos + 1));
	else
		_env_vec.push_back("QUERY_STRING=");
	_env_vec.push_back("REDIRECT_STATUS=200");
	_env_vec.push_back("CONTENT_TYPE=" + stripWhiteSpaces(_client->header_content["Content-type"]));
	temp_str = this->_isPOST ? numberToString(_client->content_size) : "0";
	_env_vec.push_back("CONTENT_LENGTH=" + temp_str);
	_env_vec.push_back("SERVER_PROTOCOL=HTTP/1.1");
	_env_vec.push_back("SERVER_SOFTWARE=Webserv/1.0");
	_env_vec.push_back("REMOTE_ADDR=" + _webserv->getRemoteIp(_client->fd));
	temp_str = stripWhiteSpaces(_client->header_content["Host"]);
	temp_pos = temp_str.find(":");
	if (temp_pos != std::string::npos)
	{
		_env_vec.push_back("SERVER_NAME=" + temp_str.substr(0, temp_pos));
		_env_vec.push_back("SERVER_PORT=" + temp_str.substr(temp_pos + 1, temp_str.length()));
	}
}

char	**CGIExecutor::recreateEnv(void)
{
	char **env = new char*[_env_vec.size() + 1];
	for (size_t i = 0; i < _env_vec.size(); i++)
		env[i] = const_cast<char*>(_env_vec[i].c_str());
	env[_env_vec.size()] = NULL;
	return (env);
}

void	CGIExecutor::storeArgv(std::string const &target)
{
	_argv_vec.push_back(_cgi->getPass());
	_argv_vec.push_back(target);
}

char **CGIExecutor::recreateArgv(void)
{
	char **argv = new char*[_argv_vec.size() + 1];
	for (size_t i = 0; i < _argv_vec.size(); i++)
		argv[i] = const_cast<char*>(_argv_vec[i].c_str());
	argv[_argv_vec.size()] = NULL;
	return (argv);
}

CGIProcess CGIExecutor::execute(const std::string &data)
{
	CGIProcess	cgi_process;
	cgi_process.pid = -1;
	cgi_process.fdout = -1;

	int pipe_fdin[2];
	int pipe_fdout[2];

	if (pipe(pipe_fdin) == -1)
		return (cgi_process);
	if (pipe(pipe_fdout) == -1)
	{
		close(pipe_fdin[0]);
		close(pipe_fdin[1]);
		return (cgi_process);
	}
	
	pid_t pid = fork();
	if (pid == -1)
	{
		close(pipe_fdin[0]);
		close(pipe_fdin[1]);
		close(pipe_fdout[0]);
		close(pipe_fdout[1]);
		return (cgi_process);
	}
	else if (pid == 0) // Child process
	{
		close(pipe_fdin[1]);
		close(pipe_fdout[0]);

		dup2(pipe_fdin[0], STDIN_FILENO);
		close(pipe_fdin[0]);
		dup2(pipe_fdout[1], STDOUT_FILENO);
		close(pipe_fdout[1]);

		if (chdir(_chdir_to.c_str()) < 0)
		{
			std::exit(EXIT_FAILURE);
		}
		if (execve(_argv[0], _argv, _env) < 0)
		{
			std::exit(EXIT_FAILURE);
		}
	}
	else // Parent process
	{
		close(pipe_fdin[0]);
		close(pipe_fdout[1]);

		if (!data.empty())
		{
			write(pipe_fdin[1], data.c_str(), data.length());
		}
		close(pipe_fdin[1]);
		cgi_process.fdout = pipe_fdout[0];
		cgi_process.pid = pid;
		cgi_process.state = CGI_LOAD;
		return (cgi_process);
	}
	return (cgi_process);
}