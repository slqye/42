/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:24:12 by slaye             #+#    #+#             */
/*   Updated: 2024/05/01 15:11:09 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "error.h"

void	safe_print(char *v1, char *v2, char *v3, int fd)
{
	char	*result1;
	char	*result2;

	if (v1 && v2 && v3)
	{
		result1 = ft_strjoin(v1, v2);
		if (!result1)
			return ((void) perror("malloc"));
		result2 = ft_strjoin(result1, v3);
		if (!result2)
			return (free(result1), (void) perror("malloc: "));
		ft_putendl_fd(result2, fd);
		free(result1);
		free(result2);
	}
	else if (v1 && v2)
	{
		result1 = ft_strjoin(v1, v2);
		if (!result1)
			return ((void) perror("malloc"));
		ft_putendl_fd(result1, fd);
		free(result1);
	}
	else if (v1)
		ft_putendl_fd(v1, fd);
}
