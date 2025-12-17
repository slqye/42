/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:36 by uwywijas          #+#    #+#             */
/*   Updated: 2024/09/24 16:28:02 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "commons.hpp"

class Log {
	public:
		static void	info(std::string value);
		static void	warning(std::string value);
		static void	error(std::string value);
		static void	debug(std::string value);
};