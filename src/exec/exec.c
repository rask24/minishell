/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/26 22:39:13 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "ctx.h"
#include "env.h"
#include "exec_internal.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	wait_for_children(pid_t last_pid, t_ctx *ctx)
{
	int		status;
	pid_t	wpid;

	while (true)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
			return ;
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				ctx->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ctx->exit_status = WTERMSIG(status) + 128;
		}
	}
}

int	execute_ast_node(t_ast *node, t_ctx *ctx, t_pipeline_conf *conf)
{
	if (node == NULL)
		return (EXIT_FAILURE);
	else if (node->type == AST_COMMAND)
		return (execute_command(node, ctx, conf));
	else if (node->type == AST_PIPE)
		return (execute_pipeline(node, ctx, conf));
	else
		return (EXIT_FAILURE);
}

void	exec(char *input, t_ctx *ctx)
{
	t_token_list	*token_list;
	t_ast			*node;
	t_pipeline_conf	conf;

	token_list = lexer(input);
	if (token_list == NULL)
		return ;
	node = parser(token_list);
	if (node == NULL)
	{
		destroy_token_list(token_list);
		return ;
	}
	conf = (t_pipeline_conf){.fd_in = STDIN_FILENO, .fd_out = STDOUT_FILENO};
	if (execute_ast_node(node, ctx, &conf) == EXIT_FAILURE)
		print_error("exec", "unsupported AST type");
	destroy_token_list(token_list);
	destroy_ast(node);
}
