/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:15:45 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/13 15:55:15 by reasuke          ###   ########.fr       */
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

static t_pipe_conf	*construct_pipe_conf(void)
{
	t_pipe_conf	*conf;

	conf = ft_xmalloc(sizeof(t_pipe_conf));
	conf->prev_read = -1;
	conf->prev_write = -1;
	conf->next_read = STDIN_FILENO;
	conf->next_write = -1;
	return (conf);
}

static void	update_pipe_conf(t_pipe_conf *conf, int pipe_fd[2])
{
	conf->prev_read = conf->next_read;
	conf->prev_write = conf->next_write;
	conf->next_read = pipe_fd[PIPE_READ];
	conf->next_write = pipe_fd[PIPE_WRITE];
}

static void	update_last_pipe_conf(t_pipe_conf *conf)
{
	conf->prev_read = conf->next_read;
	conf->prev_write = conf->next_write;
	conf->next_read = -1;
	conf->next_write = STDOUT_FILENO;
}

void	close_pipe_fd(t_pipe_conf *conf)
{
	if (conf->prev_read != STDIN_FILENO)
		close(conf->prev_read);
	if (conf->next_write != STDOUT_FILENO)
		close(conf->next_write);
}

// TODO: Is it necessary to add guard to check if conf is NULL?
int	execute_pipeline(t_ast *node, t_ctx *ctx, t_pipe_conf *conf)
{
	t_ast		*cur;
	int			ret;
	int			pipe_fd[2];

	cur = node;
	conf = construct_pipe_conf();
	while (cur && cur->type == AST_PIPE)
	{
		if (pipe(pipe_fd) == -1)
		{
			print_error("pipe", strerror(errno));
			free(conf);
			return (EXIT_FAILURE);
		}
		update_pipe_conf(conf, pipe_fd);
		ret = execute_ast_node(cur->left, ctx, conf);
		if (ret == EXIT_FAILURE)
			return (ret);
		cur = cur->right;
	}
	update_last_pipe_conf(conf);
	ret = execute_ast_node(cur, ctx, conf);
	free(conf);
	return (ret);
}
