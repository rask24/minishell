/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:41:00 by yliu              #+#    #+#             */
/*   Updated: 2024/09/21 14:52:45 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	add_complete_env(const char *input, char *equal_index,
		t_builtins_ctx *ctx)
{
	char		*key;
	char		*value;
	t_env_list	*update_target;

	key = ft_xstrndup(input, equal_index - input);
	value = ft_xstrdup(ft_strchr(input, '=') + 1);
	update_target = is_already_exist(key, ctx->env);
	if (update_target)
		update_env_value(update_target, value);
	else
		ft_lstadd_back(&ctx->env, construct_env(ft_xstrdup(key), value));
	free(key);
	return (EXIT_SUCCESS);
}

static int	add_incomplete_env(char *input, t_builtins_ctx *ctx)
{
	t_env_list	*env;

	if (!is_already_exist(input, ctx->env))
	{
		env = construct_env_with_bool(ft_xstrdup(input), NULL, false);
		ft_lstadd_back(&ctx->env, env);
	}
	return (EXIT_SUCCESS);
}

static int	add_no_key_env(char *input)
{
	char	*error_msg;

	error_msg = ft_xstrjoin(input, ": not a valid identifier");
	print_error("export", error_msg);
	free(error_msg);
	return (EXIT_FAILURE);
}

int	builtins_export(char **args, t_builtins_ctx *ctx)
{
	int		exit_status;
	char	*equal_index;

	exit_status = 0;
	if (*(args + 1))
	{
		while (*++args)
		{
			equal_index = ft_strchr(*args, '=');
			if (equal_index == *args)
				exit_status = add_no_key_env(*args);
			else if (equal_index != NULL)
				exit_status = add_complete_env(*args, equal_index, ctx);
			else
				exit_status = add_incomplete_env(*args, ctx);
		}
	}
	else
	{
		ft_lstsort(&ctx->env, cmp_func);
		ft_lstiter(ctx->env, print_a_export);
	}
	return (exit_status);
}
