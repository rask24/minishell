/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:15:45 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/24 23:34:54 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "exec_internal.h"
#include "utils.h"

#define PIPE_READ 0
#define PIPE_WRITE 1

int execute_pipeline(t_ast *node, t_env_list *env_list, t_pipeline_conf *conf)
{
	int pipe_fd[2];

	if (node->right != NULL)
	{
		if (pipe(pipe_fd) == -1)
		{
			print_error("pipe", strerror(errno));
			return (EXIT_FAILURE);
		}
		conf->fd_out = pipe_fd[PIPE_WRITE];
	}
	else
		conf->fd_out = STDOUT_FILENO;
	if (execute_ast_node(node->left, env_list, conf) == EXIT_FAILURE)
	{
		if (node->right != NULL)
		{
			close(pipe_fd[PIPE_READ]);
			close(pipe_fd[PIPE_WRITE]);
		}
		return (EXIT_FAILURE);
	}
	if (conf->fd_in != STDIN_FILENO)
		close(conf->fd_in);
	if (node->right != NULL)
	{
		close(pipe_fd[PIPE_WRITE]);
		conf->fd_in = pipe_fd[PIPE_READ];
		if (execute_ast_node(node->right, env_list, conf) == EXIT_FAILURE)
		{
			close(pipe_fd[PIPE_READ]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
