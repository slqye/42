/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:52:26 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/15 14:41:57 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# define PIPE 124
# define SL_REDIRECTION 60
# define SR_REDIRECTION 62
# define S_QUOTE 39
# define D_QUOTE 34
# define DOLLAR 36
# define EX_PIPE 17
# define EX_SL_REDIRECTION 18
# define EX_SR_REDIRECTION 19
# define EX_S_QUOTE 20
# define EX_D_QUOTE 21
# define QUESTION 63

enum e_tokens
{
	T_WORD,
	T_PIPE,
	T_SL_REDIRECTION,
	T_SR_REDIRECTION,
	T_DL_REDIRECTION,
	T_DR_REDIRECTION,
	T_S_QUOTE,
	T_D_QUOTE,
	T_SPACE,
	T_CONSUMED
};

# define TDR_R T_DR_REDIRECTION

typedef struct s_token
{
	int		type;
	void	*value;
}	t_token;

#endif