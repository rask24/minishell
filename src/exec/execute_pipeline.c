/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:15:45 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/14 17:00:42 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "exec_internal.h"
#include "utils.h"

#define PIPE_IN 0
#define PIPE_OUT 1

pid_t	execute_pipeline(t_ast *ast, char **envp, int fd_in, int fd_out)
{
	int				pipe_fds[2];
	pid_t			pid;

	if (ast->type == AST_COMMAND)
		return (execute_simple_command(ast, envp, fd_in, fd_out));
	if (pipe(pipe_fds) == -1)
	{
		print_error("pipe", strerror(errno));
		return (-1);
	}
	execute_pipeline(ast->left, envp, fd_in, pipe_fds[PIPE_OUT]);
	close(pipe_fds[PIPE_OUT]);
	pid = execute_pipeline(ast->right, envp, pipe_fds[PIPE_IN], fd_out);
	close(pipe_fds[PIPE_IN]);
	return (pid);
}
