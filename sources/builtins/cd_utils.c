/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:46:57 by slaye             #+#    #+#             */
/*   Updated: 2024/05/02 11:08:48 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"
#include "errors.h"

void	cd_solo_home(t_program *program, char *oldpwd, char *home)
{
	char	pwd[1024];

	if (chdir(home) != 0)
	{
		ft_putendl_fd(ER_HOME_NFOUND, 2);
		program->exit = EXIT_FAILURE;
	}
	else
	{
		getcwd(pwd, 1024);
		update_pwds(program, oldpwd, pwd);
		program->exit = EXIT_SUCCESS;
	}
}

void	cd_solo_path(t_program *program, char *oldpwd, char **argv)
{
	char	pwd[1024];
	char	*w_home;

	w_home = get_with_home(program->envp, argv[1]);
	if (!w_home)
	{
		perror("malloc");
		program->exit = EXIT_FAILURE;
	}
	else if (chdir(w_home) != 0)
	{
		free(w_home);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(argv[1]);
		program->exit = EXIT_FAILURE;
	}
	else
	{
		free(w_home);
		getcwd(pwd, 1024);
		update_pwds(program, oldpwd, pwd);
		program->exit = EXIT_SUCCESS;
	}
}

void	cd_home(t_program *program, char *oldpwd, char *home)
{
	char	pwd[1024];

	if (chdir(home) != 0)
	{
		ft_putendl_fd(ER_HOME_NFOUND, 2);
		free_exit(program, EXIT_FAILURE);
	}
	else
	{
		getcwd(pwd, 1024);
		update_pwds(program, oldpwd, pwd);
		free_exit(program, EXIT_SUCCESS);
	}
}

void	cd_path(t_program *program, char *oldpwd, char **argv)
{
	char	pwd[1024];
	char	*w_home;

	w_home = get_with_home(program->envp, argv[1]);
	if (!w_home)
	{
		perror("malloc");
		free_exit(program, EXIT_FAILURE);
	}
	else if (chdir(w_home) != 0)
	{
		free(w_home);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(argv[1]);
		free_exit(program, EXIT_FAILURE);
	}
	else
	{
		free(w_home);
		getcwd(pwd, 1024);
		update_pwds(program, oldpwd, pwd);
		free_exit(program, EXIT_SUCCESS);
	}
}
