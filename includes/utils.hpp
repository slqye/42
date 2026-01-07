/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:37:22 by nlederge          #+#    #+#             */
/*   Updated: 2024/10/16 13:38:49 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "commons.hpp"

// Templates
template <typename T>
std::string numberToString(T number)
{
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

template <typename T>
T stringToNumber(const std::string& str)
{
	std::istringstream iss(str);
	T number;
	iss >> number;
	return number;
}

// Number functions
bool isNumber(const std::string& str);

// String functions
std::string stripWhiteSpaces(const std::string& str);

#endif
