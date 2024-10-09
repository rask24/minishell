/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:15:45 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/09 20:18:19 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "ctx.h"
#include "exec_internal.h"
#include "utils.h"

#define PIPE_READ 0
#define PIPE_WRITE 1

int	execute_left_node(t_ast *node, t_ctx *ctx, t_pipe_conf *conf, int *pipe_fd)
{
	int	ret;

	conf->fd_out = pipe_fd[PIPE_WRITE];
	ret = execute_ast_node(node, ctx, conf);
	close(pipe_fd[PIPE_WRITE]);
	return (ret);
}

int	execute_right_node(t_ast *node, t_ctx *ctx, t_pipe_conf *conf, int *pipe_fd)
{
	int	ret;

	if (conf->fd_in != STDIN_FILENO)
		close(conf->fd_in);
	conf->fd_in = pipe_fd[PIPE_READ];
	if (node->type != AST_PIPE)
		conf->fd_out = STDOUT_FILENO;
	ret = execute_ast_node(node, ctx, conf);
	close(pipe_fd[PIPE_READ]);
	return (ret);
}

int	execute_pipeline(t_ast *node, t_ctx *ctx, t_pipe_conf *conf)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		print_error("pipe", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (execute_left_node(node->left, ctx, conf, pipe_fd) == EXIT_FAILURE)
	{
		close(pipe_fd[PIPE_READ]);
		close(pipe_fd[PIPE_WRITE]);
		return (EXIT_FAILURE);
	}
	if (execute_right_node(node->right, ctx, conf, pipe_fd)
		== EXIT_FAILURE)
	{
		close(pipe_fd[PIPE_READ]);
		close(pipe_fd[PIPE_WRITE]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
