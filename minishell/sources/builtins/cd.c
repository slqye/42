/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:14:21 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/02 17:31:02 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

void	update_pwds(t_program *program, char *current, char *next)
{
	char	*oldpwd;
	char	*pwd;

	if (!program->envp)
		return ;
	oldpwd = ft_strjoin("OLDPWD=", current);
	if (!oldpwd)
		return (perror("malloc"));
	pwd = ft_strjoin("PWD=", next);
	if (!pwd)
		return (free(oldpwd), perror("malloc"));
	if (is_env_containing(program, "PWD"))
		remove_to_envp(program, "PWD");
	if (is_env_containing(program, "OLDPWD"))
		remove_to_envp(program, "OLDPWD");
	add_to_envp(program, oldpwd);
	add_to_envp(program, pwd);
	free(oldpwd);
	free(pwd);
}

char	*get_home(char **envp)
{
	int	i;

	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			return (&(envp[i][5]));
	}
	return (NULL);
}

char	*get_with_home(char **envp, char *value)
{
	char	*result;

	if (value[0] == '~')
	{
		result = ft_strjoin(get_home(envp), &value[1]);
		return (result);
	}
	return (ft_strdup(value));
}

void	ft_solo_cd(t_program *program, t_tree *node)
{
	char	**argv;
	char	oldpwd[1024];
	int		i;

	argv = get_cmd_option(node);
	if (!argv)
		return (ft_putendl_fd(ER_MALLOC_FUNC, 2), \
		(void)(program->exit = EXIT_FAILURE));
	i = 0;
	getcwd(oldpwd, 1024);
	while (argv[i])
		i++;
	if (i > 2)
		return (free(argv), ft_putendl_fd(ER_CD_ARGS_NB, 2), \
		(void)(program->exit = EXIT_FAILURE));
	if (i == 1)
		return (cd_solo_home(program, oldpwd, get_home(program->envp)), \
		free(argv));
	else
		return (cd_solo_path(program, oldpwd, argv), free(argv));
}

void	ft_cd(t_program *program, t_tree *node)
{
	char	**argv;
	char	oldpwd[1024];
	int		i;

	argv = get_cmd_option(node);
	if (!argv)
		return (ft_putendl_fd(ER_MALLOC_FUNC, 2), \
	free_exit(program, EXIT_FAILURE));
	i = 0;
	getcwd(oldpwd, 1024);
	while (argv[i])
		i++;
	if (i > 2)
		return (free(argv), ft_putendl_fd(ER_CD_ARGS_NB, 2), \
	free_exit(program, EXIT_FAILURE));
	if (i == 1)
		return (cd_home(program, oldpwd, get_home(program->envp)), free(argv));
	else
		return (cd_path(program, oldpwd, argv), free(argv));
}
