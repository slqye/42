/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:56:36 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/12 17:48:33 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	rrb(t_list **stack_b)
{
	t_list	*holder;
	t_list	*prevlast;

	if (counter(stack_b) <= 1)
		return ;
	holder = ft_lstlast(*stack_b);
	prevlast = ft_lst_prevlast(*stack_b);
	holder->next = *stack_b;
	*stack_b = holder;
	prevlast->next = NULL;
}
