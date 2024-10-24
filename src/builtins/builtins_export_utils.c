/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:52:34 by yliu              #+#    #+#             */
/*   Updated: 2024/10/24 20:12:35 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_a_export(void *content)
{
	t_env	*env_item;

	env_item = (t_env *)content;
	if (env_item->is_valid_value)
		ft_printf("declare -x %s=\"%s\"\n", env_item->key, env_item->value);
	else
		ft_printf("declare -x %s\n", env_item->key);
}

bool	cmp_func(t_env_list *a, t_env_list *b)
{
	return (ft_strcmp(get_env_key(a), get_env_key(b)) > 0);
}

void	update_env_value(t_env_list *env, char *value)
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
