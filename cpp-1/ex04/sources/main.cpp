/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:40:54 by slaye             #+#    #+#             */
/*   Updated: 2024/05/21 10:15:00 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

std::string	get_sed_replace(std::string value, std::string s1, std::string s2) {
	std::string	result;
	std::string	holder;

	if (s1 == "")
		return (value);
	for (int i = 0; i < (int) value.length(); i++) {
		if (i + s1.length() > value.length())
			break ;
		holder = value.substr(i, s1.length());
		if (holder == s1) {
			result += s2;
			i += s1.length() - 1;
		}
		else
			result += value[i];
	}
	return (result);
}

int	main(int argc, char **argv) {
	FileManager	fread(F_READ);
	FileManager	fwrite(F_WRITE);
	std::string	file_value;

	if (argc != 4) {
		std::cerr << ERR_NB_ARGS << std::endl;
		return (1);
	}
	if (fread.open(argv[1]) == false) {
		std::cerr << ERR_OP_FILE << std::endl;
		return (1);
	}
	file_value = fread.read_file();
	if (file_value == "" && fread.get_error() == true) {
		std::cerr << ERR_RD_FILE << std::endl;
		return (1);
	}
	fread.close();
	if (fwrite.open((std::string(argv[1]) + ".replace").c_str()) == false) {
		std::cerr << ERR_OP_FILE << std::endl;
		return (1);
	}
	fwrite.write_file(get_sed_replace(file_value, argv[2], argv[3]));
	fwrite.close();
	return (0);
}
