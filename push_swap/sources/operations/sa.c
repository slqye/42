/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:38:26 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/06 16:20:05 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	sa(t_list **stack_a)
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
	ft_putstr_fd("sa\n", 1);
}
