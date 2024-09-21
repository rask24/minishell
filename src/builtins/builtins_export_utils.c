/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:52:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/21 14:53:25 by yliu             ###   ########.fr       */
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
