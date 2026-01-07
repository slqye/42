/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:26:27 by slaye             #+#    #+#             */
/*   Updated: 2024/08/12 15:12:15 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

template <typename T>
class MutantStack : public std::stack<T> {
	public:
		MutantStack<T>(void);
		MutantStack<T>(const MutantStack &reference);
		virtual ~MutantStack<T>(void);

		MutantStack<T>	&operator=(const MutantStack &reference);

		typedef typename	std::stack<T> stack;
		typedef typename	stack::container_type::iterator iterator;
		iterator	begin() {
			return (this->c.begin());
		}
		iterator	end() {
			return (this->c.end());
		}
};

template <typename T>
MutantStack<T>::MutantStack(void) : stack()
{
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &reference) : stack(reference)
{
}

template <typename T>
MutantStack<T>::~MutantStack(void)
{
}

template <typename T>
MutantStack<T>	&MutantStack<T>::operator=(const MutantStack &reference)
{
	if (*this != reference)
		*this = reference;
	return (*this);
}