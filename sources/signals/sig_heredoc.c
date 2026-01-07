/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:51:39 by uwywijas          #+#    #+#             */
/*   Updated: 2024/04/25 15:47:17 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

void	heredoc_sigint_handler(int signal)
{
	g_sig = signal;
	write(1, "\n", 1);
}

void	signals_setup_heredocs(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	bzero(&sigint, sizeof(sigint));
	sigint.sa_handler = &heredoc_sigint_handler;
	sigaction(SIGINT, &sigint, NULL);
	bzero(&sigquit, sizeof(sigquit));
	sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit, NULL);
}
