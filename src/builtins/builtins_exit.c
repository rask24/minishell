/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:47:26 by yliu              #+#    #+#             */
/*   Updated: 2024/09/17 19:27:01 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <errno.h>

static bool	is_numeric(const char *exit_status)
{
	if (*exit_status == '-' || *exit_status == '+')
		exit_status++;
	if (*exit_status == '\0')
		return (false);
	while (*exit_status)
	{
		if (!ft_isdigit(*exit_status))
			return (false);
		exit_status++;
	}
	return (true);
}

int	builtins_exit(char **args, t_builtins_ctx *config)
{
	long	res;
	int		i;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1] == NULL)
		exit(config->exit_status & 0xFF);
	i = 1;
	if (ft_strcmp(args[1], "--") == 0)
		i++;
	if (args[++i] == NULL)
	{
		res = ft_strtol(args[--i], NULL, 10);
		if (errno == ERANGE || is_numeric(args[i]) == false)
		{
			print_error("exit", ft_strjoin(args[i],
					": numeric argument required"));
			exit(2);
		}
		exit(res & 0xFF);
	}
	else
	{
		print_error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
}
