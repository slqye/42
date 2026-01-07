/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:12:08 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/19 17:08:00 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	setup_hashmap(char *line, int *hashmap)
{
	if (setup_quotes(line, hashmap) != 0)
		return (ft_putendl_fd(ER_LEXER_QUOTE, 2), 1);
	setup_tokens(line, hashmap);
	return (0);
}

int	*ft_hashmap(char *line)
{
	int	*hashmap;

	hashmap = ft_calloc(ft_strlen(line) + 1, sizeof(int));
	if (!hashmap)
		return (NULL);
	if (setup_hashmap(line, hashmap) != 0)
		return (free(hashmap), NULL);
	return (hashmap);
}
