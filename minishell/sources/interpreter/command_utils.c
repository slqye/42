/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:14:45 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/01 14:38:58 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (lstat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	error_slash(t_program *program, char *cmd_name)
{
	if (is_directory(cmd_name))
	{
		safe_print("minishell: ", cmd_name, ER_CMD_DIRECTORY, 2);
		free_exit(program, 127);
	}
	else if (access(cmd_name, F_OK))
	{
		safe_print("minishell: ", cmd_name, ER_FILE_NFOUND, 2);
		free_exit(program, 127);
	}
	else
	{
		safe_print("minishell: ", cmd_name, ER_CMD_PERMS, 2);
		free_exit(program, 126);
	}
}

void	per_cmd_nfound(t_program *program, char *cmd_name)
{
	if (ft_strchr(cmd_name, '/') != 0)
		error_slash(program, cmd_name);
	else
	{
		safe_print("minishell: ", cmd_name, ER_CMD_NFOUND, 2);
		free_exit(program, 127);
	}
}

void	check_perms(t_program *program, char *builded_cmd)
{
	if (access(builded_cmd, F_OK) != -1)
	{
		if (access(builded_cmd, X_OK) == -1)
		{
			safe_print("minishell: ", builded_cmd, ER_CMD_PERMS, 2);
			free_exit(program, 126);
		}
	}
}

void	free_path_split(char **split)
{
	int	i;

	i = -1;
	if (!split)
		return ;
	while (split[++i])
		free(split[i]);
	free(split);
}
