/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:58:25 by slaye             #+#    #+#             */
/*   Updated: 2024/08/16 13:16:36 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class BitcoinExchange {
	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &reference);
		virtual ~BitcoinExchange(void);

		BitcoinExchange	&operator=(const BitcoinExchange &reference);

		void	exchange(char *input);

	private:
		std::string						_path_db;
		std::map<std::string, double>	_map_db;
};