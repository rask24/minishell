/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:44:03 by yliu              #+#    #+#             */
/*   Updated: 2024/09/11 11:36:01 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtins.h"

static void	_print_args(char **args)
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

static bool	_is_option(char *arg)
{
	int	i;

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

int	builtins_echo(char **args, char **env)
{
	(void)env;
	if (_is_option(*++args))
		_print_args(++args);
	else
	{
		_print_args(args);
		printf("\n");
	}
	return (EXIT_SUCCESS);
}
