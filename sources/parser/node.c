/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:23 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/05 18:27:29 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

t_tree	*get_node_prefix(t_list *lexer, t_list *token, t_tree *prefix)
{
	t_tree	*result;
	t_tree	*suffix;
	t_tree	*node;

	if (lexer_get_type(token) == T_WORD)
	{
		consume_token(token);
		node = tree_new(T_WORD, lexer_get_value(token), prefix, NULL);
		suffix = get_suffix(lexer, node);
		get_lprefix(prefix)->left = suffix;
		result = tree_new(T_PIPE, "|", node, NULL);
		return (result);
	}
	result = tree_new(T_PIPE, "|", prefix, NULL);
	return (result);
}

t_tree	*get_node(t_list *lexer)
{
	t_list	*token;
	t_tree	*prefix;
	t_tree	*suffix;
	t_tree	*node;
	t_tree	*result;

	if (!lexer)
		return (NULL);
	prefix = get_prefix(lexer);
	token = get_next_token(lexer);
	if (prefix)
		return (get_node_prefix(lexer, token, prefix));
	else if (lexer_get_type(token) == T_WORD)
	{
		consume_token(token);
		node = tree_new(T_WORD, lexer_get_value(token), NULL, NULL);
		suffix = get_suffix(lexer, node);
		node->left = suffix;
		result = tree_new(T_PIPE, "|", node, NULL);
		return (result);
	}
	return (NULL);
}
