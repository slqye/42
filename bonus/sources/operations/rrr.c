/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:38:26 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/12 17:48:48 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	rrr(t_list **stack_a, t_list **stack_b)
{
	t_list	*holder;
	t_list	*prevlast;

	if (counter(stack_a) <= 1 || counter(stack_b) <= 1)
		return ;
	holder = ft_lstlast(*stack_a);
	prevlast = ft_lst_prevlast(*stack_a);
	holder->next = *stack_a;
	*stack_a = holder;
	prevlast->next = NULL;
	holder = ft_lstlast(*stack_b);
	prevlast = ft_lst_prevlast(*stack_b);
	holder->next = *stack_b;
	*stack_b = holder;
	prevlast->next = NULL;
}
