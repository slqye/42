/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:56:36 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/12 17:47:57 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	ra(t_list **stack_a)
{
	t_list	*holder;

	if (counter(stack_a) <= 1)
		return ;
	holder = *stack_a;
	*stack_a = (*stack_a)->next;
	ft_lstlast(*stack_a)->next = holder;
	holder->next = NULL;
}
