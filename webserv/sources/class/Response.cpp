/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:37:10 by uwywijas          #+#    #+#             */
/*   Updated: 2024/10/28 16:17:48 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "class/Response.hpp"
#include "class/Server.hpp"

// Constructors / Destructors
Response::Response(Server *server, unsigned int code, std::string mime_type, std::string content)
{
	this->_mtu = server->getMtu();
	this->_error_pages = server->getErrorPages();
	this->_code = code;
	this->_mime_type = mime_type;
	this->_content = content;
	this->_http_codes = getHttpCodes();
	this->_state = false;
}

Response::~Response(void)
{
}

std::string	Response::generate_header(void)
{
	std::map<int, std::string>	errors_pages;
	std::ifstream				file;
	std::stringstream			stream;
	std::string					header;
	std::string					chunk;
	std::string					line;
	std::string					page;

	if (this->_http_codes.find(this->_code) == this->_http_codes.end())
		this->_code = 500;
	if (this->_code == 301 || this->_code == 302 || this->_code == 304 || this->_code == 305 || this->_code == 307 || this->_code == 308)
	{
		// redirection
		stream << this->_code;
		header = "HTTP/1.1 " + stream.str() + " " + this->_http_codes[this->_code] + "\r\n";
		header += "Location: " + this->_content + "\r\n";
		header += "Content-Type: " + this->_mime_type + "\r\n"; //TODO: need to retrieve correct MIME type
		header += "Transfer-Encoding: chunked\r\n"; //TODO: Select correct transfer-encoding based on size
		header += "\r\n";
		this->_content = "";
	}
	else
	{
		stream << this->_code;
		header = "HTTP/1.1 " + stream.str() + " " + this->_http_codes[this->_code] + "\r\n";
		header += "Content-Type: " + this->_mime_type + "\r\n"; //TODO: need to retrieve correct MIME type
		header += "Transfer-Encoding: chunked\r\n"; //TODO: Select correct transfer-encoding based on size
		header += "Connection: keep-alive\r\n";
		header += "\r\n";
		errors_pages = this->_error_pages;
		if (this->_content == "" && errors_pages.find(this->_code) != errors_pages.end())
		{
			file.open(errors_pages[this->_code].c_str());
			if (!file.good())
				Log::error("requested error page cannot be open");
			else
			{
				page = "";
				while (getline(file, line))
					page += line + '\n';
				file.close();
				this->_content = page;
			}
		}
	}
	return (header);
}

std::string	Response::generate_chunk(void)
{
	std::stringstream	stream;
	std::string			chunk;
	unsigned int		mtu;

	mtu = this->_mtu;
	if (this->_content.length() > mtu)
	{
		stream << std::hex << std::uppercase << std::setw(1) << std::setfill('0') << mtu;
		chunk = stream.str() + "\r\n";
		chunk += this->_content.substr(0, mtu) + "\r\n";
		this->_content = this->_content.substr(mtu, this->_content.length() - mtu);
		return (chunk);
	}
	if (this->_content.length() != 0)
	{
		stream.str("");
		stream << std::hex << std::uppercase << std::setw(1) << std::setfill('0') << this->_content.length();
		chunk = stream.str() + "\r\n";
		chunk += this->_content + "\r\n";
		this->_content = "";
		return (chunk);
	}
	this->_state = true;
	return ("0\r\n\r\n");
}

bool	endsWith(const std::string &str, const std::string suffix)
{
	std::size_t suffix_pos = str.find(suffix, 0);
	if (suffix_pos == std::string::npos)
		return (false);
	std::size_t str_size = str.size();
	std::size_t	suffix_size = suffix.size();
	if (str_size - suffix_size == suffix_pos)
		return (true);
	return (false);
}

std::string Response::getMimeType(const std::string &file_path)
{
	// HTML
	if (endsWith(file_path, ".html") || endsWith(file_path, ".htm"))
		return ("text/html");

	// CSS and JavaScript
	if (endsWith(file_path, ".css"))
		return ("text/css");
	if (endsWith(file_path, ".js"))
		return ("application/javascript");

	// Data formats
	if (endsWith(file_path, ".json"))
		return ("application/json");
	if (endsWith(file_path, ".xml"))
		return ("application/xml");
	if (endsWith(file_path, ".csv"))
		return ("text/csv");
	if (endsWith(file_path, ".txt"))
		return ("text/plain");

	// Images
	if (endsWith(file_path, ".png"))
		return ("image/png");
	if (endsWith(file_path, ".jpg") || endsWith(file_path, ".jpeg"))
		return ("image/jpeg");
	if (endsWith(file_path, ".gif"))
		return ("image/gif");
	if (endsWith(file_path, ".bmp"))
		return ("image/bmp");
	if (endsWith(file_path, ".ico"))
		return ("image/x-icon");
	if (endsWith(file_path, ".svg"))
		return ("image/svg+xml");
	if (endsWith(file_path, ".tiff") || endsWith(file_path, ".tif"))
		return ("image/tiff");
	if (endsWith(file_path, ".webp"))
		return ("image/webp");

	// Audio
	if (endsWith(file_path, ".mp3"))
		return ("audio/mpeg");
	if (endsWith(file_path, ".wav"))
		return ("audio/wav");
	if (endsWith(file_path, ".ogg"))
		return ("audio/ogg");
	if (endsWith(file_path, ".m4a"))
		return ("audio/mp4");

	// Video
	if (endsWith(file_path, ".mp4"))
		return ("video/mp4");
	if (endsWith(file_path, ".webm"))
		return ("video/webm");
	if (endsWith(file_path, ".ogv"))
		return ("video/ogg");
	if (endsWith(file_path, ".avi"))
		return ("video/x-msvideo");
	if (endsWith(file_path, ".mov"))
		return ("video/quicktime");
	if (endsWith(file_path, ".mpeg") || endsWith(file_path, ".mpg"))
		return ("video/mpeg");

	// Application types
	if (endsWith(file_path, ".pdf"))
		return ("application/pdf");
	if (endsWith(file_path, ".zip"))
		return ("application/zip");
	if (endsWith(file_path, ".tar"))
		return ("application/x-tar");
	if (endsWith(file_path, ".rar"))
		return ("application/vnd.rar");
	if (endsWith(file_path, ".7z"))
		return ("application/x-7z-compressed");
	if (endsWith(file_path, ".gz"))
		return ("application/gzip");
	if (endsWith(file_path, ".exe"))
		return ("application/vnd.microsoft.portable-executable");
	if (endsWith(file_path, ".iso"))
		return ("application/x-iso9660-image");

	// Fonts
	if (endsWith(file_path, ".woff"))
		return ("font/woff");
	if (endsWith(file_path, ".woff2"))
		return ("font/woff2");
	if (endsWith(file_path, ".ttf"))
		return ("font/ttf");
	if (endsWith(file_path, ".otf"))
		return ("font/otf");

	// Default for unknown types
	return ("application/octet-stream");
}


// Getters

std::map<unsigned int, std::string> Response::getHttpCodes(void) const
{
	std::map<unsigned int, std::string> result;

	result[100] = "Continue";
	result[101] = "Switching Protocols";
	result[102] = "Processing";
	result[200] = "OK";
	result[201] = "Created";
	result[202] = "Accepted";
	result[203] = "Non-Authoritative Information";
	result[204] = "No Content";
	result[205] = "Reset Content";
	result[206] = "Partial Content";
	result[207] = "Multi-Status";
	result[208] = "Already Reported";
	result[226] = "IM Used";
	result[300] = "Multiple Choices";
	result[301] = "Moved Permanently";
	result[302] = "Found";
	result[303] = "See Other";
	result[304] = "Not Modified";
	result[305] = "Use Proxy";
	result[307] = "Temporary Redirect";
	result[308] = "Permanent Redirect";
	result[400] = "Bad Request";
	result[401] = "Unauthorized";
	result[402] = "Payment Required";
	result[403] = "Forbidden";
	result[404] = "Not Found";
	result[405] = "Method Not Allowed";
	result[406] = "Not Acceptable";
	result[407] = "Proxy Authentication Required";
	result[408] = "Request Timeout";
	result[409] = "Conflict";
	result[410] = "Gone";
	result[411] = "Length Required";
	result[412] = "Precondition Failed";
	result[413] = "Payload Too Large";
	result[414] = "URI Too Long";
	result[415] = "Unsupported Media Type";
	result[416] = "Range Not Satisfiable";
	result[417] = "Expectation Failed";
	result[418] = "I'm a teapot";
	result[421] = "Misdirected Request";
	result[422] = "Unprocessable Entity";
	result[423] = "Locked";
	result[424] = "Failed Dependency";
	result[426] = "Upgrade Required";
	result[428] = "Precondition Required";
	result[429] = "Too Many Requests";
	result[431] = "Request Header Fields Too Large";
	result[451] = "Unavailable For Legal Reasons";
	result[500] = "Internal Server Error";
	result[501] = "Not Implemented";
	result[502] = "Bad Gateway";
	result[503] = "Service Unavailable";
	result[504] = "Gateway Timeout";
	result[505] = "HTTP Version Not Supported";
	result[506] = "Variant Also Negotiates";
	result[507] = "Insufficient Storage";
	result[508] = "Loop Detected";
	result[510] = "Not Extended";
	result[511] = "Network Authentication Required";
	return (result);
}

bool	Response::getState(void) const
{
	return (this->_state);
}