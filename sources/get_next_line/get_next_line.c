/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:41:03 by uwywijas          #+#    #+#             */
/*   Updated: 2024/06/05 17:26:07 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "get_next_line.h"

char	*get_buffer_line(int fd, char *buffer, char *result)
{
	int	reads;

	reads = 1;
	while (reads > 0 && !ft_gnlstrchr(buffer, '\n'))
	{
		reads = read(fd, buffer, BUFFER_SIZE);
		if (reads == -1)
			return (free(result), NULL);
		buffer[reads] = '\0';
		if (reads == 0)
		{
			if (result != NULL && ft_gnlstrlen(result) == 0)
				return (free(result), NULL);
			return (result);
		}
		result = ft_gnlstrjoin(result, buffer);
	}
	return (result);
}

void	buffer_update(char *buffer)
{
	int		length;

	if (buffer[0] == '\0' || !ft_gnlstrchr(buffer, '\n'))
		return ;
	length = BUFFER_SIZE - ft_gnlstrlen(buffer);
	buffer = ft_memmove(buffer, ft_gnlstrchr(buffer, '\n') + 1, length);
	while (length < BUFFER_SIZE)
	{
		buffer[length] = '\0';
		length++;
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	result = malloc(sizeof(char));
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	if (buffer[0])
		result = ft_gnlstrjoin(result, buffer);
	if (ft_gnlstrchr(buffer, '\n'))
		buffer_update(buffer);
	else
	{
		ft_bzero(buffer, BUFFER_SIZE);
		result = get_buffer_line(fd, buffer, result);
		buffer_update(buffer);
	}
	return (result);
}
