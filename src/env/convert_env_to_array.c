/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:32:41 by yliu              #+#    #+#             */
/*   Updated: 2024/10/26 18:06:49 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

const char	**convert_env_to_array(t_env_list *env)
{
	const char	**env_array;
	char		*tmp;
	int			i;

	env_array = ft_xmalloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	while (env)
	{
		tmp = ft_xstrjoin(get_env_key(env), "=");
		env_array[i] = ft_xstrjoin(tmp, get_env_value(env));
		free(tmp);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
