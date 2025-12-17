/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_formater_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:37:20 by uwywijas          #+#    #+#             */
/*   Updated: 2024/03/15 17:01:28 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	useless_quotes_case_recursion(char *value, int *hashmap, int *i)
{
	if (*i <= (int) ft_strlen(value) - 2)
	{
		if (hashmap[*i] == T_S_QUOTE && hashmap[*i + 1] == T_S_QUOTE)
			*i += 2;
		else if (hashmap[*i] == T_D_QUOTE && hashmap[*i + 1] == T_D_QUOTE)
			*i += 2;
	}
	if (*i >= (int) ft_strlen(value) - 1)
		return ;
	if (hashmap[*i] == T_S_QUOTE && hashmap[*i + 1] == T_S_QUOTE)
		useless_quotes_case_recursion(value, hashmap, i);
	else if (hashmap[*i] == T_D_QUOTE && hashmap[*i + 1] == T_D_QUOTE)
		useless_quotes_case_recursion(value, hashmap, i);
}

int	useless_quotes_case(t_list **lexer)
{
	char	*result;
	char	*value;
	int		*hashmap;
	int		i;
	int		offset;

	value = lexer_get_value(*lexer);
	hashmap = ft_hashmap(value);
	if (!hashmap)
		return (1);
	result = ft_calloc(ft_strlen(value) + 1, sizeof(char));
	if (!result)
		return (free(hashmap), 1);
	i = -1;
	offset = -1;
	while (value[++i] != '\0')
	{
		useless_quotes_case_recursion(value, hashmap, &i);
		if (i >= (int) ft_strlen(value))
			break ;
		result[++offset] = value[i];
	}
	result[++offset] = '\0';
	((t_token *)(*lexer)->content)->value = result;
	return (free(value), free(hashmap), 0);
}

int	clean_quotes_case(t_list **lexer)
{
	char	*result;
	char	*value;
	int		*hashmap;
	int		i;
	int		offset;

	value = lexer_get_value(*lexer);
	hashmap = ft_hashmap(value);
	if (!hashmap)
		return (1);
	result = ft_calloc(ft_strlen(value) + 1, sizeof(char));
	if (!result)
		return (free(hashmap), 1);
	i = -1;
	offset = -1;
	while (value[++i] != '\0')
	{
		if (hashmap[i] == T_S_QUOTE || hashmap[i] == T_D_QUOTE)
			i++;
		if (i >= (int) ft_strlen(value))
			break ;
		result[++offset] = value[i];
	}
	((t_token *)(*lexer)->content)->value = result;
	return (free(value), free(hashmap), 0);
}
