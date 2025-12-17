/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:09 by uwywijas          #+#    #+#             */
/*   Updated: 2024/03/07 11:27:20 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	show_hashmap(int *hashmap, int length)
{
	int	i;

	i = -1;
	printf("hashmap: ");
	while (++i < length)
		printf("%d ", hashmap[i]);
	printf("\n");
}
