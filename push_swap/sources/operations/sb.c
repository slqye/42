/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:38:26 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/06 16:20:12 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	sb(t_list **stack_b)
{
	t_list	*holder;
	t_list	*third;

	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	holder = *stack_b;
	third = (*stack_b)->next->next;
	*stack_b = (*stack_b)->next;
	(*stack_b)->next = holder;
	(*stack_b)->next->next = third;
	ft_putstr_fd("sb\n", 1);
}
