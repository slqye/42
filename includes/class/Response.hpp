/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:33:05 by uwywijas          #+#    #+#             */
/*   Updated: 2024/10/25 16:16:26 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commons.hpp"
#include "Server.hpp"

class Server;

class Response {
	public:
		// Constructors / Destructors
		Response(Server *server, unsigned int code, std::string mime_type, std::string content);
		~Response(void);

		// Functions
		static std::string	getMimeType(const std::string &file_path);
		std::string			generate_header(void);
		std::string			generate_chunk(void);

		// Getters
		std::map<unsigned int, std::string>	getHttpCodes(void) const;
		bool								getState(void) const;

	private:
		// Variables
		std::map<unsigned int, std::string>	_http_codes;
		unsigned int						_code;
		std::string							_mime_type;
		std::string							_content;
		unsigned int						_mtu;
		std::map<int, std::string>			_error_pages;
		bool								_state;
};