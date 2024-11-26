/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:59:10 by yliu              #+#    #+#             */
/*   Updated: 2024/11/25 10:58:51 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*lookup_value(const char *key, t_env_list *env_list)
{
	return (get_env_value(lookup_env(key, env_list)));
}

t_env_list	*lookup_env(const char *key, t_env_list *env)
{
	while (env)
	{
		if (ft_strcmp(get_env_key(env), key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
