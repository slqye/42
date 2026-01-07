/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:20:59 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/05 18:16:44 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	check_syntax_redirection(t_list *lexer)
{
	int	type;

	type = lexer_get_type(lexer);
	if (type == T_PIPE)
		return (ft_putendl_fd(ER_PARSER_PIPE, 2), 1);
	else if (type == T_SL_REDIRECTION)
		return (ft_putendl_fd(ER_PARSER_RL, 2), 1);
	else if (type == T_SR_REDIRECTION)
		return (ft_putendl_fd(ER_PARSER_RR, 2), 1);
	else if (type == T_DL_REDIRECTION)
		return (ft_putendl_fd(ER_PARSER_RLL, 2), 1);
	else if (type == T_DR_REDIRECTION)
		return (ft_putendl_fd(ER_PARSER_RRR, 2), 1);
	return (0);
}

int	check_syntax(t_list *lexer)
{
	t_list	*holder;

	holder = lexer;
	while (lexer)
	{
		if (lexer_get_type(lexer) == T_PIPE)
		{
			if (!lexer->next)
				return (lexer = holder, ft_putendl_fd(ER_PARSER_NL, 2), 1);
			else if (lexer_get_type(lexer->next) == T_PIPE)
				return (lexer = holder, ft_putendl_fd(ER_PARSER_PIPE, 2), 1);
		}
		else if (lexer_get_type(lexer) != T_WORD)
		{
			if (!lexer->next)
				return (lexer = holder, ft_putendl_fd(ER_PARSER_NL, 2), 1);
			else if (check_syntax_redirection(lexer->next) != 0)
				return (lexer = holder, 1);
		}
		lexer = lexer->next;
	}
	return (lexer = holder, 0);
}
