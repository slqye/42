/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:09:48 by slaye             #+#    #+#             */
/*   Updated: 2024/07/05 15:48:36 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

int	main(void)
{
	Data		*tdata = new Data;
	Data		*rdata;
	uintptr_t	holder;

	tdata->value = "Test";
	holder = Serializer::serialize(tdata);
	rdata = Serializer::deserialize(holder);
	std::cout << tdata << " : " << rdata << std::endl;
	std::cout << tdata->value << " : " << rdata->value << std::endl;
	delete (tdata);
}