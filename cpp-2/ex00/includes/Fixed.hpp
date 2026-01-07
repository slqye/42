/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:59:31 by slaye             #+#    #+#             */
/*   Updated: 2024/05/29 15:45:25 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed {
	public:
		Fixed(void); // canonical
		Fixed(Fixed const &ref); // canonical
		~Fixed(void); // canonical

		Fixed	&operator=(Fixed const &ref); // canonical
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
	private:
		static int const	shift = 8;
		int					value;
};

#endif
