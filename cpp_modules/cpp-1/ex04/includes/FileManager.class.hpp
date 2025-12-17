/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileManager.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:56:30 by slaye             #+#    #+#             */
/*   Updated: 2024/05/21 10:14:21 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEMANAGER_CLASS_HPP
# define FILEMANAGER_CLASS_HPP

# include "commons.hpp"

# define F_READ 0
# define F_WRITE 1
# define FM_ERR_MODE "FileManager: Wrong type of mode."

class FileManager {
	public:
		FileManager(int mode);
		~FileManager(void);
		bool		open(const char *fpath);
		void		close(void);
		std::string	read_file(void);
		void		write_file(std::string value);
		bool		get_error(void) const;
	private:
		int				_mode;
		const char		*_fpath;
		std::ifstream	_ifs;
		std::ofstream	_ofs;
		bool			_error;
};

#endif