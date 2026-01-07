/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:30:24 by slaye             #+#    #+#             */
/*   Updated: 2024/08/17 15:44:12 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class RPN {
	public:
		static float	calculate(std::string value);

	private:
		RPN(void);
		RPN(const RPN &reference);
		virtual ~RPN(void);

		RPN	&operator=(const RPN &reference);
};