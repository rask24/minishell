/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/25 16:05:38 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"
#include "ctx.h"
#include "env.h"
#include "exec_internal.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	wait_for_children(pid_t last_pid)
{
	int		status;

	waitpid(last_pid, &status, WNOHANG);
	while (waitpid(-1, NULL, 0) > 0)
		;
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
