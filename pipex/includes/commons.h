/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:33:33 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/05 15:41:42 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_H
# define COMMONS_H

void	pipex(int argc, char ***stock);
void	pipex_limiter(int argc, char ***stock);
int		split_counter(char	**value);
void	s_free(char **value);
void	exec_paths(char ***stock, char **split, int i);

#endif