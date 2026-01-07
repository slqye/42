/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:38:26 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/08 15:14:22 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	rr(t_list **stack_a, t_list **stack_b)
{
	t_list	*holder;

	holder = *stack_a;
	*stack_a = (*stack_a)->next;
	ft_lstlast(*stack_a)->next = holder;
	holder->next = NULL;
	holder = *stack_b;
	*stack_b = (*stack_b)->next;
	ft_lstlast(*stack_b)->next = holder;
	holder->next = NULL;
	ft_putstr_fd("rr\n", 1);
}
