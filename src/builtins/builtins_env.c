/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:41:44 by yliu              #+#    #+#             */
/*   Updated: 2024/09/20 12:09:39 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_env_entry(void *content)
{
	printf("%s=%s\n", ((t_env *)content)->key, ((t_env *)content)->value);
}

int	builtins_env(char **args, t_builtins_ctx *ctx)
{
	(void)args;
	ft_lstiter(ctx->env, print_env_entry);
	return (EXIT_SUCCESS);
}
