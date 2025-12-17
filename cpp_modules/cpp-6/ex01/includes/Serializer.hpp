/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:30:45 by slaye             #+#    #+#             */
/*   Updated: 2024/07/05 15:50:03 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

typedef struct Data
{
	std::string	value;
}	Data;

class Serializer {
	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
	private:
		Serializer(void); // canonical
		Serializer(Serializer const &ref); // canonical
		virtual ~Serializer(void); // canonical
		Serializer	&operator=(Serializer const &ref); // canonical
};
