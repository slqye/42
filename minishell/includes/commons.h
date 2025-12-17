/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:12:23 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/02 17:16:40 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_H
# define COMMONS_H

# define TRUE 1
# define FALSE 0

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <stddef.h>
# include "../sources/libft/libft.h"
# include "tokens.h"

typedef struct s_tree
{
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
	char			*value;
	int				*heredoc;
}	t_tree;

typedef struct s_program
{
	char	**argv;
	char	**envp;
	t_list	**lexer;
	t_tree	*ast;
	int		argc;
	int		exit;
	int		pipelvl;
	int		hofd;
}	t_program;

typedef struct s_fds
{
	int	ifd;
	int	ofd;
	int	pifd;
	int	pofd;
}	t_fds;

extern sig_atomic_t	g_sig;

// Utils
void	free_exit(t_program *program, int status);

// Prompt
void	prompt(char *value, t_program *program);

// Lexer
t_token	*get_token(int type, char *value);
t_list	**lexer(char *line, t_program *program);
t_list	**split_command(char *command);
t_list	*get_lpipe(t_list **lexer);;
void	lst_update_type(t_list *first, t_list *second, int type);
void	free_lexer(t_list **lexer);
void	lfree(void *token);
void	print_lexer(t_list **lexer);
void	show_hashmap(int *hashmap, int length);
void	setup_tokens(char *line, int *hashmap);
void	replace_token_by_ascii(char *value);
void	update_token_by_ascii(char *value);
char	*lexer_get_value(t_list *list);
char	*get_word(int *hashmap, char *line);
char	*lexer_expender(char *value, t_program *program);
char	*get_expend_value(char *value, t_program *program);
int		lexer_get_type(t_list *list);
int		lexer_formater(t_list **lexer);
int		spaces_before_case(t_list **lexer);
int		spaces_after_case(t_list **lexer);
int		useless_quotes_case(t_list **lexer);
int		*ft_hashmap(char *line);
int		setup_quotes(char *line, int *hashmap);
int		get_list_value_length(t_list **list);
int		clean_quotes_case(t_list **lexer);
int		is_simple_quoted(char *value, int *hashmap, int is_quoted, int i);
int		add_to_list(t_list **list, char *value, int type);
int		add_var_to_list(t_list **list, char *value, t_program *program, int *i);
int		list_return_selector(t_list **list);
int		get_envp_var_length(char *str);

// Parser
t_tree	*ast(t_list **lexer);
t_tree	*get_node(t_list *lexer);
t_tree	*get_prefix(t_list *lexer);
t_tree	*get_lprefix(t_tree *prefix);
t_tree	*get_redirect(t_list *lexer);
t_tree	*get_suffix(t_list *lexer, t_tree *node);
t_tree	*tree_new(int type, char *value, t_tree *left, t_tree *right);
t_list	*get_next_token(t_list *lexer);
void	print_tree(t_tree *tree, int n);
void	free_tree(t_tree *tree);
void	consume_token(t_list *token);
int		check_syntax(t_list *lexer);

// Interpreter
t_list	*setup_pipes(t_tree *ast);
void	close_pipes(t_list *pipe);
void	per_cmd_nfound(t_program *program, char *cmd_name);
void	free_path_split(char **split);
void	path_execve(char *cmd, char **argv, t_program *program);
void	execute_ast(t_program *program, t_tree *node, int ifd, int ofd);
void	execute_cmd(t_program *program, t_tree *node, int ifd, int ofd);
void	f_pipe(t_program *program, t_tree *node, int ifd, int ofd);
void	f_pipe_right(t_program *program, t_tree *node, t_fds *fds);
void	sclose(int fd);
void	get_cmd_fds(t_program *program, t_tree *node, int *ifd, int *ofd);
void	check_perms(t_program *program, char *builded_cmd);
void	*redirect_setup(t_tree *node, t_tree **holder, int *fds);
void	setup_io_fds(int *rifd, int *rofd, int *ifd, int *ofd);
void	cmd_duping(t_program *program, int ifd, int ofd);
void	update_exit_status(t_program *program, int status);
void	safe_print(char *v1, char *v2, char *v3, int fd);
char	**get_cmd_option(t_tree *node);
int		interpreter(t_tree *ast, t_program *program);
int		cmd_execute(t_tree *node, t_program *program, int in_fd, t_list *pipe);
int		get_node_size(t_tree *node, int select);
int		f_pipe_left(t_program *program, t_tree *node, t_fds *fds);
int		setup_heredocs(t_tree *tree);

// Builtins
void	check_and_exec_builtin(t_program *program, t_tree *node);
void	ft_echo(t_tree *node);
void	ft_pwd(void);
void	ft_exit(t_program *program, t_tree *node);
void	ft_env(t_program *program);
void	ft_cd(t_program *program, t_tree *node);
void	ft_solo_cd(t_program *program, t_tree *node);
void	ft_unset(t_program *program, t_tree *node);
void	ft_export(t_program *program, t_tree *node);
void	update_pwds(t_program *program, char *current, char *next);
char	*get_with_home(char **envp, char *value);
void	cd_solo_home(t_program *program, char *oldpwd, char *home);
void	cd_solo_path(t_program *program, char *oldpwd, char **argv);
void	cd_home(t_program *program, char *oldpwd, char *home);
void	cd_path(t_program *program, char *oldpwd, char **argv);
int		add_to_envp(t_program *program, char *value);
int		remove_to_envp(t_program *program, char *value);
int		is_env_containing(t_program *program, char *key);
int		ft_array_len(char **array);
void	ft_array_cleaner(void **array, int position);
int		ft_print_env(char **envp);
char	**ft_dup_envp(char **envp);
int		ft_env_args(char **argv);
int		ft_valid_arg(char *argv);
int		ft_to_update(t_program *program, char *argv);
void	ft_been_printed(char *line);
int		ft_strcmp(char *s1, char *s2);

// Signals
void	setup_signals(void);
void	sig_default(void);
void	sig_ignore(void);
void	signals_setup_heredocs(void);

#endif