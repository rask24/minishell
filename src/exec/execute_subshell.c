/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:29:00 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/16 17:20:18 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "ctx.h"
#include "exec_internal.h"

int	execute_subshell(t_ast *node, t_ctx *ctx, t_pipe_conf *conf)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		handle_io(NULL, node->redirects, ctx, true);
		execute_ast_node(node->left, ctx, conf);
		exit(ctx->exit_status);
	}
	if (conf->next_write == STDOUT_FILENO)
		wait_for_children_with_last_status(pid, ctx);
	return (EXIT_SUCCESS);
}
