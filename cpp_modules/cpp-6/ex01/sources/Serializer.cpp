/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:34:09 by slaye             #+#    #+#             */
/*   Updated: 2024/07/05 15:45:33 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.hpp"

Serializer::Serializer(void)
{
}

Serializer::Serializer(const Serializer &ref)
{
	*this = ref;
}

Serializer &Serializer::operator=(Serializer const &ref)
{
	(void) ref;
	return (*this);
}

Serializer::~Serializer(void)
{
}

uintptr_t Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}