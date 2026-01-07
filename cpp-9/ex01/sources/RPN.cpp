/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:30:37 by slaye             #+#    #+#             */
/*   Updated: 2024/08/17 15:51:31 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
}

RPN::RPN(const RPN &reference)
{
	(void) reference;
}

RPN::~RPN(void)
{
}

RPN	&RPN::operator=(const RPN &reference)
{
	(void) reference;
	return (*this);
}

float	add(float a, float b)
{
	return (a + b);
}

float	substract(float a, float b)
{
	return (a - b);
}

float	divide(float a, float b)
{
	return(a / b);
}

float	multiply(float a, float b)
{
	return (a * b);
}

float	RPN::calculate(std::string value)
{
	std::stack<float>	stack;
	float				result;
	std::string			operations = "+-/*";
	float				(*functions [])(float, float) = {&add, &substract, &divide, &multiply};
	float				holder1;
	float				holder2;

	for (unsigned int i = 0; i < value.length(); i++) {
		if (isdigit(value[i]))
			stack.push(static_cast<int>(value[i] - '0'));
		else if (value[i] != ' ') {
			for (unsigned int j = 0; j < operations.length(); j++) {
				if (value[i] == operations[j]) {
					if (stack.size() < 2)
						throw std::runtime_error(ERR_RUNTIME);
					holder1 = stack.top();
					stack.pop();
					holder2 = stack.top();
					stack.pop();
					stack.push((*functions[j])(holder2, holder1));
				}
			}
			
		}
	}
	result = stack.top();
	return (result);
}