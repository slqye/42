/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:14:21 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/16 14:57:14 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

void	print_value(char **values, int i)
{
	int	start;

	start = i;
	while (values[i])
	{
		if (i != start && values[i])
			printf(" ");
		printf("%s", values[i]);
		i++;
	}
}

void	ft_echo(t_tree *node)
{
	char	**argv;
	int		i;
	int		j;
	int		is_newline;

	is_newline = 1;
	argv = get_cmd_option(node);
	if (argv == NULL)
		return ((void) printf("\n"));
	i = 0;
	while (argv[++i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j] != '\0' && argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		is_newline = 0;
	}
	if (i == 0)
		i++;
	print_value(argv, i);
	if (is_newline)
		printf("\n");
	free(argv);
}
