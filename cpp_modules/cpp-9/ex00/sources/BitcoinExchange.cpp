/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:58:44 by slaye             #+#    #+#             */
/*   Updated: 2024/08/16 15:16:09 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) : _path_db("utils/data.csv")
{
	std::ifstream	file;
	std::string		line;
	unsigned int	comma_index = 0;

	file.open((this->_path_db).c_str());
	getline(file, line);
	while (getline(file, line)) {
		comma_index = line.find(',');
		this->_map_db[line.substr(0, comma_index)] = atof(line.substr(comma_index + 1, line.length()).c_str());
	}
	file.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &reference)
{
	this->_path_db = reference._path_db;
	this->_map_db = reference._map_db;
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &reference)
{
	 if (this == &reference)
		return (*this);
	this->_path_db = reference._path_db;
	this->_map_db = reference._map_db;
	return (*this);
}

std::string	format_int_date(int year, int month, int day)
{
	std::ostringstream result;

	result << year << "-";
	if (month < 10)
		result << "0";
	result << month << "-";
	if (day < 10)
		result << "0";
	result << day;
	return (result.str());
}

void	BitcoinExchange::exchange(char *input)
{
	std::ifstream	file;
	std::string		line;
	int				year;
	int				month;
	int				day;
	float			value;
	char			extra;
	int				months_with_31_days[7] = {1, 3, 5, 7, 8, 10, 12};
	bool			is_months_with_31_days = false;

	file.open(input);
	if (!file.good())
		throw std::runtime_error(ERR_FILE);
	getline(file, line);
	if (line != "date | value")
		throw std::runtime_error(ERR_FORMAT);
	while (getline(file, line)) {
		if (!(sscanf((line.c_str()), "%d-%d-%d | %f%s", &year, &month, &day, &value, &extra) == 4))
			std::cerr << DEBUG_NAME << ERR_BAD_INPUT << line << std::endl;
		else {
			if (month > 12) {
				std::cerr << DEBUG_NAME << ERR_BAD_INPUT << line << std::endl;
				continue ;
			}
			for (unsigned int i = 0; i < 7; i++) {
				if (month == months_with_31_days[i]) {
					is_months_with_31_days = true;
					break ;
				}
			}
			if (is_months_with_31_days && day > 31) {
				std::cerr << DEBUG_NAME << ERR_BAD_INPUT << line << std::endl;
				continue ;
			}
			if (!is_months_with_31_days && day > 30) {
				std::cerr << DEBUG_NAME << ERR_BAD_INPUT << line << std::endl;
				continue ;
			}
			if (!((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
				if (month == 2 && day == 29) {
					std::cerr << DEBUG_NAME << ERR_BAD_INPUT << line << std::endl;
					continue ;
				}
			}
			if (!(value >= 0 && value <= 1000)) {
				std::cerr << DEBUG_NAME << ERR_BAD_INPUT << line << std::endl;
					continue ;
			}
			if (year < 2009 || (year == 2009 && month <= 1 && day <= 2)) {
				std::cerr << DEBUG_NAME << ERR_BAD_INPUT << line << std::endl;
					continue ;
			}
			std::map<std::string, double>::iterator it = (this->_map_db).lower_bound(format_int_date(year, month, day));
			if (it != (this->_map_db).end()) {
				if (it->first != format_int_date(year, month, day))
					it--;
				std::cout << DEBUG_NAME << line.substr(0, 11) << " => " << value << " = " << (value * it->second) << std::endl;
			}
			else if (it == (this->_map_db).end()) {
				it--;
				std::cout << DEBUG_NAME << line.substr(0, 11) << " => " << value << " = " << (value * it->second) << std::endl;
			}
			else {
				std::cerr << DEBUG_NAME << ERR_NOT_FOUND << line << std::endl;
			}
		}
	}
	file.close();
}