/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:56:36 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/15 21:09:53 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	rb(t_list **stack_b)
{
	t_list	*holder;

	if (counter(stack_b) <= 1)
		return ;
	holder = *stack_b;
	*stack_b = (*stack_b)->next;
	ft_lstlast(*stack_b)->next = holder;
	holder->next = NULL;
	ft_putstr_fd("rb\n", 1);
}
