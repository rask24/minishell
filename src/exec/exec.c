/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/20 14:56:04 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "env.h"
#include "exec_internal.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	wait_for_children(pid_t last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	exec(char *input, t_env_list *env_list)
{
	t_token_list	*token_list;
	t_ast			*node;
	pid_t			last_pid;

	token_list = lexer(input);
	if (token_list == NULL)
		return ;
	node = parser(token_list);
	if (node == NULL)
	{
		destroy_token_list(token_list);
		return ;
	}
	if (node->type == AST_PIPE || node->type == AST_COMMAND)
	{
		last_pid
			= execute_pipeline(node, env_list, STDIN_FILENO, STDOUT_FILENO);
		wait_for_children(last_pid);
	}
	else
		print_error("exec", "unsupported AST type");
	destroy_token_list(token_list);
	destroy_ast(node);
}
