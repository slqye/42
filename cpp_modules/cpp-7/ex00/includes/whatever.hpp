/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:12:09 by slaye             #+#    #+#             */
/*   Updated: 2024/07/08 15:20:04 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<typename T>
void	swap(T &a, T &b)
{
	T	holder;

	holder = a;
	a = b;
	b = holder;
}

template<typename T>
T	min(const T &a, const T &b)
{
	if (a == b)
		return (b);
	return (a < b ? a : b);
}

template<typename T>
T	max(const T &a, const T &b)
{
	if (a == b)
		return (b);
	return (a > b ? a : b);
}
