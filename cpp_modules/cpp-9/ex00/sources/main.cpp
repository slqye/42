/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:12:13 by slaye             #+#    #+#             */
/*   Updated: 2024/08/16 13:28:39 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

int	main(int argc, char **argv) {
	BitcoinExchange	btc;

	if (argc != 2) {
		std::cerr << DEBUG_NAME << ERR_ARG << std::endl;
		return (1);
	}
	try { btc.exchange(argv[1]); }
	catch (std::exception &e) {
		std::cerr << DEBUG_NAME << e.what() << std::endl;
		return (2);
	}
	return (0);
}