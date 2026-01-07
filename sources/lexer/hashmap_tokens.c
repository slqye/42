/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:39:51 by uwywijas          #+#    #+#             */
/*   Updated: 2024/03/12 15:46:33 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	setup_tokens(char *line, int *hashmap)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == S_QUOTE)
		{
			while (line[++i] != S_QUOTE)
				;
		}
		else if (line[i] == D_QUOTE)
		{
			while (line[++i] != D_QUOTE)
				;
		}
		if (line[i] == PIPE)
			hashmap[i] = T_PIPE;
		if (line[i] == SPACE)
			hashmap[i] = T_SPACE;
		else if (line[i] == SL_REDIRECTION)
			hashmap[i] = T_SL_REDIRECTION;
		else if (line[i] == SR_REDIRECTION)
			hashmap[i] = T_SR_REDIRECTION;
	}
}
