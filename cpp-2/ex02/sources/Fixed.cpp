/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:02:20 by slaye             #+#    #+#             */
/*   Updated: 2024/05/24 14:33:11 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>
#include "Fixed.hpp"

#include <bitset>

Fixed::Fixed(void) : value(0) {
}

Fixed::Fixed(Fixed const &ref) {
	*this = ref;
}

Fixed::Fixed(const int value) {
	this->value = (value << this->shift);
}

Fixed::Fixed(const float value) {
	this->value = roundf(value * (1 << this->shift));
}

Fixed::~Fixed(void) {
}

Fixed	&Fixed::operator=(Fixed const &ref) {
	this->value = ref.getRawBits();
	return (*this);
}

bool	Fixed::operator>(Fixed const &ref) {
	if (this->toFloat() > ref.toFloat())
		return (true);
	return (false);
}

bool	Fixed::operator>=(Fixed const &ref) {
	if (this->toFloat() >= ref.toFloat())
		return (true);
	return (false);
}

bool	Fixed::operator<(Fixed const &ref) {
	if (this->toFloat() < ref.toFloat())
		return (true);
	return (false);
}

bool	Fixed::operator<=(Fixed const &ref) {
	if (this->toFloat() < ref.toFloat())
		return (true);
	return (false);
}

bool	Fixed::operator==(Fixed const &ref) {
	if (this->toFloat() == ref.toFloat())
		return (true);
	return (false);
}

bool	Fixed::operator!=(Fixed const &ref) {
	if (this->toFloat() != ref.toFloat())
		return (true);
	return (false);
}

Fixed	Fixed::operator+(Fixed const &ref) {
	return (Fixed(this->toFloat() + ref.toFloat()));
}

Fixed	Fixed::operator-(Fixed const &ref) {
	return (Fixed(this->toFloat() - ref.toFloat()));
}

Fixed	Fixed::operator*(Fixed const &ref) {
	return (Fixed(this->toFloat() * ref.toFloat()));
}

Fixed	Fixed::operator/(Fixed const &ref) {
	if (ref.getRawBits() != 0)
		return (Fixed(this->toFloat() / ref.toFloat()));
	return (*this);
}

Fixed	&Fixed::operator++(void) {
	this->value += 1;
	return (*this);
}

Fixed	Fixed::operator++(int value) {
	Fixed	holder;

	holder = *this;
	if (value != 0)
		this->value += value;
	else
		this->value += 1;
	return (holder);
}

Fixed	&Fixed::operator--(void) {
	this->value -= 1;
	return (*this);
}

Fixed	Fixed::operator--(int value) {
	Fixed	holder;

	holder = *this;
	if (value != 0)
		this->value -= value;
	else
		this->value -= 1;
	return (holder);
}

Fixed	&Fixed::min(Fixed &a, Fixed &b) {
	if (a.toFloat() < b.toFloat())
		return (a);
	return (b);
}

const Fixed	&Fixed::min(const Fixed &a, const Fixed &b) {
	if (a.toFloat() < b.toFloat())
		return (a);
	return (b);
}

Fixed	&Fixed::max(Fixed &a, Fixed &b) {
	if (a.toFloat() > b.toFloat())
		return (a);
	return (b);
}

const Fixed	&Fixed::max(const Fixed &a, const Fixed &b) {
	if (a.toFloat() > b.toFloat())
		return (a);
	return (b);
}

int	Fixed::getRawBits(void) const {
	return (this->value);
}

int	Fixed::toInt(void) const {
	return(this->value >> this->shift);
}

float	Fixed::toFloat(void) const {
	return(((float) this->value / (float) (1 << this->shift)));
}

void	Fixed::setRawBits(int const raw) {
	this->value = raw;
}

std::ostream	&operator<<(std::ostream &stream, Fixed const &fixed) {
	stream << fixed.toFloat();
	return (stream);
}
