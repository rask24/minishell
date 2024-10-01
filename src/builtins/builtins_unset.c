/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:45:52 by yliu              #+#    #+#             */
/*   Updated: 2024/10/01 19:30:27 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	should_remove(t_env_list *env, void *name)
{
	return (ft_strcmp(get_env_key(env), name) == 0);
}

int	builtins_unset(char **args, t_ctx *ctx)
{
	++args;
	while (*args)
	{
		ft_lstremove_if(&ctx->env, should_remove, *args, destroy_env_helper);
		args++;
	}
	return (EXIT_SUCCESS);
}
