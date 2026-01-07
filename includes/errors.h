/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaye <slaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:34:17 by uwywijas          #+#    #+#             */
/*   Updated: 2024/05/04 10:15:23 by slaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// Lexer
# define ER_LEXER_QUOTE "minishell: error when parsing for quotes"

// Parser
# define ER_PARSER_NL "minishell: syntax error near unexpected token `newline'"
# define ER_PARSER_PIPE "minishell: syntax error near unexpected token `|'"
# define ER_PARSER_RL "minishell: syntax error near unexpected token `<'"
# define ER_PARSER_RR "minishell: syntax error near unexpected token `>'"
# define ER_PARSER_RLL "minishell: syntax error near unexpected token `<<'"
# define ER_PARSER_RRR "minishell: syntax error near unexpected token `>>'"

// Interpreter
# define ER_PATH_NFOUND "minishell: path not found"
# define ER_PIPE_FUNC "minishell: pipe function error"
# define ER_FORK_FUNC "minishell: fork function error"
# define ER_MALLOC_FUNC "minishell: malloc function error"
# define ER_CMD_NFOUND ": command not found"
# define HEREDOC_STOP "\nminishell: here-document stopped"
# define ER_FILE_NFOUND ": No such file or directory"
# define ER_OPEN_FAILED "minishell: open function failed"
# define ER_CMD_DIRECTORY ": Is a directory"
# define ER_CMD_PERMS ": Permission denied"

// Builtins
# define ER_EXIT_ARGS_NB "minishell: exit: too many arguments"
# define ER_EXIT_ARG_VALUE ": numeric argument required"
# define ER_CD_ARGS_NB "minishell: cd: too many arguments"
# define ER_HOME_NFOUND "minishell: cd: HOME not set"
# define ER_EXPORT_ID "': not a valid identifier"

#endif