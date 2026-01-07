/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expender_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:37:20 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/04 10:14:06 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	get_list_value_length(t_list **list)
{
	int		length;
	t_list	*holder;

	holder = *list;
	length = ft_lstsize(*list) - 1;
	while (*list)
	{
		if (lexer_get_type(*list) == 1 || lexer_get_type(*list) == 2)
			length += ft_strlen(lexer_get_value(*list));
		*list = (*list)->next;
	}
	*list = holder;
	return (length);
}

int	is_simple_quoted(char *value, int *hashmap, int is_quoted, int i)
{
	if (value[i] != '\0' && hashmap[i] == T_S_QUOTE && is_quoted == 0)
		return (1);
	else if (value[i] != '\0' && hashmap[i] == T_S_QUOTE && is_quoted == 1)
		return (0);
	return (is_quoted);
}

int	add_var_to_list(t_list **list, char *value, t_program *program, int *i)
{
	if (value[*i + 1] && value[*i + 1] == QUESTION)
	{
		if (add_to_list(list, \
		get_expend_value(&value[*i + 1], program), 2) != 0)
			return (1);
	}
	else if (add_to_list(list, \
	get_expend_value(&value[*i + 1], program), 1) != 0)
		return (1);
	while (value[++(*i)] != SPACE \
	&& value[*i] != D_QUOTE && value[*i] != QUESTION \
	&& value[*i] != S_QUOTE && value[*i] != DOLLAR && value[*i] != '\0')
		;
	if (value[*i] == QUESTION)
		(*i)++;
	(*i)--;
	return (0);
}

int	list_return_selector(t_list **list)
{
	if (add_to_list(list, "\0", 0) != 0)
		return (1);
	return (0);
}

int	get_envp_var_length(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && str[i] != '=')
		;
	return (i);
}
