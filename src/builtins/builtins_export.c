/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:41:00 by yliu              #+#    #+#             */
/*   Updated: 2024/10/24 23:05:48 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	register_value(char *key, const char *equal_ptr, t_ctx *ctx,
							bool is_append)
{
	t_env_list	*update_target;
	char		*value;
	char		*new_value;

	value = ft_xstrdup(equal_ptr + 1);
	update_target = lookup_env(key, ctx->env);
	if (update_target)
	{
		if (is_append)
		{
			new_value = ft_xstrjoin(get_env_value(update_target), value);
			free(value);
		}
		else
			new_value = value;
		update_env_value(update_target, new_value);
	}
	else
		ft_lstadd_back(&ctx->env, construct_env(ft_xstrdup(key), value));
}

static int	add_complete_env(const char *input, const char *equal_ptr,
								t_ctx *ctx)
{
	const char	*plus_ptr;
	char		*key;
	bool		is_append;

	plus_ptr = strchr(input, '+');
	if (plus_ptr != NULL && plus_ptr + 1 == equal_ptr)
	{
		is_append = true;
		key = ft_xstrndup(input, plus_ptr - input);
	}
	else
	{
		is_append = false;
		key = ft_xstrndup(input, equal_ptr - input);
	}
	if (!is_identifier(key))
	{
		print_error_export(input);
		free(key);
		return (EXIT_FAILURE);
	}
	register_value(key, equal_ptr, ctx, is_append);
	free(key);
	return (EXIT_SUCCESS);
}

static int	add_no_value_env(char *input, t_ctx *ctx)
{
	t_env_list	*env;

	if (!is_identifier(input))
	{
		print_error_export(input);
		return (EXIT_FAILURE);
	}
	if (!lookup_env(input, ctx->env))
	{
		env = construct_env_with_bool(ft_xstrdup(input), NULL, false);
		ft_lstadd_back(&ctx->env, env);
	}
	return (EXIT_SUCCESS);
}

static int	add_no_key_env(char *input)
{
	print_error_export(input);
	return (EXIT_FAILURE);
}

int	builtins_export(char **args, t_ctx *ctx)
{
	int			exit_status;
	const char	*equal_ptr;
	int			i;

	if (args[1] == NULL)
	{
		ft_lstsort(&ctx->env, cmp_func);
		ft_lstiter(ctx->env, print_a_export);
		return (EXIT_SUCCESS);
	}
	exit_status = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		equal_ptr = ft_strchr(args[i], '=');
		if (equal_ptr == args[i])
			exit_status = add_no_key_env(args[i]);
		else if (equal_ptr == NULL)
			exit_status = add_no_value_env(args[i], ctx);
		else
			exit_status = add_complete_env(args[i], equal_ptr, ctx);
		i++;
	}
	return (exit_status);
}
