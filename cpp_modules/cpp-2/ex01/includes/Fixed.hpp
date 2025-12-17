/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:59:31 by slaye             #+#    #+#             */
/*   Updated: 2024/05/22 18:38:03 by slaye            ###   ########.fr       */
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

		Fixed	&operator=(Fixed const &ref); // canonical
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		int		toInt(void) const;
		float	toFloat(void) const;
	private:
		static int const	shift = 8;
		int					value;
};

std::ostream	&operator<<(std::ostream &stream, Fixed const &fixed);

#endif
