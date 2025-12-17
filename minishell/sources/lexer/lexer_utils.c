/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:11:48 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/05 17:19:24 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

char	*get_word(int *hashmap, char *line)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	while (++i < (int) ft_strlen(line))
	{
		if (hashmap[i] == T_PIPE)
			break ;
		if (hashmap[i] == T_SPACE)
			break ;
		if (hashmap[i] == T_SL_REDIRECTION)
			break ;
		if (hashmap[i] == T_SR_REDIRECTION)
			break ;
	}
	result = ft_calloc(i + 1, sizeof(char));
	if (!result)
		return (NULL);
	j = -1;
	while (++j < i)
		result[j] = line[j];
	result[j] = '\0';
	return (result);
}

t_token	*get_token(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

void	lfree(void *token)
{
	free(((t_token *) token)->value);
	free(token);
}

void	free_lexer(t_list **lexer)
{
	ft_lstclear(lexer, &lfree);
	free(lexer);
}

void	print_lexer(t_list **lexer)
{
	t_list	*holder;

	holder = *lexer;
	while (*lexer)
	{
		printf("[%d]: ", lexer_get_type(*lexer));
		printf("[%s]\n", lexer_get_value(*lexer));
		*lexer = (*lexer)->next;
	}
	*lexer = holder;
}
