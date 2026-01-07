/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:34:25 by nlederge          #+#    #+#             */
/*   Updated: 2024/11/05 17:57:31 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

# include "commons.hpp"
# include "CGI.hpp"

class CGI;

class Location {
	private:
		std::string						_route;
		std::string						_root;
		unsigned int					_allowedMethods;
		std::map<int, std::string>		_redirection;
		bool							_autoindex;
		std::vector<CGI>				_cgi;
		std::string						_uploadsDirectory;
		std::string						_index;

	public:
		Location(void);
		~Location(void);

		// Setters
		void	setAutoindex(bool autoindex);
		void	setUploadsDirectory(std::string const &uploadsDirectory);
		void	setAllowedMethods(unsigned int methods);
		void	setIndex(std::string const &index);
		void	setRoute(std::string const &route);
		void	setRoot(std::string const &root);

		// Adders
		void	addRedirection(int code, std::string const &url);
		void	addCGI(CGI const &cgi);

		// Getters
		unsigned int const					&getAllowedMethods(void) const;
		std::map<int, std::string> const	&getRedirection(void) const;
		bool								getAutoindex(void) const;
		std::vector<CGI> const				&getCgi(void) const;
		std::string const					&getUploadsDirectory(void) const;
		std::string const					&getIndex(void) const;
		std::string const					&getRoute(void) const;
		std::string const					&getRoot(void) const;

		// Functions for parsing
		bool	isComplete(void);

		//Functions
		CGI			*selectCGI(std::string const &target);
		std::string	getActualFilePath(std::string const &header_content_target);
		bool		isMainDirectory(std::string const &header_content_target);
		bool		isInsideUploadsDirectory(std::string const &target);

		// Debug
		void	displayLocationConfig(void) const;
};

#endif // LOCATION_HPP
