/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:46:50 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/05 15:41:15 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

void	exec(char ***stock, int input_fd, int output_fd, int n)
{
	char	**split;
	int		i;

	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	split = ft_split(stock[0][n], ' ');
	if (split == NULL)
		return (ft_putstr_fd("split: An error occured\n", 2));
	i = 0;
	while (ft_strncmp(stock[1][i], "PATH=", 5) != 0)
		i++;
	exec_paths(stock, split, i);
}

void	parenting(int fd, int *fds, int i)
{
	close(fd);
	if (i != 0)
		close(fds[0]);
	close(fds[1]);
	wait(NULL);
}

void	childing(int *fd, int i, char ***stock, int *hfd)
{
	close(fd[0]);
	if (i == 0)
		exec(stock, hfd[1], fd[1], i + 2);
	else
		exec(stock, hfd[0], fd[1], i + 2);
}

void	last_cmd(int hfd, char ***stock, int *fd, int argc)
{
	int	id;

	id = fork();
	if (id != 0)
	{
		wait(NULL);
		close(hfd);
		close(fd[0]);
	}
	else
	{
		hfd = open(stock[0][argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (hfd == -1)
			return (perror(stock[0][argc - 1]));
		exec(stock, fd[0], hfd, argc - 2);
		close(fd[1]);
	}
}

void	pipex(int argc, char ***stock)
{
	int	fd[2];
	int	hfd[2];
	int	id;
	int	i;

	i = -1;
	if (i == -1 && pipe(fd) == -1)
		return (perror(stock[0][1]));
	while (++i != argc - 4)
	{
		hfd[0] = fd[0];
		if (i != 0 && pipe(fd) == -1)
			return (perror(stock[0][1]));
		if (i == 0)
			hfd[1] = open(stock[0][1], O_RDONLY);
		id = fork();
		if (id != 0)
			parenting(fd[1], hfd, i);
		else if (id == 0 && hfd[1] != -1)
			childing(fd, i, stock, hfd);
		else if (id == 0)
			return (perror(stock[0][1]), exit(EXIT_FAILURE));
	}
	last_cmd(hfd[0], stock, fd, argc);
}
