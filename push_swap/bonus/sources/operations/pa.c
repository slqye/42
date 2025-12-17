/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:47:39 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/12 17:32:21 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	pa(t_list **stack_a, t_list **stack_b)
{
	t_list	*holder;

	if (*stack_b == NULL)
		return ;
	holder = (*stack_b)->next;
	ft_lstadd_front(stack_a, *stack_b);
	*stack_b = holder;
}
