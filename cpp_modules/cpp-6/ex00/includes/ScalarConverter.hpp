/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:58:47 by slaye             #+#    #+#             */
/*   Updated: 2024/07/05 15:09:45 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class ScalarConverter {
	public:
		static void	convert(std::string value);
	private:
		ScalarConverter(void); // canonical
		ScalarConverter(ScalarConverter const &ref); // canonical
		virtual ~ScalarConverter(void); // canonical
		ScalarConverter	&operator=(ScalarConverter const &ref); // canonical
};
