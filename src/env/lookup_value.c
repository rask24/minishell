/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:59:10 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 09:59:21 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*lookup_value(const char *key, t_env_list *env_list)
{
	t_env_list	*env;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(key, get_env_name(env)) == 0)
			return (get_env_value(env));
		env = env->next;
	}
	return (NULL);
}
