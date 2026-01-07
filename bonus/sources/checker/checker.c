/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:32:59 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/15 21:03:35 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/imports.h"
#include "../../includes/commons.h"
#include "../../includes/operations.h"

int	is_sorted(t_list **stack)
{
	t_list	*saver;

	saver = *stack;
	if (!*stack)
		return (0);
	while ((*stack)->next)
	{
		if ((*stack)->content > (*stack)->next->content)
			return (*stack = saver, 0);
		*stack = (*stack)->next;
	}
	*stack = saver;
	return (1);
}

int	is_operation(t_list **stack_a, t_list **stack_b, char *value)
{
	if (ft_strncmp(value, "pa\n", 3) == 0)
		pa(stack_a, stack_b);
	else if (ft_strncmp(value, "pb\n", 3) == 0)
		pb(stack_a, stack_b);
	else if (ft_strncmp(value, "ra\n", 3) == 0)
		ra(stack_a);
	else if (ft_strncmp(value, "rb\n", 3) == 0)
		rb(stack_b);
	else if (ft_strncmp(value, "rr\n", 3) == 0)
		rr(stack_a, stack_b);
	else if (ft_strncmp(value, "rra\n", 4) == 0)
		rra(stack_a);
	else if (ft_strncmp(value, "rrb\n", 4) == 0)
		rrb(stack_b);
	else if (ft_strncmp(value, "rrr\n", 4) == 0)
		rrr(stack_a, stack_b);
	else if (ft_strncmp(value, "sa\n", 3) == 0)
		sa(stack_a);
	else if (ft_strncmp(value, "sb\n", 3) == 0)
		sb(stack_b);
	else if (ft_strncmp(value, "ss\n", 3) == 0)
		ss(stack_a, stack_b);
	else
		return (0);
	return (1);
}

void	checker(t_list **stack_a, t_list **stack_b)
{
	char	*value;

	while (1)
	{
		value = get_next_line(0);
		if (!value)
			break ;
		if (!is_operation(stack_a, stack_b, value))
			return (free(value), ft_putstr_fd("Error\n", 2));
		free(value);
	}
	if (is_sorted(stack_a) && !*stack_b)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}
