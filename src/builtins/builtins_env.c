/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:41:44 by yliu              #+#    #+#             */
/*   Updated: 2024/10/24 20:11:09 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_env_entry(void *content)
{
	t_env	*env_item;

	env_item = (t_env *)content;
	if (env_item->is_valid_value)
		ft_printf("%s=%s\n", env_item->key, env_item->value);
}

int	builtins_env(char **args, t_ctx *ctx)
{
	if (args[1])
	{
		print_error("env", "too many arguments");
		return (EXIT_FAILURE);
	}
	ft_lstiter(ctx->env, print_env_entry);
	return (EXIT_SUCCESS);
}
