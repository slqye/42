/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:54:29 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/08 17:55:58 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

t_list	*get_next_cmd(t_list *lexer)
{
	while (lexer)
	{
		if (lexer_get_type(lexer) == T_PIPE)
			return (lexer);
		lexer = lexer->next;
	}
	return (NULL);
}

t_tree	*get_lrnode(t_tree *node)
{
	t_tree	*result;
	t_tree	*holder;

	holder = node;
	while (node->right)
		node = node->right;
	result = node;
	node = holder;
	return (result);
}

t_tree	*builder(t_list *lexer, int lvl)
{
	t_tree	*result;
	t_tree	*holder;
	t_list	*lholder;

	if (lexer == NULL)
		return (NULL);
	if (lvl != 0 && lexer_get_type(lexer) == T_PIPE)
	{
		consume_token(lexer);
		lexer = lexer->next;
	}
	lholder = lexer;
	result = builder(get_next_cmd(lexer), lvl + 1);
	holder = get_node(lholder);
	if (result == NULL)
		return (holder);
	get_lrnode(result)->right = holder;
	return (result);
}

t_tree	*ast(t_list **lexer)
{
	t_tree	*tree;

	if (check_syntax(*lexer) != 0)
		return (NULL);
	tree = builder(*lexer, 0);
	if (!tree)
		return (NULL);
	return (tree);
}
