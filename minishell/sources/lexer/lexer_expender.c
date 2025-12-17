/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expender.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:37:20 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/04 10:10:23 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	add_to_list(t_list **list, char *value, int type)
{
	t_token	*token;
	t_list	*holder;

	if (!value)
		return (1);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (1);
	token->type = type;
	token->value = value;
	holder = ft_lstnew(token);
	if (!holder)
		return (free(token), 1);
	ft_lstadd_back(list, holder);
	return (0);
}

char	*get_expend_value(char *value, t_program *program)
{
	int	i;
	int	length;

	length = 0;
	i = -1;
	if (value[0] && value[0] == QUESTION)
		return (ft_itoa(program->exit));
	if (!value[0])
		return ("$");
	while (ft_isalpha(value[++i]) && value[i] != '\0')
		length++;
	i = -1;
	while (length > 0 && program->envp[++i])
	{
		if (get_envp_var_length(program->envp[i]) != length)
			continue ;
		else if (ft_strncmp(program->envp[i], value, \
		get_envp_var_length(program->envp[i])) == 0)
		{
			replace_token_by_ascii(&program->envp[i][length + 1]);
			return (&program->envp[i][length + 1]);
		}
	}
	return ("");
}

int	list_expend(t_list **list, char *value, t_program *program)
{
	int		*hashmap;
	int		is_quoted;
	int		i;

	hashmap = ft_hashmap(value);
	if (!hashmap)
		return (1);
	is_quoted = 0;
	i = -1;
	while (value[++i] != '\0')
	{
		is_quoted = is_simple_quoted(value, hashmap, is_quoted, i);
		if (value[i] == DOLLAR && is_quoted == 0)
		{
			if (add_var_to_list(list, value, program, &i) != 0)
				return (free(hashmap), 1);
		}
		else
		{
			if (add_to_list(list, &value[i], 0) != 0)
				return (free(hashmap), 1);
		}
	}
	return (list_return_selector(list), free(hashmap), 0);
}

char	*get_result_value(t_list **list)
{
	int		length;
	char	*result;
	int		i;
	int		j;

	length = get_list_value_length(list);
	result = ft_calloc(length + 1, sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	while (*list)
	{
		if (lexer_get_type(*list) == 1 || lexer_get_type(*list) == 2)
		{
			i = -1;
			while (lexer_get_value(*list)[++i] != '\0')
				result[j++] = lexer_get_value(*list)[i];
			if (lexer_get_type(*list) == 2)
				free(lexer_get_value(*list));
		}
		else
			result[j++] = lexer_get_value(*list)[0];
		*list = (*list)->next;
	}
	return (result);
}

char	*lexer_expender(char *value, t_program *program)
{
	t_list	**lst;
	t_list	*holder;
	char	*result;

	lst = ft_calloc(1, sizeof(t_list *));
	if (!lst)
		return (NULL);
	if (ft_strchr(value, DOLLAR) == NULL)
		return (free(lst), ft_strdup(value));
	if (list_expend(lst, value, program) != 0)
		return (ft_lstclear(lst, &free), free(lst), NULL);
	holder = *lst;
	result = get_result_value(lst);
	if (!result)
		return (ft_lstclear(lst, &free), free(lst), NULL);
	*lst = holder;
	return (ft_lstclear(lst, &free), free(lst), result);
}
