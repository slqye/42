/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:44:46 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/15 21:06:38 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/imports.h"
#include "../includes/commons.h"
#include "../includes/operations.h"

void	ft_freesplit(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != 0)
		free(split[i]);
	free(split);
}

void	push_swap(char **tab, int length, int s)
{
	int		i;
	t_list	**stack_a;
	t_list	**stack_b;
	t_list	*holder;

	stack_a = malloc(sizeof(t_list **));
	stack_b = ft_calloc(sizeof(t_list **), 1);
	if (stack_a == NULL)
		return (free(stack_b), exit(EXIT_FAILURE));
	if (stack_b == NULL)
		return (free(stack_a), exit(EXIT_FAILURE));
	*stack_a = NULL;
	i = -1;
	while (++i < length)
	{
		holder = ft_lstnew(ft_atoi(tab[i]));
		if (holder == NULL)
			return (ft_lstclear(stack_a), free(stack_a), free(stack_b));
		ft_lstadd_back(stack_a, holder);
	}
	sorter(stack_a, stack_b);
	if (!s)
		ft_freesplit(tab);
	return (ft_lstclear(stack_a), free(stack_a), free(stack_b));
}

int	main(int argc, char **argv)
{
	char	**numbers;

	if (argc == 2)
	{
		numbers = ft_split(argv[1], ' ');
		if (!numbers)
			return (ft_putstr_fd("Error\n", 2), 1);
		if (!is_tab_valid(numbers, get_tab_length(numbers)))
			return (ft_freesplit(numbers), ft_putstr_fd("Error\n", 2), 1);
		if (numbers[0] == 0)
			return (free(numbers), 1);
		push_swap(numbers, get_tab_length(numbers), 0);
	}
	else if (argc > 2)
	{
		if (!is_tab_valid(&argv[1], argc - 1))
			return (ft_putstr_fd("Error\n", 2), 1);
		push_swap(&argv[1], argc - 1, 1);
	}
	return (0);
}
