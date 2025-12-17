/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:12:24 by uwywijas          #+#    #+#             */
/*   Updated: 2024/08/16 15:15:02 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include <sstream>
#include "BitcoinExchange.hpp"

#define DATA_PATH "utils/data.csv"
#define DEBUG_NAME "btc: "
#define ERR_ARG "error: wrong number of arguments."
#define ERR_FILE "error: input file cannot be read."
#define ERR_FORMAT "error: input file is not well formated."
#define ERR_BAD_INPUT "error: bad input => "
#define ERR_NOT_FOUND "error: date not found in database."