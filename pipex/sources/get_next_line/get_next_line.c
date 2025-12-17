/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:41:03 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/01 15:14:49 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*get_buffer_line(int fd, char *buffer, char *result)
{
	int	reads;

	reads = 1;
	while (reads > 0 && !ft_strchr(buffer, '\n'))
	{
		reads = read(fd, buffer, BUFFER_SIZE);
		if (reads == -1)
			return (free(result), NULL);
		buffer[reads] = '\0';
		if (reads == 0)
		{
			if (result != NULL && ft_strlen(result) == 0)
				return (free(result), NULL);
			return (result);
		}
		result = ft_strjoing(result, buffer);
	}
	return (result);
}

void	buffer_update(char *buffer)
{
	int		length;

	if (buffer[0] == '\0' || !ft_strchr(buffer, '\n'))
		return ;
	length = BUFFER_SIZE - ft_strlen(buffer);
	buffer = ft_memmove(buffer, ft_strchr(buffer, '\n') + 1, length);
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
		result = ft_strjoing(result, buffer);
	if (ft_strchr(buffer, '\n'))
		buffer_update(buffer);
	else
	{
		ft_bzero(buffer, BUFFER_SIZE);
		result = get_buffer_line(fd, buffer, result);
		buffer_update(buffer);
	}
	return (result);
}
