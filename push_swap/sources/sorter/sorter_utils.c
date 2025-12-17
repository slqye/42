/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:03:43 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/15 21:27:20 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/imports.h"
#include "../../includes/commons.h"
#include "../../includes/operations.h"

int	get_app_pos(t_list **stack, t_list *item)
{
	t_list	*saver;
	int		counter;
	int		place;

	saver = *stack;
	counter = 0;
	place = 0;
	while (*stack)
	{
		if ((*stack) == item)
			place = counter;
		*stack = (*stack)->next;
		counter++;
	}
	*stack = saver;
	if (place > counter / 2)
		return (1);
	return (0);
}

int	lst_huv(t_list **stack, t_list *max, int value)
{
	t_list	*saver;

	saver = *stack;
	while (*stack)
	{
		if ((*stack)->content <= value && *stack != max)
			return (*stack = saver, 1);
		*stack = (*stack)->next;
	}
	*stack = saver;
	return (0);
}

t_list	*get_min(t_list **stack)
{
	t_list	*result;
	t_list	*saver;
	int		counter;

	saver = *stack;
	counter = INT_MAX;
	while (*stack)
	{
		if ((*stack)->content <= counter)
		{
			counter = (*stack)->content;
			result = *stack;
		}
		*stack = (*stack)->next;
	}
	*stack = saver;
	return (result);
}

t_list	*get_max(t_list **stack)
{
	t_list	*result;
	t_list	*saver;
	int		counter;

	saver = *stack;
	counter = INT_MIN;
	while (*stack)
	{
		if ((*stack)->content >= counter)
		{
			counter = (*stack)->content;
			result = *stack;
		}
		*stack = (*stack)->next;
	}
	*stack = saver;
	return (result);
}

int	counter(t_list **stack)
{
	t_list	*saver;
	int		counter;

	counter = 0;
	saver = *stack;
	while (*stack)
	{
		*stack = (*stack)->next;
		counter++;
	}
	*stack = saver;
	return (counter);
}
