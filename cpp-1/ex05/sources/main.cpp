/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:26:33 by slaye             #+#    #+#             */
/*   Updated: 2024/05/17 18:12:37 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

int	main(void) {
	Harl	harl;
	std::string	strs[8] = {"DEBUG", "INFO", "WARNING", "ERROR", "EMPTY", "", "azd", "       "};

	for (int i = 0; i < 8; i++)
		harl.complain(strs[i]);
	return (0);
}