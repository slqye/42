/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:47:05 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/12 17:47:30 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commons.h"
#include "../../includes/operations.h"
#include "../../includes/imports.h"

int	counter(t_list **stack)
{
	t_list	*saver;
	int		counter;

	counter = 0;
	saver = *stack;
	while (*stack)
	{
		*stack = (*stack)->next;
		counter++;
	}
	*stack = saver;
	return (counter);
}

t_list	*ft_lst_prevlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst);
}
