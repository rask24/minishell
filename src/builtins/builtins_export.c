/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:41:00 by yliu              #+#    #+#             */
/*   Updated: 2024/09/21 14:50:13 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_a_export(void *content)
{
	if (((t_env *)content)->is_valid_value)
		printf("declare -x %s=\"%s\"\n", ((t_env *)content)->key,
			((t_env *)content)->value);
	else
		printf("declare -x %s\n", ((t_env *)content)->key);
}

bool	cmp_func(t_env_list *a, t_env_list *b)
{
	return (ft_strcmp(get_env_key(a), get_env_key(b)) > 0);
}

static void	update_env_value(t_env_list *env, char *value)
{
	free(get_env_value(env));
	set_env_value(env, value);
	return ;
}

t_env_list	*is_already_exist(char *key, t_env_list *env)
{
	while (env)
	{
		if (ft_strcmp(get_env_key(env), key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

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
