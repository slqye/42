/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:56:36 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/06 16:19:48 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

void	rra(t_list **stack_a)
{
	t_list	*holder;
	t_list	*prevlast;

	holder = ft_lstlast(*stack_a);
	prevlast = ft_lst_prevlast(*stack_a);
	holder->next = *stack_a;
	*stack_a = holder;
	prevlast->next = NULL;
	ft_putstr_fd("rra\n", 1);
}
