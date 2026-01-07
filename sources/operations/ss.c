/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ss.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:38:26 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/11 16:57:33 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	ss(t_list **stack_a, t_list **stack_b)
{
	t_list	*holder;
	t_list	*third;

	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	holder = *stack_a;
	third = (*stack_a)->next->next;
	*stack_a = (*stack_a)->next;
	(*stack_a)->next = holder;
	(*stack_a)->next->next = third;
	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	holder = *stack_b;
	third = (*stack_b)->next->next;
	*stack_b = (*stack_b)->next;
	(*stack_b)->next = holder;
	(*stack_b)->next->next = third;
	ft_putstr_fd("ss\n", 1);
}
