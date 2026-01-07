/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expender_ascii.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:37:20 by uwywijas          #+#    #+#             */
/*   Updated: 2024/03/15 16:59:06 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	replace_token_by_ascii(char *value)
{
	int	i;

	i = -1;
	while (value[++i] != '\0')
	{
		if (value[i] == PIPE)
			value[i] = EX_PIPE;
		else if (value[i] == SL_REDIRECTION)
			value[i] = EX_SL_REDIRECTION;
		else if (value[i] == SR_REDIRECTION)
			value[i] = EX_SR_REDIRECTION;
		else if (value[i] == S_QUOTE)
			value[i] = EX_S_QUOTE;
		else if (value[i] == D_QUOTE)
			value[i] = EX_D_QUOTE;
	}
}

void	update_token_by_ascii(char *value)
{
	int	i;

	i = -1;
	while (value[++i] != '\0')
	{
		if (value[i] == EX_PIPE)
			value[i] = PIPE;
		else if (value[i] == EX_SL_REDIRECTION)
			value[i] = SL_REDIRECTION;
		else if (value[i] == EX_SR_REDIRECTION)
			value[i] = SR_REDIRECTION;
		else if (value[i] == EX_S_QUOTE)
			value[i] = S_QUOTE;
		else if (value[i] == EX_D_QUOTE)
			value[i] = D_QUOTE;
	}
}
