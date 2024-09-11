/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:41:44 by yliu              #+#    #+#             */
/*   Updated: 2024/09/11 10:41:20 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_a_env(void *content)
{
	printf("%s=%s\n", ((t_env *)content)->name, ((t_env *)content)->value);
}

int	builtins_env(char **args, t_config *config)
{
	(void)args;
	ft_lstiter(config->env, print_a_env);
	return (EXIT_SUCCESS);
}
