/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:41:00 by slaye             #+#    #+#             */
/*   Updated: 2024/08/09 11:16:07 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class Span {
	public:
		Span(void);
		Span(unsigned int n);
		Span(const Span &reference);
		virtual ~Span(void);

		Span	&operator=(const Span &reference);

		void			addNumber(int number);
		unsigned int	shortestSpan(void) const;
		unsigned int	longestSpan(void) const;

		template <typename T>
		void			addNumber(T begin, T end)
		{
			if (_container.size() + std::distance(begin, end) > _n)
				throw Span::CapacityException();
			_container.insert(_container.end(), begin, end);
		}

		class CapacityException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class DistanceException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

	private:
		unsigned int		_n;
		std::vector<int>	_container;
};