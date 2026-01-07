/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_limiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:46:50 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/05 15:42:48 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "imports.h"

void	exec2(char ***stock, int input_fd, int output_fd, int n)
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

void	parenting2(int fd, int *fds, int i)
{
	close(fd);
	if (i != 0)
		close(fds[0]);
	wait(NULL);
}

void	childing2(int *fd, int i, char ***stock, int *hfd)
{
	char	*value;
	int		fds[2];

	close(fd[0]);
	if (i == 0)
	{
		if (pipe(fds) == -1)
			return (perror("pipe"));
		while (1)
		{
			ft_putstr_fd("here_doc> ", 1);
			value = get_next_line(0);
			if (!value)
				return (close(fds[1]), ft_putstr_fd("\nhere_doc: stopped\n", \
			2), exec2(stock, fds[0], fd[1], i + 3));
			if (ft_strlen(stock[0][2]) == ft_strlen(value) - 1 && \
			ft_strncmp(stock[0][2], value, ft_strlen(value) - 1) == 0)
				return (free(value), close(fds[1]), \
				exec2(stock, fds[0], fd[1], i + 3));
			write(fds[1], value, ft_strlen(value));
			free(value);
		}
	}
	else
		exec2(stock, hfd[0], fd[1], i + 3);
}

void	last_cmd2(int hfd, char ***stock, int *fd, int argc)
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
		hfd = open(stock[0][argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (hfd == -1)
			return (perror(stock[0][argc - 1]));
		exec2(stock, fd[0], hfd, argc - 2);
		close(fd[1]);
	}
}

void	pipex_limiter(int argc, char ***stock)
{
	int	fd[2];
	int	hfd[2];
	int	id;
	int	i;

	i = -1;
	if (i == -1 && pipe(fd) == -1)
		return (perror(stock[0][1]));
	while (++i != argc - 5)
	{
		hfd[0] = fd[0];
		if (i != 0 && pipe(fd) == -1)
			return (perror(stock[0][1]));
		id = fork();
		if (id != 0)
			parenting2(fd[1], hfd, i);
		else if (id == 0)
			childing2(fd, i, stock, hfd);
		else
			return (perror(stock[0][1]), exit(EXIT_FAILURE));
	}
	last_cmd2(hfd[0], stock, fd, argc);
}
