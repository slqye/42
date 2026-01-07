/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:31 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/05 16:34:42 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

t_tree	*get_lprefix(t_tree *prefix)
{
	if (!prefix)
		return (NULL);
	while (prefix->left)
		prefix = prefix->left;
	return (prefix);
}

t_tree	*get_prefix(t_list *lexer)
{
	t_tree	*prefix;

	prefix = get_redirect(lexer);
	if (prefix)
		prefix->left = get_prefix(lexer);
	return (prefix);
}
