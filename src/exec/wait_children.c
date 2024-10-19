/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:20:58 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/19 23:41:21 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ctx.h"
#include "ui.h"

static void	print_signa_termination_info(int status)
{
	const char	**siglist;

	siglist = create_siglist();
	if (!WIFSIGNALED(status))
		return ;
	if (WTERMSIG(status) == SIGINT)
		ft_putchar_fd('\n', STDERR_FILENO);
	else
		print_signal_info(siglist[WTERMSIG(status)], WTERMSIG(status));
}

static void	update_exit_status(int status, t_ctx *ctx)
{
	if (WIFEXITED(status))
		ctx->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		ctx->exit_status = WTERMSIG(status) + 128;
		print_signa_termination_info(status);
	}
}

static bool	wait_for_single_child(pid_t last_pid, t_ctx *ctx)
{
	int		status;
	pid_t	wpid;

	wpid = waitpid(-1, &status, 0);
	if (wpid == -1)
	{
		if (errno == EINTR)
			return (true);
		if (errno == ECHILD)
			return (false);
		print_error("waitpid", strerror(errno));
		return (false);
	}
	if (last_pid != -1 && wpid == last_pid)
		update_exit_status(status, ctx);
	return (true);
}

void	wait_children(void)
{
	while (wait_for_single_child(-1, NULL))
		;
}

void	wait_children_with_last_status(pid_t last_pid, t_ctx *ctx)
{
	while (wait_for_single_child(last_pid, ctx))
		;
}
