/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:47:26 by yliu              #+#    #+#             */
/*   Updated: 2024/09/25 18:20:46 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <errno.h>

static int	exec_valid_exit(int exit_pos, char **args)
{
	long	res;
	char	*end_ptr;

	errno = 0;
	res = ft_strtol(args[exit_pos], &end_ptr, 10);
	if (errno == ERANGE || errno == EINVAL || *end_ptr != '\0')
	{
		print_error("exit", ft_xstrjoin(args[exit_pos],
				": numeric argument required"));
		return (2);
	}
	return (res & 0xFF);
}

int	builtins_exit(char **args, t_ctx *ctx)
{
	int		exit_pos;

	exit_pos = 1;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1] == NULL)
		exit(ctx->exit_status & 0xFF);
	if (ft_strcmp(args[1], "--") == 0)
		exit_pos++;
	if (args[exit_pos] != NULL && args[exit_pos + 1] == NULL)
		exit(exec_valid_exit(exit_pos, args));
	else
	{
		print_error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
}
