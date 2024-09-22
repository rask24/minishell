/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:32:41 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 10:03:46 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

const char	**convert_env_to_array(t_env_list *env)
{
	const char	**env_array;
	const char	**tmp_array;

	env_array = ft_xmalloc(sizeof(char *) * (ft_lstsize(env) + 1));
	tmp_array = env_array;
	while (env)
	{
		*tmp_array = ft_xstrjoin(get_env_key(env),
				ft_xstrjoin("=", get_env_value(env)));
		env = env->next;
		tmp_array++;
	}
	tmp_array = NULL;
	return (env_array);
}
