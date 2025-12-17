/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:59:16 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/10 18:33:48 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

t_tree	*tree_new(int type, char *value, t_tree *left, t_tree *right)
{
	t_tree	*node;

	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->left = left;
	node->right = right;
	return (node);
}

void	print_tree(t_tree *tree, int n)
{
	int	i;

	i = n;
	if (tree->right)
		print_tree(tree->right, n + 1);
	while (i-- > 0)
		printf("\t");
	if (tree)
		printf("[%d]: %s\n", tree->type, tree->value);
	if (tree->left)
		print_tree(tree->left, n + 1);
}

t_list	*get_next_token(t_list *lexer)
{
	while (lexer)
	{
		if (lexer_get_type(lexer) != T_CONSUMED)
			return (lexer);
		lexer = lexer->next;
	}
	return (NULL);
}

void	consume_token(t_list *token)
{
	if (!token)
		return ;
	((t_token *)token->content)->type = T_CONSUMED;
}

void	free_tree(t_tree *tree)
{
	if (tree->right)
		free_tree(tree->right);
	if (tree->left)
		free_tree(tree->left);
	if (tree->heredoc)
	{
		sclose(tree->heredoc[0]);
		sclose(tree->heredoc[1]);
		free(tree->heredoc);
	}
	if (tree)
		free(tree);
}
