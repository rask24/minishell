/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:47:26 by yliu              #+#    #+#             */
/*   Updated: 2024/10/26 19:17:14 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <errno.h>

static void	close_std_io(int *std_fds)
{
	if (std_fds == NULL)
		return ;
	close(std_fds[0]);
	close(std_fds[1]);
	close(std_fds[2]);
}

static int	exec_valid_exit(int exit_pos, char **args)
{
	long	res;
	char	*end_ptr;
	char	*msg;

	errno = 0;
	res = ft_strtol(args[exit_pos], &end_ptr, 10);
	if (errno == ERANGE || errno == EINVAL || *end_ptr != '\0')
	{
		msg = ft_xstrjoin(args[exit_pos], ": numeric argument required");
		print_error("exit", msg);
		free(msg);
		return (2);
	}
	return (res & 0xFF);
}

static int	builtins_exit_in_pipeline(char**args, t_ctx *ctx)
{
	int		exit_pos;

	(void)ctx;
	exit_pos = 1;
	if (args[1] == NULL)
		return (ctx->exit_status & 0xFF);
	if (ft_strcmp(args[1], "--") == 0)
		exit_pos++;
	if (args[exit_pos] == NULL || args[exit_pos + 1] != NULL)
	{
		print_error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	ctx->exit_status = exec_valid_exit(exit_pos, args);
	return (ctx->exit_status);
}

int	builtins_exit(char **args, t_ctx *ctx, t_pipe_conf *conf, int *std_fds)
{
	int		exit_pos;

	if (conf != NULL)
		return (builtins_exit_in_pipeline(args, ctx));
	exit_pos = 1;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1] == NULL)
	{
		close_std_io(std_fds);
		exit(ctx->exit_status & 0xFF);
	}
	if (ft_strcmp(args[1], "--") == 0)
		exit_pos++;
	if (args[exit_pos] != NULL && args[exit_pos + 1] == NULL)
	{
		close_std_io(std_fds);
		exit(exec_valid_exit(exit_pos, args));
	}
	else
	{
		print_error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
