/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:44:03 by yliu              #+#    #+#             */
/*   Updated: 2024/09/29 16:23:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtins.h"

static void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (i != 0)
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
}

static bool	has_n_option(char *arg)
{
	int	i;

	if (arg == NULL)
		return (false);
	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	builtins_echo(char **args, t_ctx *ctx)
{
	(void)ctx;
	if (has_n_option(args[1]))
		print_args(args + 2);
	else
	{
		print_args(args + 1);
		printf("\n");
	}
	return (EXIT_SUCCESS);
}
