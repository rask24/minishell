/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:20:58 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/13 14:51:10 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

#include "ctx.h"

static void	update_exit_status(int status, t_ctx *ctx)
{
	if (WIFEXITED(status))
		ctx->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ctx->exit_status = WTERMSIG(status) + 128;
}

static bool	wait_for_single_child(pid_t last_pid, t_ctx *ctx)
{
	int		status;
	pid_t	wpid;

	wpid = waitpid(-1, &status, 0);
	if (wpid == -1)
	{
		if (errno == ECHILD)
			return (false);
		print_error("waitpid", strerror(errno));
		return (false);
	}
	if (last_pid != -1 && wpid == last_pid)
		update_exit_status(status, ctx);
	return (true);
}

void	wait_for_children(void)
{
	while (wait_for_single_child(-1, NULL))
		;
}

void	wait_for_children_with_last_status(pid_t last_pid, t_ctx *ctx)
{
	while (wait_for_single_child(last_pid, ctx))
		;
}
