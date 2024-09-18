/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:45:52 by yliu              #+#    #+#             */
/*   Updated: 2024/09/17 19:27:01 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	is_remove(t_env_list *env, void *name)
{
	return (ft_strcmp(get_env_name(env), name) == 0);
}

int	builtins_unset(char **args, t_builtins_ctx *config)
{
	++args;
	while (*args)
	{
		ft_lstremove_if(&config->env, is_remove, *args, destroy_env_helper);
		args++;
	}
	return (EXIT_SUCCESS);
}
