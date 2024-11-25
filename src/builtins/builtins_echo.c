/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:44:03 by yliu              #+#    #+#             */
/*   Updated: 2024/11/25 10:46:54 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtins.h"
#include "libft.h"

static void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (i != 0)
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
	}
}

static bool	has_n_option(char *arg)
{
	int		i;
	bool	has_n;

	if (arg == NULL)
		return (false);
	if (arg[0] != '-')
		return (false);
	has_n = false;
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		has_n |= true;
		i++;
	}
	return (has_n);
}

int	builtins_echo(char **args, t_ctx *ctx)
{
	size_t	option_idx;

	(void)ctx;
	option_idx = 1;
	while (has_n_option(args[option_idx]))
		option_idx++;
	print_args(args + option_idx);
	if (option_idx == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
