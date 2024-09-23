/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:41:44 by yliu              #+#    #+#             */
/*   Updated: 2024/09/20 22:33:19 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_env_entry(void *content)
{
	if (((t_env *)content)->is_valid_value)
		printf("%s=%s\n", ((t_env *)content)->key, ((t_env *)content)->value);
}

int	builtins_env(char **args, t_builtins_ctx *ctx)
{
	if (args[1])
	{
		print_error("env", "too many arguments");
		return (EXIT_FAILURE);
	}
	ft_lstiter(ctx->env, print_env_entry);
	return (EXIT_SUCCESS);
}
