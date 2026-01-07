/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:24:04 by uwywijas          #+#    #+#             */
/*   Updated: 2024/11/07 10:55:15 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_HPP
# define COMMONS_HPP

// c++ library
# include <iostream>
# include <algorithm>
# include <map>
# include <vector>
# include <sstream>
# include <ctime>
# include <fstream>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <string>
# include <iomanip>
# include <iterator>

// c library
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <errno.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <poll.h>
# include <sys/time.h>
# include <netdb.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <netinet/tcp.h>

// Errors
# define ERROR_UNDEFINED "undefined"
# define ERROR_ARGS "wrong number of arguments"
# define ERROR_SOCKET_CREATE "socket failed"
# define ERROR_SOCKET_OPTION "socket options failed"
# define ERROR_SOCKET_BIND "socket binding failed"
# define ERROR_SOCKET_LISTEN "socket listening failed"
# define ERROR_SOCKET_READ "socket reading failed"
# define ERROR_POLL "poll failed"

// Colors
# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BOLD "\033[1m"

// Values
# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

// Class
# include "class/Log.hpp"

// Utils
# include "utils.hpp"

// GET, POST, DELETE
# define GET 0x01
# define POST 0x02
# define DELETE 0x04

#endif