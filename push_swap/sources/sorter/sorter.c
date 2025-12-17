/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:32:59 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/23 14:54:00 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/imports.h"
#include "../../includes/commons.h"
#include "../../includes/operations.h"

int	get_step(t_list **stack, int stacks)
{
	if (get_min(stack)->content < 0)
		return ((get_max(stack)->content + (get_min(stack)->content * -1)) \
	/ stacks);
	return ((get_max(stack)->content + get_min(stack)->content) / stacks);
}

void	small_sorter(t_list **a, t_list **b, t_max m)
{
	int		p;
	int		s;

	p = get_step(a, get_stacks(a));
	s = get_min(a)->content + p;
	while (counter(a) != 3)
	{
		while (lst_huv(a, m.m1, s) && counter(a) != 3)
		{
			if ((*a)->content <= s && *a != m.m1 && *a != m.m2 && *a != m.m3)
			{
				pb(a, b);
				if ((*b)->content < s - (p / 2) && (*b)->next)
				{
					if ((*a)->next && !((*a)->content <= s && *a != m.m1))
						rr(a, b);
					else
						rb(b);
				}
			}
			else
				ra(a);
		}
		s += p;
	}
}

void	big_sorter(t_list **a, t_list **b, t_list *m1, t_list *m2)
{
	int	is_double;

	is_double = 0;
	while (*b != m1)
	{
		if (*b == m2)
		{
			pa(a, b);
			is_double = 1;
		}
		else if (get_app_pos(b, m1))
			rrb(b);
		else
			rb(b);
	}
	pa(a, b);
	if (is_double)
	{
		if (!*b)
			sa(a);
		else if ((*b)->next && (*b)->content < (*b)->next->content)
			ss(a, b);
		else
			sa(a);
	}
}

void	sorter(t_list **stack_a, t_list **stack_b)
{
	t_list	*holder;
	t_max	maxs;
	int		stacks;

	maxs.m1 = get_max(stack_a);
	maxs.m2 = get_max_n1(stack_a);
	maxs.m3 = get_max_n2(stack_a);
	holder = get_max(stack_a);
	stacks = get_stacks(stack_a);
	if (is_sorted(stack_a))
		return ;
	if (counter(stack_a) == 2)
		return (ra(stack_a));
	if (counter(stack_a) == 3)
		return (triple_sorter(stack_a));
	small_sorter(stack_a, stack_b, maxs);
	if (!is_sorted(stack_a))
		triple_sorter(stack_a);
	while (*stack_b)
	{
		holder = get_max(stack_b);
		big_sorter(stack_a, stack_b, holder, get_max_n1(stack_b));
	}
}
