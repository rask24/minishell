/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:20:58 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/12 10:02:25 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

#include "ctx.h"

void	wait_for_children(void)
{
	int		status;
	pid_t	wpid;

	while (true)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
			return ;
	}
}

void	wait_for_children_with_last_status(pid_t last_pid, t_ctx *ctx)
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
