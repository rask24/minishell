/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/07 19:02:33 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "exec.h"
#include "exec_internal.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "ui.h"
#include "utils.h"

static char	**convert_list_to_array(t_list *cmd_args)
{
	char	**argv;
	int		i;

	argv = ft_xmalloc(sizeof(char *) * (ft_lstsize(cmd_args) + 1));
	i = 0;
	while (cmd_args != NULL)
	{
		argv[i] = cmd_args->content;
		cmd_args = cmd_args->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static void	execute_command(t_list *cmd_args, t_list *redirects, char **envp)
{
	char	**argv;

	argv = convert_list_to_array(cmd_args);
	if (handle_redirects(redirects) == -1)
		exit(EXIT_FAILURE);
	reset_signal_handlers();
	if (execve(argv[0], argv, envp) == -1)
	{
		print_error("execve", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

// Note: Now supports only simple commands
static void	spawn_process(t_list *cmd_args, t_list *redirects, char **envp)
{
	pid_t	ch_pid;
	int		status;

	ch_pid = fork();
	if (ch_pid == 0)
	{
		execute_command(cmd_args, redirects, envp);
		exit(EXIT_FAILURE);
	}
	waitpid(ch_pid, &status, 0);
}

void	exec(char *input, char **envp)
{
	t_token_list	*token_list;
	t_ast			*ast;

	token_list = lexer(input);
	if (token_list == NULL)
		return ;
	ast = parser(token_list);
	if (ast == NULL)
	{
		destroy_token_list(token_list);
		return ;
	}
	if (ast->type != AST_COMMAND)
		return ;
	spawn_process(ast->cmd_args, ast->redirects, envp);
	destroy_token_list(token_list);
}
