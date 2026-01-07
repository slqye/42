/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:59:31 by slaye             #+#    #+#             */
/*   Updated: 2024/05/24 14:15:13 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed {
	public:
		Fixed(void); // canonical
		Fixed(Fixed const &ref); // canonical
		Fixed(const int value);
		Fixed(const float value);
		~Fixed(void); // canonical

		Fixed				&operator=(Fixed const &ref); // canonical

		bool				operator>(Fixed const &ref);
		bool				operator>=(Fixed const &ref);
		bool				operator<(Fixed const &ref);
		bool				operator<=(Fixed const &ref);
		bool				operator==(Fixed const &ref);
		bool				operator!=(Fixed const &ref);
		Fixed				operator+(Fixed const &ref);
		Fixed				operator-(Fixed const &ref);
		Fixed				operator*(Fixed const &ref);
		Fixed				operator/(Fixed const &ref);

		Fixed				&operator++(void);
		Fixed				operator++(int value);
		Fixed				&operator--(void);
		Fixed				operator--(int value);

		int					getRawBits(void) const;
		void				setRawBits(int const raw);
		int					toInt(void) const;
		float				toFloat(void) const;
		static Fixed		&min(Fixed &a, Fixed &b);
		static const Fixed	&min(const Fixed &a, const Fixed &b);
		static Fixed		&max(Fixed &a, Fixed &b);
		static const Fixed	&max(const Fixed &a, const Fixed &b);
	private:
		static int const	shift = 8;
		int					value;
};

std::ostream	&operator<<(std::ostream &stream, Fixed const &fixed);

#endif
