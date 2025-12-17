/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:19 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/05 16:05:22 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

t_tree	*redirect_return(t_list *token, int type)
{
	consume_token(token);
	consume_token(token->next);
	return (tree_new(type, lexer_get_value(token->next), NULL, NULL));
}

t_tree	*get_redirect(t_list *lexer)
{
	t_list	*token;

	token = get_next_token(lexer);
	if (!token)
		return (NULL);
	if (!token->next)
		return (NULL);
	if (token->next && lexer_get_type(token->next) != T_WORD)
		return (NULL);
	if (lexer_get_type(token) == T_SL_REDIRECTION)
		return (redirect_return(token, T_SL_REDIRECTION));
	if (lexer_get_type(token) == T_SR_REDIRECTION)
		return (redirect_return(token, T_SR_REDIRECTION));
	if (lexer_get_type(token) == T_DL_REDIRECTION)
		return (redirect_return(token, T_DL_REDIRECTION));
	if (lexer_get_type(token) == T_DR_REDIRECTION)
		return (redirect_return(token, T_DR_REDIRECTION));
	return (NULL);
}
