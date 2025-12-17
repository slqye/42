/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:50:45 by uwywijas          #+#    #+#             */
/*   Updated: 2024/01/12 17:47:35 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_H
# define COMMONS_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# include "imports.h"

int		get_tab_length(char **tab);
int		is_tab_valid(char **tab, int length);
void	checker(t_list **stack_a, t_list **stack_b);
t_list	*get_min(t_list **stack);
t_list	*get_max(t_list **stack);
int		get_app_pos(t_list **stack, t_list *item);
int		lst_huv(t_list **stack, t_list *max, int value);
int		counter(t_list **stack);
int		is_sorted(t_list **stack);
void	triple_sorter(t_list **stack_a);
int		get_stacks(t_list **stack_a);

#endif