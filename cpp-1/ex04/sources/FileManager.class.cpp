/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileManager.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:57:31 by slaye             #+#    #+#             */
/*   Updated: 2024/05/21 10:14:51 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

FileManager::FileManager(int mode) : _mode(mode), _error(false) {
	if (this->_mode != F_READ && this->_mode != F_WRITE)
		this->~FileManager();
}

FileManager::~FileManager(void) {
	return ;
}

bool	FileManager::open(const char *fpath) {
	this->_fpath = fpath;
	if (this->_mode == F_READ) {
		this->_ifs.open(this->_fpath);
		if (!this->_ifs.good())
			return (false);
		return (true);
	}
	else {
		this->_ofs.open(this->_fpath);
		if (!this->_ofs.good())
			return (false);
		return (true);
	}
}

void	FileManager::close(void) {
	if (this->_mode == F_READ)
		this->_ifs.close();
	else
		this->_ofs.close();
}

std::string	FileManager::read_file(void) {
	std::string	line;
	std::string	value;

	if (this->_mode != F_READ) {
		this->_error = true;
		return ("");
	}
	while (getline(this->_ifs, line)) {
		value += line + "\n";
	}
	return (value);
}

void	FileManager::write_file(std::string value) {
	this->_ofs << value << std::endl;
}

bool	FileManager::get_error(void) const {
	return (this->_error);
}