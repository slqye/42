/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:38:00 by nlederge          #+#    #+#             */
/*   Updated: 2024/10/16 13:40:27 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.hpp"

std::string stripWhiteSpaces(const std::string& str)
{
	size_t pos_start = 0;
	size_t pos_end = str.length() - 1;

	while (pos_start <= pos_end && std::isspace(str[pos_start]))
		pos_start++;
	while (pos_end >= pos_start && std::isspace(str[pos_end]))
		pos_end--;
	return str.substr(pos_start, pos_end - pos_start + 1);
}