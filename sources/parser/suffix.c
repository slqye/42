/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:29 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/05 16:09:25 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

t_tree	*get_suffix(t_list *lexer, t_tree *node)
{
	t_list	*token;
	t_tree	*suffix;

	token = get_next_token(lexer);
	if (!token)
		return (NULL);
	while (lexer_get_type(token) == T_WORD)
	{
		consume_token(token);
		node->right = tree_new(T_WORD, lexer_get_value(token), NULL, NULL);
		node = node->right;
		token = get_next_token(lexer);
	}
	suffix = get_redirect(lexer);
	if (suffix)
		suffix->left = get_suffix(lexer, node);
	return (suffix);
}
