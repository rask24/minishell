/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:41:00 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 23:21:53 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_error_export(const char *input)
{
	char	*tmp;
	char	*error_msg;

	tmp = ft_xstrjoin("`", input);
	error_msg = ft_xstrjoin(tmp, ": not a valid identifier");
	free(tmp);
	print_error("export", error_msg);
	free(error_msg);
}

static int	add_complete_env(const char *input, char *equal_ptr,
		t_builtins_ctx *ctx)
{
	char		*key;
	char		*value;
	t_env_list	*update_target;

	key = ft_xstrndup(input, equal_ptr - input);
	if (!is_identifier(key))
	{
		print_error_export(key);
		return (EXIT_FAILURE);
	}
	value = ft_xstrdup(ft_strchr(input, '=') + 1);
	update_target = is_already_exist(key, ctx->env);
	if (update_target)
		update_env_value(update_target, value);
	else
		ft_lstadd_back(&ctx->env, construct_env(ft_xstrdup(key), value));
	free(key);
	return (EXIT_SUCCESS);
}

static int	add_no_value_env(char *input, t_builtins_ctx *ctx)
{
	t_env_list	*env;

	if (!is_identifier(input))
	{
		print_error_export(input);
		return (EXIT_FAILURE);
	}
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
	char	*equal_ptr;
	int		i;

	exit_status = 0;
	if (args[1] == NULL)
	{
		ft_lstsort(&ctx->env, cmp_func);
		ft_lstiter(ctx->env, print_a_export);
		return (EXIT_SUCCESS);
	}
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		equal_ptr = ft_strchr(args[i], '=');
		if (equal_ptr == args[i])
			exit_status = add_no_key_env(args[i]);
		else if (equal_ptr != NULL)
			exit_status = add_complete_env(args[i], equal_ptr, ctx);
		else
			exit_status = add_no_value_env(args[i], ctx);
		i++;
	}
	return (exit_status);
}
